#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/SceneManager.h"
#include "Utility/Profiler.h"
#include "Scenes/LevelSelectorScene.h"
#include "Scenes/TutorialScene.h"


#include "Utility/Resources.h"
class Program
{
public:
	sf::RenderWindow* window;

	LevelSelectorOriginal* levelSelectorOriginal;
	SceneManager* sceneManager;
	HighScoreManager* highScoreManager;
	TutorialScene* tutorialScene;
	GameScene* game;
	MenuScene* menu;

	Program();
	~Program();

	void CloseWindow();
	void Run();

private:
	const std::string windowTitle = "ArkanoidClone";

	sf::Event sfEvent;
	sf::Color backgroundColor = sf::Color::Black;
	sf::Clock clock;
	float deltaTime;

	Profiler profiler;

	void InitializeWindow(unsigned int width, unsigned int height, std::string title);
	void CalculateDeltaTime();
	void UpdateEvents();
	void Update();
	void Render();
};

