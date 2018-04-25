#pragma once

#include <memory>

#include <SFML/Graphics.hpp>


//#include "ScreenManager.h"

#include "GameScreen.h"
#include "GameObject.h"

class SpriteRenderComponent;

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

		GameObject* background;
		GameObject* ground;
		GameObject* player;
		GameObject* player2;
		GameObject* shield;

	protected:

	private:
		sf::Text text;
		sf::Font font;
		
};

