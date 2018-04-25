#pragma once

#include <SFML/Graphics.hpp>

#include "Matrices.h"

#include "BaseComponent.h"

class TransformComponent : public BaseComponent
{
	public:
		TransformComponent(sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f)) : BaseComponent()
		{
			this->position = pos;
			this->transform.translate(pos.x, pos.y, 0);
		}

		void move(float x, float y);

		//	inline sf::Vector2f getPosition() const { return position; }
		sf::Vector2f const getPosition(); 
		inline sf::Vector2f getRotation() const { return rotation; }
		inline sf::Vector2f getScale() const { return scale; }
		//	inline TransformComponent* GetTransform() { return this; }
		inline Matrix4 GetTransform() { return transform; }
		inline Matrix4 GetWorldTransform() { return worldTransform; }

		void Update(float deltaTime);

	protected:
		//sf::Transform transform;
		Matrix4 transform;
		Matrix4 worldTransform;

	private:
		sf::Vector2f position;
		sf::Vector2f rotation;
		sf::Vector2f scale;

		

};
