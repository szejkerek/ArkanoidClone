#pragma once
#include "Scene.h"
#include "../Entity/Stage.h"
#include "../UI/Button.h"
#include "../UI/TextElement.h"

class LevelSelectorScene : public Scene
{
protected:
	std::vector<Stage*> stages;
	sf::RectangleShape preview;
	int currentIndex = 0;
	
	void IncrementIndex();
	void DecrementIndex();
	void LoadGame();
	 
	Button* backToMenuBtn;
	Button* playBtn;
	Button* nextStageBtn;
	Button* previousStageBtn;
	Button* programableSwapStageBtn;

	TextElement* indexText;
	TextElement* stageTypeText;
	
	void SetUpScene();
	void ChoosePreviewImage();
	void CreateButtnos();
	void LayoutButtons();
	void LayoutText();


public:
	virtual void LoadStages() = 0;
	LevelSelectorScene(Program* _program);
	~LevelSelectorScene();

	virtual void Update(float& dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class LevelSelectorOriginal : public LevelSelectorScene
{
public:
	LevelSelectorOriginal(Program* _program);
	virtual void LoadStages();
};

class LevelSelectorCustom : public LevelSelectorScene
{
public:
	LevelSelectorCustom(Program* _program);
	virtual void LoadStages();
};
