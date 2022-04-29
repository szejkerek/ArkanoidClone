#pragma once
#include "Entity.h"
#include "Utility.h"
#include "Bricks.h"
class Ball : public EntityCircle
{
private:

	//Variables
	sf::FloatRect playgroundCollider;
	sf::Vector2f ballToVausOffset;
	sf::Vector2f direction;
	bool stickedToVaus;
	float speed;

	//Collisions
	void UpdateCollistions();
	void UpdateWallCollisions();
	void UpdateBricksCollision();
	void UpdateVausCollision();
	void UpdateBrickCollision(IBrick* brick ,sf::FloatRect& overlap);

	//Move
	void Move(float& deltaTime);
	void Move(sf::Vector2f moveToVector);

	//Methods
	void StickedBallLogic();

public:
	//Constructors & Destructors
	Ball(Game* game);
	void SetPlaygroundConstrains(const sf::FloatRect& _playgroundConstrains);

	//Methods
	void ChangeDirection(sf::Vector2f newDirection);
	void StickBallToVaus();
	
	void InitGameObject(const float& _speed);

	//SFML Methods
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float& dt);
};

