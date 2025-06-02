#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player_.h"
#include "Animation_.h"
#include "constant.h"

static const float playerView_Height = 1024.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) 
{
	// only changed width becoz the height remains constat even after resize
	float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	view.setSize(sf::Vector2f(playerView_Height*aspectRatio, playerView_Height));
}


int main() {

	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_SIZE)), "Ping Pong", sf::Style::Default, sf::State::Windowed);
	sf::View playerView(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_SIZE));
	

	sf::Texture playerBodyTexture;
	playerBodyTexture.loadFromFile("./Texture/skeleton.png");

	Player_ player(&playerBodyTexture, sf::Vector2u(6,6), 0.3f, 100);




	float deltaTime;
	sf::Clock clock;
	while (window.isOpen()) 
	{
		deltaTime = clock.restart().asSeconds();

//	BasicEvents Checks
		while (std::optional<sf::Event> evnet = window.pollEvent()) 
		{
			if (evnet->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto keyPress=evnet->getIf<sf::Event::TextEntered>()){
				std::cout << static_cast<char>(keyPress->unicode) << "\n";
			}
			else if (evnet->is<sf::Event::Resized>()) {
				ResizeView(window, playerView);
			}

//	MOUSE KEYS
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				player.body.setPosition(sf::Vector2f(mousePosition));
			}


			std::cout << "+";
		}
//	BasicEvent Ended


		player.Update(deltaTime);
		playerView.setCenter(player.GetPosition());
//	Clearing

		window.clear(sf::Color::Black);
//	Drawing
		window.setView(playerView);
		player.Draw(window);
//	Displaying
		window.display();

	}

	return 0;
}