#pragma once

#include <SFML/Graphics.hpp>

#include "BaseComponent.h"

class SpriteRenderComponent : public BaseComponent
{
	public:
		SpriteRenderComponent(std::string fileName);
		SpriteRenderComponent(std::string fileName, sf::IntRect rectShape);
		~SpriteRenderComponent() {};

		void Update();
		inline sf::Texture GetTexture() { return texture; }
		inline sf::Sprite GetSprite() { return sprite; }

		void SetScale(float x, float y);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::IntRect rectShape;

		std::string fileName;

		void LoadContent();

		void SetPosition(sf::Vector2f newPos);

};
