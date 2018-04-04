#pragma once

#include <SFML/Graphics.hpp>

#include "BaseComponent.h"

class TransformComponent : public BaseComponent
{
	public:
		TransformComponent(sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f)) : BaseComponent()
		{
			this->position = pos;
		}

		void move(float x, float y);

		inline sf::Vector2f getPosition() const { return position; }
		inline sf::Vector2f getRotation() const { return rotation; }
		inline sf::Vector2f getScale() const { return scale; }
		inline TransformComponent* GetTransform() { return this; }

	private:
		sf::Vector2f position;
		sf::Vector2f rotation;
		sf::Vector2f scale;

};
