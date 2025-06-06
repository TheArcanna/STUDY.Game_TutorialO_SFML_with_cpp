#include "./Header/Collider.h"
#include <SFML/Graphics.hpp>

Collider::Collider(sf::RectangleShape& body) :
	body(body)
{
}
bool Collider::CheckCollision(Collider other, float push)
{
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = this->GetPosition();
    sf::Vector2f thisHalfSize = this->GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    
    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if (intersectX > intersectY)
        {// x-axis movement
            if (deltaX > 0.0f)
            {
                this->Move(sf::Vector2f(intersectX * (1.0f - push), 0.0f));
                other.Move(sf::Vector2f(-intersectX * push, 0.0f));
            }
            else
            {
                this->Move(sf::Vector2f(-intersectX * (1.0f - push), 0.0f));
                other.Move(sf::Vector2f(intersectX * push, 0.0f));
            }
        }
        else
        {
            if (deltaY > 0.0f)
            {
                Move(sf::Vector2f(0.0f, intersectY * (1.0f - push)));
                other.Move(sf::Vector2f(0.0f, -intersectY * push));
            }
            else
            {
                Move(sf::Vector2f(0.0f, -intersectY * (1.0f - push)));
                other.Move(sf::Vector2f(0.0f, intersectY * push));
            }
        }
        return true;
    }
    return false;
}