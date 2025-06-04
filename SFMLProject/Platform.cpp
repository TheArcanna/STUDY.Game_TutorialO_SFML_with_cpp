#include "Header/Platform.h"
#include <SFML/Graphics.hpp>
#include "Header/Collider.h"


Platform::Platform(sf::Texture* texture, sf::Vector2f frameSize, sf::Vector2f position) 
{
	body.setSize(frameSize);
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
}


void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
   