#include "LevelSelectorScene.h"
#include "../Program.h"
#include "../Utility/Utility.h"

void LevelSelectorScene::CreateButtnos()
{
	backToMenuBtn = new Button(program);
	playBtn = new Button(program);
	nextStageBtn = new Button(program);
	previousStageBtn = new Button(program);
}

void LevelSelectorScene::LayoutButtons()
{
	sf::Vector2f window = static_cast<sf::Vector2f>(PixelSizes::GetInstance().windowResolution);
	float screenMargin = 0;
	float buttonPadding = 150;

	backToMenuBtn->PlaceOnScene({ screenMargin + backToMenuBtn->GetSize().x, window.y - backToMenuBtn->GetSize().y - screenMargin }, ButtonType::RectangleMedium, "Back", 30, Scenes::Menu);
	playBtn->PlaceOnScene({ window.x / 2, window.y - playBtn->GetSize().y - screenMargin }, ButtonType::RectangleBig, "Play", 55);
	nextStageBtn->PlaceOnScene({ window.x / 2 + buttonPadding, screenMargin + nextStageBtn->GetSize().y }, ButtonType::squareMedium, ">", 25);
	previousStageBtn->PlaceOnScene({ window.x / 2 - buttonPadding,screenMargin + previousStageBtn->GetSize().y }, ButtonType::squareMedium, "<", 25);

	nextStageBtn->SetOnClickFunction(std::bind(&LevelSelectorScene::IncrementIndex, this));
	previousStageBtn->SetOnClickFunction(std::bind(&LevelSelectorScene::DecrementIndex, this));
	playBtn->SetOnClickFunction(std::bind(&LevelSelectorScene::LoadGame, this));
}

void LevelSelectorScene::LayoutText()
{
	indexText = new TextElement(program);
	stageTypeText = new TextElement(program);
	sf::Vector2f window = static_cast<sf::Vector2f>(PixelSizes::GetInstance().windowResolution);
	indexText->SetTextPosition({ window.x / 2, 20 });
	stageTypeText->SetTextPosition({ window.x / 2, 80 });
}

LevelSelectorScene::LevelSelectorScene(Program* _program) : Scene(_program)
{
	backgroundBehind.setSize(static_cast<sf::Vector2f>(PixelSizes::GetInstance().windowResolution));
	backgroundBehind.setTexture(ResourceManager::Get().GetTexture("backgroundMenu"));
	CreateButtnos();
	LayoutText();
}

LevelSelectorScene::~LevelSelectorScene()
{
	FreeMemory();
}


void LevelSelectorScene::SetUpScene()
{
	sf::Vector2f window = static_cast<sf::Vector2f>(PixelSizes::GetInstance().windowResolution);
	preview.setSize({ 733, 876 });
	preview.setTextureRect(sf::IntRect({ 0,0 }, { 733, 876 }));
	preview.setScale(preview.getScale() * 0.8f);
	preview.setOrigin(preview.getSize().x / 2, preview.getSize().y / 2);
	preview.setPosition({ window.x / 2,window.y / 2 });

	LayoutButtons();
	ChoosePreviewImage();
}

void LevelSelectorScene::IncrementIndex()
{
	if (currentIndex < stages.size() - 1)
		currentIndex++;

	
	ChoosePreviewImage();
}

void LevelSelectorScene::DecrementIndex()
{
	if (currentIndex > 0)
		currentIndex--;

	ChoosePreviewImage();
}

void LevelSelectorScene::LoadGame()
{
	LoadStages();

	if (stages[currentIndex] != nullptr)
	{
		program->game->SelectStage(stages[currentIndex]);
		program->sceneManager->LoadScene(Scenes::Game);

	}
	else
	{
		preview.setTexture(ResourceManager::Get().GetTexture("StageNotFound"));
	}

}

void LevelSelectorScene::ChoosePreviewImage()
{
	stageTypeText->SetText(std::to_string(currentIndex + 1) + "/" + std::to_string(levelsCount), 20, sf::Color::White);

	if (currentIndex == 0)
		previousStageBtn->Disable();
	else
		previousStageBtn->Enable();


	if (currentIndex == stages.size() - 1)
		nextStageBtn->Disable();
	else
		nextStageBtn->Enable();

	if (stages[currentIndex] != nullptr)
	{
		playBtn->Enable();
		preview.setTexture(stages[currentIndex]->GetPreview());
		
	}
	else
	{
		playBtn->Disable();
		preview.setTexture(ResourceManager::Get().GetTexture("StageNotFound"));
	}
}

void LevelSelectorOriginal::LoadStages()
{
	for (auto stage : stages)
	{
		if (stage != nullptr)
			delete stage;
	}
	stages.clear();

	levelsCount = 33; 

	for (int i = 0; i < levelsCount; i++) 
	{
		Stage* tempStage = new Stage(i, program);
		if (tempStage->LoadedSucessfuly())
		{
			stages.push_back(tempStage);
		}
		else
		{
			delete tempStage;
			stages.push_back(nullptr);
		}
	}

}


LevelSelectorOriginal::LevelSelectorOriginal(Program* _program) : LevelSelectorScene(_program)
{
	LoadStages();
	SetUpScene();
	indexText->SetText("Original stages", 12, sf::Color::White);
	stageTypeText->SetText(std::to_string(1) + "/" + std::to_string(levelsCount), 20, sf::Color::White);

}

void LevelSelectorScene::Update(float& dt)
{
	backToMenuBtn->Update(dt);
	playBtn->Update(dt);
	nextStageBtn->Update(dt);
	previousStageBtn->Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		LoadGame();
}

void LevelSelectorScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundBehind);
	target.draw(*backToMenuBtn);
	target.draw(*playBtn);
	target.draw(*nextStageBtn);
	target.draw(*previousStageBtn);
	target.draw(preview);
	target.draw(*indexText);
	target.draw(*stageTypeText);
}

void LevelSelectorScene::FreeMemory()
{	
	delete backToMenuBtn;
	delete playBtn;
	delete nextStageBtn;
	delete previousStageBtn;
	delete indexText;
	delete stageTypeText;

	for (auto stage : stages)
	{
		if (stage != nullptr)
			delete stage;
	}
	stages.clear();
}

void LevelSelectorScene::ResetIndex()
{
	currentIndex = 0;
	ChoosePreviewImage();
}

int LevelSelectorScene::GetIndex()
{
	return currentIndex;
}