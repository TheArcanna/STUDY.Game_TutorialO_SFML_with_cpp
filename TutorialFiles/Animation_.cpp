
#include <SFML/Graphics.hpp>
#include "Animation_.h"

Animation_::Animation_(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	this->totalTime = 0.0f;
	currentImage = sf::Vector2u(0,0);

	int frameWidth = (texture->getSize().x) / (imageCount.x);
	int frameHeight = (texture->getSize().y) / (imageCount.y);

	uvRect.size = sf::Vector2i(frameWidth, frameHeight);	
}


void Animation_::Update(int row, float deltaTime, bool FLIP)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime) 
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) 
			currentImage.x = 0;
	}

	uvRect.position.y = (currentImage.y * uvRect.size.y);
	int frameWidth = std::abs(uvRect.size.x);
	if (FLIP) {
		uvRect.position.x = ((currentImage.x + 1) * frameWidth);
		uvRect.size.x = -frameWidth;
	}
	else {
		uvRect.position.x = (currentImage.x  * frameWidth);
		uvRect.size.x = frameWidth;
	}

}
