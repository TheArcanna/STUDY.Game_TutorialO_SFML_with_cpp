#include <SFML/Graphics.hpp>
#pragma once

class Animation_
{
public:
	Animation_(sf::Texture* texture, sf::Vector2u imageCount, float switchTime );

	void Update(int row, float deltaTime, bool FLIP);

public:

	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	
	float totalTime;
	float switchTime;
};

