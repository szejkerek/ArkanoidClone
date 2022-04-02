#pragma once
#include "SFML/Graphics.hpp"

inline sf::Vector2f MultipyVectors(sf::Vector2f vectorA, sf::Vector2f vectorB)
{
	return  sf::Vector2f(vectorA.x * vectorB.x, vectorA.y * vectorB.y);
}

struct ScreenRelativeConstrains 
{
	float maxRight = 0;
	float maxLeft = 0;
	float maxUp = 0;
	float maxDown = 0;
};