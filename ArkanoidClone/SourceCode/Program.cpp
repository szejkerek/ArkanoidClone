#include "Program.h"
#include "Utility/Utility.h"
Program::Program() : game (new Game(this, deltaTime)), sceneManager(new SceneManager(this)), menu (new MenuScene(this))
{
	int screenWidth  = PixelSizes::GetInstance().windowResolution.x;
	int screenHeight = PixelSizes::GetInstance().windowResolution.y;
	InitializeWindow(screenWidth, screenHeight, windowTitle);
	sceneManager->LoadScene(Scenes::Menu);
}

Program::~Program()
{
	delete sceneManager;
	delete menu;
	delete game;
	delete window;
}

void Program::InitializeWindow(unsigned int width, unsigned int height, std::string title)
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
	window->setPosition(PixelSizes::GetInstance().windowPosition);
	//window->setVerticalSyncEnabled(false); - ENABLE ONLY WHEN BOOST GAMEPLAY
	//window->setFramerateLimit(60 or 144); - ENABLE THIS ON FINAL BUILD
}

void Program::CalculateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}

void Program::UpdateEvents()
{	
	while (window->pollEvent(this->sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			profiler.SaveProfile();
			window->close();
		}
	}
}

void Program::Update()
{
	UpdateEvents();
	CalculateDeltaTime();

	sceneManager->Update(deltaTime);
}

void Program::Render()
{
	window->clear(backgroundColor);

	window->draw(*sceneManager);
	
	window->display();
}

void Program::Run()
{
	//Main game loop
	while (window->isOpen())
	{
		Update();
		Render();
		profiler.Update(); //REMOVE ON FINAL BUILD
	}
}