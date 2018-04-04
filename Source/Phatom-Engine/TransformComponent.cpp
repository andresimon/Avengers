#include "TransformComponent.h"

void TransformComponent::move(float x, float y)
{
	this->position = sf::Vector2f(x, y);
}
