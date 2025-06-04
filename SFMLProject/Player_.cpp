#include<SFML/Graphics.hpp>
#include "Header/Animation_.h"
#include "Header/Player_.h"
#include "Header/constant.h"

Player_::Player_(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float Speed) :
	bodyTextureAnimation(texture, imageCount, switchTime)
{
	this->speed = Speed;
	row = 0;
	FLIP = false;

	sf::Vector2f frameSize(bodyTextureAnimation.uvRect.size);
	body.setSize(frameSize);

	body.setOrigin(sf::Vector2f(body.getSize() / 2.0f));
	body.setPosition(sf::Vector2f(WINDOW_SIZE)/2.0f);
	//body.setFillColor(sf::Color::Green);
	body.setOutlineColor(sf::Color::Red);
	body.setOutlineThickness(1);

	body.setTexture(texture);
}

void Player_::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) 
			movement.y -= (speed * deltaTime);		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) 
			movement.x -= (speed * deltaTime);		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) 
			movement.y += (speed * deltaTime);		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) 
			movement.x += (speed * deltaTime);
		

	if (movement.x == 0.0f && movement.y == 0.0f) {
		row = 0;//Idle
	}
	else {
		//if (movement.x && movement.y) {
		//	row = 3;//diagonal Up only
		//	FLIP = (movement.x < 0.0f);
		//}
		//else
		if (movement.x) {
			row = 5;// left & right
			FLIP = (movement.x > 0.0f);
		}
		else if (movement.y) {
			FLIP = false;
			if (movement.y < 0.0f)	row = 2;//up
			else row = 1;//down
		}
	}

	bodyTextureAnimation.Update(row, deltaTime, FLIP);
	body.setTextureRect(bodyTextureAnimation.uvRect);
	body.move(movement);

}

void Player_::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
