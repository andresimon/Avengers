#pragma once

#include <SFML/Graphics.hpp>

//#include "Phantom.h"
#include "ScreenManager.h"
#include "GameScreen.h"
#include "GameObject.h"
class LevelScreen : public GameScreen
{
	public:
		LevelScreen();
		~LevelScreen();

		void LoadContent();
		void UnloadContent();
		void UpdateEvent(sf::Event event);
		void Update(double deltaTime);
		void Draw(sf::RenderWindow& window);

		GameObject* player;

	protected:

	private:
		sf::Text text;
		sf::Font font;
		
};

