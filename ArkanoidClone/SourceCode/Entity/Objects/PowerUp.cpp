#include "../Objects/PowerUp.h"
#include "../ArkanoidClone/SourceCode/Program.h"
#include "../ArkanoidClone/SourceCode/Utility/Utility.h"

IPowerUp::IPowerUp(Program* _program, const sf::Vector2f& position) : program(_program), EntityRectangle(_program->game, PixelSizes::GetInstance().powerUpSize)
{
	powerUpTexture = ResourceManager::Get().GetTexture("powerUpTexture");
	sf::Vector2f brickSize = PixelSizes::GetInstance().brickSize;
	SetOriginCenter();
	SetPosition({ position.x - 1.5f + brickSize.x / 2,  position.y - 1.5f + brickSize.y / 2 });
	bottomCollider = program->game->background->GetCollider().top + program->game->background->GetCollider().height - GetSize().y / 2;

	textureRect.width = GetSize().x;
	textureRect.height = GetSize().y;

	SetTexture(powerUpTexture);
	gameObject.setTextureRect(textureRect);
}

void IPowerUp::Hide()
{
	gameObject.setTexture(nullptr);
	gameObject.setFillColor(sf::Color(0, 0, 0, 0));
}

void IPowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(gameObject);
}

void IPowerUp::Update(float& dt)
{
	MoveDown(dt);
	Animate(dt);
	CheckForCollisions();

}

void IPowerUp::MoveDown(float& dt)
{
	SetPosition({ GetPosition().x, GetPosition().y + speed * dt });
}

void IPowerUp::CheckForCollisions()
{
	PowerUpManager* tempManager = program->game->powerUpManager;
	if (GetPosition().y >= bottomCollider)
	{
		tempManager->FreeMemory();
		return;
	}
	
	for (auto part : (program->game->vaus->parts))
	{
		if (GetCollider().intersects(part->GetCollider()) && effectApplied == false)
		{
			ApplyEffect();
			effectApplied = true;
			tempManager->FreeMemory();
			return;
		}
	}
}

void IPowerUp::Animate(float& dt)
{
	timer -= dt;

	if (timer <= 0)
	{
		ChangeTexture();
		timer = defaultTimer;
	}
}

void IPowerUp::ChangeTexture()
{
	if (textureRect.left >= textureRect.width * 15)
		textureRect.left = 0;
	else
		textureRect.left += GetSize().x;

	gameObject.setTextureRect(textureRect);
}

AddHealth::AddHealth(Program* _program, const sf::Vector2f& position) : IPowerUp(_program, position)
{
	SetFillColor(sf::Color::Red);
}

void AddHealth::ApplyEffect()
{
	program->game->healthManager->HealOneHealth();
}

SplitBall::SplitBall(Program* _program, const sf::Vector2f& position) : IPowerUp(_program, position)
{
	SetFillColor(sf::Color::Blue);
}

void SplitBall::ApplyEffect()
{
	program->game->AddBall();
	program->game->AddBall();
}

SlowDown::SlowDown(Program* _program, const sf::Vector2f& position) : IPowerUp(_program, position)
{
	SetFillColor(sf::Color(255,165,0));
}

void SlowDown::ApplyEffect()
{
	program->game->powerUpManager->ChangeAllBallsSpeed(450);
}
