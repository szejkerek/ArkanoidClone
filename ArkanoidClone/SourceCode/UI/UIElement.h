#pragma once
#include "SFML/Graphics.hpp"
#include "../Scenes/Scene.h"

class Program;

class UIElement : public sf::Drawable
{
public:
	Program* program;
	UIElement(Program* program);
	virtual ~UIElement() = default;

	virtual inline void InitGameObject();
	virtual inline void SetTexture(sf::Texture * texture);
	virtual inline void SetPosition(const sf::Vector2f & position);
	virtual inline void SetSize(const sf::Vector2f & size);
	virtual inline void SetFillColor(const sf::Color & color);
	virtual inline void SetOriginCenter();
	virtual inline void SetOutlineThickness(const float& size);
	virtual inline void SetOutlineColor(const sf::Color & color);
	virtual inline sf::FloatRect GetCollider();
	virtual inline sf::Vector2f GetPosition();
	virtual inline bool MouseHovers();
	virtual inline sf::Vector2f GetSize();
	virtual inline void Disable();
	virtual inline void Enable();
	virtual void Update(float& dt);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override = 0;

protected:
	sf::RectangleShape gameObject;
	bool isDisabled = false;
};

