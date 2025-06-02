#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"

int main() {

	// create a render window { Width, Height } => { x, y }
	sf::RenderWindow window(sf::VideoMode({ 1024,1024 }), "Ping Pong", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

	//	creating a rectangle becoz
			//we can simply specify height,width & give it texture & using trasperancy we can make it however shape we want

/* Before Body 

	sf::RectangleShape player(sf::Vector2f( 66.67f, 110.167f ));
	//player.setFillColor(sf::Color::Green);
	//	setting Origin as Centre of Box, for mouse movement
	player.setOrigin(sf::Vector2f( 50.0f,50.0f ));
	player.setPosition(sf::Vector2f( 512.0f, 512.0f ));

	
*/

/* SIMPLE_TEXTURING
		sf::Vector2u playerTextureSize = playerTexture.getSize();

		playerTextureSize.x /= 3;
		playerTextureSize.y /= 2;

	//	sf::Vector2i playerTextureSize_box  ( static_cast<int>(playerTextureSize.x) / 3, static_cast<int>(playerTextureSize.y) / 2 );

		player.setTextureRect(sf::IntRect(sf::Vector2i( static_cast<int>(playerTextureSize.x * 1) ,0 ), sf::Vector2i(playerTextureSize)));
		
*/
/* ANIMATION (via dynamic textures)
*/
//	setting Texture 
/*
	sf::RectangleShape Rect({ (549.0f / 3), (367.0f / 3) });

	Rect.setOrigin({ (Rect.getSize().x / 2), (Rect.getSize().y / 2) });
	Rect.setPosition({ 512.0f, 512.0f });

	sf::Texture rectTexture;
	rectTexture.loadFromFile("./Texture/gather.png");
	Rect.setTexture(&rectTexture);

	Animation rectAni(&rectTexture, sf::Vector2u( 3,2 ), 0.5f);
*/

// Player_text..
	sf::Texture playerTexture;
	playerTexture.loadFromFile("./Texture/skeleton.png");

	Player player(&playerTexture, sf::Vector2u( 6,6 ), 0.1f, 100);


	float deltaTime;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		// what is the use of pollEvent in diff to sfml2 & sfml3 ?
		while (const std::optional<sf::Event> evnt = window.pollEvent())
		{
			//	std::cout << "Event type: " << typeid(*evnt).name() << std::endl;

// Basics
			if (evnt->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto* newSizeofWindow = evnt->getIf<sf::Event::Resized>()) {

				size_t newWidth = newSizeofWindow->size.x;
				size_t newHeight = newSizeofWindow->size.y;

				std::cout << "New WindowSize : " << newWidth << "x" << newHeight << std::endl;
			}
			else if (const auto* txet = evnt->getIf<sf::Event::TextEntered>()) {

				// ASCII Char. (Thestandard 7-bit ASCII Range in UNICODE)
				if (txet->unicode < 128) {
					std::cout << static_cast<char>(txet->unicode) << "\n";
				}
			}

// Basics Ended

// Keyboard Movement
/*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
				std::cout << " -W- ";
				player.move( sf::Vector2f({ 0, -1 }) );
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
				std::cout << " -A- ";
				player.move( sf::Vector2f({ -1, 0 }) );
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
				std::cout << " -S- ";
				player.move( sf::Vector2f({ 0, 1 }) );
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
				std::cout << " -D- ";
				player.move( sf::Vector2f({ 1, 0 }) );
			}
*/

// Mouse Movement
/*
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				player.setPosition(sf::Vector2f(mousePos));
				//	player.setPosition({ static_cast<float> (mousePos.x), static_cast<float> (mousePos.y) });
			}
*/

			std::cout << "+";
		}
		

		player.Update(deltaTime);

//Clearing
		window.clear(sf::Color::Black);

//Drawing
		player.draw(window);
//Display
		window.display();

	}
	return 0;
}
/*
	1. Two Buffer Working:

		- *Back Buffer* : This is an off-screen buffer where all the drawing operations for the current frame take place.
					You draw your sprites, shapes, text, etc., onto this buffer.
		- *Front Buffer* : This is the buffer that is currently being displayed on the screen.

		- Swapping (via window.display() in SFML): When you call window.display() in SFML, it essentially swaps the roles of the front and back buffers.
				The back buffer, which now contains the complete rendered frame, becomes the front buffer and is displayed.
				The old front buffer becomes the new back buffer, ready for the next frame's drawing.

	This process ensures that the user only sees fully rendered frames, preventing issues
		where a partially drawn image might be displayed, leading to a "tearing" effect.


	```
		window.draw(player)
		window.display();
	```
*/
/*
	2. window.clear()

	The provided text explains a common issue in game development where objects appear to "drag" or leave trails when they move. 
		This happens because the screen isn't being cleared before each new frame is drawn. 
		The solution is to call window.clear() at the beginning of each frame, before drawing anything else. 
		This resets the screen, preventing the overlapping of previous frames and resulting in smooth movement
	
	```
		window.clear();
	```

*/
/* KEYBOARD
//		the left_top Position is { 0.0f, 0.0f }

	1.	event->getIf<sf::Event::KeyPressed>()
		
		Event-based input, When key first goes down (one-time event)
		Use case -> Menu Trigger, One-Shot Trigger, AUDIO..

```
	if (const auto* keyPressed = evnt->getIf<sf::Event::KeyPressed>()) {

			auto keyscancode = keyPressed->scancode;
			if (keyscancode == sf::Keyboard::Scancode::W) {
				std::cout << " -W- ";
				player.move({0,-1});
			}
	}
```


	2.	sf::Keyboard::isKeyPressed(...)
	
		Real-time input, While key is held down (continuous)
		Use Case -> Character Movement..

```
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
			std::cout << " -W- ";
			player.move({ 0,-1 });
		}
```
*/
/* KEYS
	in SFML 3, when you press a key, you may see four different event types depending on context and configuration.

	sf::Event::KeyPressed
	sf::Event::KeyReleased
	sf::Event::TextEntered
	sf::Event::KeyboardUpdated -> maybe 
*/
/* MOUSE
```
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		player.setPosition(sf::Vector2f (mousePos));
	//	player.setPosition({ static_cast<float> (mousePos.x), static_cast<float> (mousePos.y) });
			}
```
	return_type = sf::vector2i
	sf::Mouse::getPosition() -> Get the current position of the mouse in desktop coordinates.
	sf::Mouse::getPosition(const WindowBase &relative_to) -> Get the current position of the mouse in window coordinates.
*/
/*	
	sf::IntRect(left, top, width, height) defines the rectangle area in the texture's coordinate space (pixels).

		left and top = top-left corner (x, y)
		width and height = size of the cropped area
*/

/* ANIMATION !)!
	1. Idle Animation
	2. Walking Animation (left,right) -> can flip
*/