#include <SFML/Graphics.hpp>
#include "Animation.h"
#pragma once
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u ImageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape body;
	Animation bodyAnimation;
	unsigned int row;
	bool faceChange;
	float speed;
};

