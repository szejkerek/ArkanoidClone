#include "PowerUpManager.h"

PowerUpManager::PowerUpManager(Program* _program) : program(_program), currentPowerUp(nullptr)
{
}

void PowerUpManager::PickRandomPowerUp(const sf::Vector2f& position)
{
	if (!blocked)
	{
		FreeMemory();
		currentPowerUp = new AddHealth(program, position);
		blocked = true;
	}
}

void PowerUpManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(currentPowerUp != nullptr)
		target.draw(*currentPowerUp);
}

void PowerUpManager::Update(float& dt)
{
	if (currentPowerUp != nullptr)
		currentPowerUp->Update(dt);
}

void PowerUpManager::FreeMemory()
{
	if (currentPowerUp != nullptr)
	{
		delete currentPowerUp;
		currentPowerUp = nullptr;
		blocked = false;
	}
}