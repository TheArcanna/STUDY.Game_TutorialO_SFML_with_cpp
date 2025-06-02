#include "Player.h"
#include "Animation.h"
#include <iostream>
#define WINDOW_CNTR 512.0f

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	bodyAnimation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceChange = true;

	body.setSize(sf::Vector2f(bodyAnimation.uvRect.size));
	
	body.setOrigin(sf::Vector2f( (body.getSize().x)/2, (body.getSize().y)/2 ));
	body.setPosition(sf::Vector2f( WINDOW_CNTR, WINDOW_CNTR));

	body.setTexture(texture);

}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	
	sf::Vector2f movement{ 0.0f, 0.0f };
//		Moves based on deltaTime to keep speed consistent regardless of framerate.

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
		movement.y -= (speed * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
		movement.x -= (speed * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
		movement.y += (speed * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
		movement.x += (speed * deltaTime);

	std::cout <<"Movement :" << movement.x << ", " << movement.y << "\n";

	if (movement.x == 0.0f && movement.y == 0.0f) {
		// No movement - Idle
		row = 0;
	}
	else {
		// Determine direction
		if (movement.x != 0.0f && movement.y != 0.0f) {
			row = 3; // Diagonal movement ( Up+Right)
			faceChange = (movement.x > 0.0f); // Change to (Up+Left)
		}
		else if (movement.x != 0.0f) {
			row = 5; // Horizontal
			faceChange = (movement.x < 0.0f); // true if moving left
		}
		else if (movement.y != 0.0f) {
			if (movement.y < 0.0f)
				row = 2; // Up
			else row = 1; // Down

			faceChange = true; // keep facing forward
		}
	}

	bodyAnimation.Update(row, deltaTime, faceChange);
	body.setTextureRect(bodyAnimation.uvRect);
	body.move(movement);

}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}
