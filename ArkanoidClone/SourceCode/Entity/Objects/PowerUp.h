#pragma once
#include "SFML/Graphics.hpp"
#include "../Objects/Entity.h"
#include <iostream>

class Program;
class IPowerUp : public EntityRectangle
{
public:
	IPowerUp(Program* _program, const sf::Vector2f& position);

	virtual void ApplyEffect() = 0;
	void Hide();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float& dt);
	
protected:
	Program* program;
	float speed = 250.f;
	float bottomCollider = 0;
	bool effectApplied = false;
	sf::Texture* powerUpTexture;
	sf::IntRect textureRect;
	float timer = 0.06f;
	float defaultTimer = 0.06f;

	void MoveDown(float& dt);
	void CheckForCollisions();
	void Animate(float& dt);
	void ChangeTexture();
};

class AddHealth : public IPowerUp
{
public:
	AddHealth(Program* _program, const sf::Vector2f& position);

	void ApplyEffect();
};

class SplitBall : public IPowerUp
{
public:
	SplitBall(Program* _program, const sf::Vector2f& position);

	void ApplyEffect();
};

class SlowDown : public IPowerUp
{
public:
	SlowDown(Program* _program, const sf::Vector2f& position);

	void ApplyEffect();
}; 
