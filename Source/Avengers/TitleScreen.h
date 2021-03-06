#pragma once

#include "SFML/Graphics.hpp"

#include "../Phatom-Engine/ScreenManager.h"

#include "MenuManager.h"

class TitleScreen : public GameScreen
{
	public:
		TitleScreen();
		~TitleScreen();

		void LoadContent();
		void UnloadContent();

		void UpdateEvent(sf::Event event);
		void Update(double deltaTime);

		void Draw(sf::RenderWindow &window);

	private:

		sf::Text text;
		sf::Font font;

		MenuManager menu;
};

