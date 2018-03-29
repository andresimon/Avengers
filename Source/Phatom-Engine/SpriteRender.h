#pragma once

#include <SFML/Graphics.hpp>

#include "Phantom.h"
#include "BaseComponent.h"
#include "FileManager.h"

class SpriteRender : public BaseComponent
{
	public:
		SpriteRender(std::string fileName);
		~SpriteRender() {};

		void Update();

	private:
		sf::Sprite sprite;
		FileManager file;

		std::string fileName;

		void LoadContent();

};
