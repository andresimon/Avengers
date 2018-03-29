#pragma once

//#include <iostream>
//#include <string>

#include "SFML/Graphics.hpp"

#include "InputManager.h"
#include "FileManager.h"

class GameScreen
{
	public:
		GameScreen();
		~GameScreen();

		virtual void LoadContent();
		virtual void UnloadContent();
		
		virtual void UpdateEvent(sf::Event event);
		virtual void Update(double deltaTime);

		virtual void Draw(sf::RenderWindow &window);

	protected:
		InputManager input;
		std::vector<sf::Keyboard::Key> keys;

		FileManager file;
		std::vector<std::vector<std::string> > attr;
		std::vector<std::vector<std::string> > content;

};

