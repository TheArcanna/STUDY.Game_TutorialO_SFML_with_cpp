#include <SFML/Graphics.hpp>
#pragma once

class Animation
{
public:
	Animation(sf::Texture *texture, sf::Vector2u ImageCount, float switchTime);
	~Animation();

	void Update(int row, float deltaTime, bool faceChange);



public:
	sf::IntRect uvRect;
private:
	sf::Vector2u ImageCount;
	sf::Vector2u currentImage;

// To control SpeedOfAnimation
	float totalTime;
	float switchTime;
};

