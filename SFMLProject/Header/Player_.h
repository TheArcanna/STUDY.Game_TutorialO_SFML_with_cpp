
#include <SFML/Graphics.hpp>
#include "Header/Animation_.h"
#include "Header/Collider.h"
#pragma once
class Player_
{
public:

	Player_(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

	void Update(float deltaTime);

	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }

	Collider GetCollider() { return Collider(body); }

public:
	sf::RectangleShape body;
	Animation_ bodyTextureAnimation;

private:

	float speed;
	int row;
	bool FLIP;

};

