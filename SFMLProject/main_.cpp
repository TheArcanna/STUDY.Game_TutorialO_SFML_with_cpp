#include <SFML/Graphics.hpp>
#include <iostream>
#include "Header/Player_.h"
#include "Header/Animation_.h"
#include "Header/constant.h"
#include "Header/Platform.h"

static const float playerView_Height = 1024.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	// only changed width becoz the height remains constat even after resize
	float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	view.setSize(sf::Vector2f(playerView_Height * aspectRatio, playerView_Height));
}


int main() {

	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_SIZE)), "Ping Pong", sf::Style::Default, sf::State::Windowed);
	sf::View playerView(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_SIZE));


	sf::Texture playerBodyTexture;
	playerBodyTexture.loadFromFile("./Texture/skeleton.png");

	Player_ player(&playerBodyTexture, sf::Vector2u(6, 6), 0.3f, 100);

	Platform platform1(nullptr, sf::Vector2f(400, 200), sf::Vector2f(512, 200));
	Platform platform2(nullptr, sf::Vector2f(400, 200), sf::Vector2f(512, 0));

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
			else if (const auto keyPress = evnet->getIf<sf::Event::TextEntered>()) {
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

		platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
		platform2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);


		playerView.setCenter(player.GetPosition());
		//	Clearing

		window.clear(sf::Color::Black);
		//	Drawing
		window.setView(playerView);
		platform2.Draw(window);
		platform1.Draw(window);
		player.Draw(window);
		//	Displaying
		window.display();

	}

	return 0;
}