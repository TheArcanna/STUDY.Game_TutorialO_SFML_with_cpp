#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
    Collider(sf::RectangleShape& body);
    ~Collider();

    void Move(sf::Vector2f offset) { body.move(offset); }
    bool CheckCollision(Collider& other, float push);

    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
    sf::RectangleShape& body;
};