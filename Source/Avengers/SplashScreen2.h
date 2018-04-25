#pragma once

#include <SFML/Graphics.hpp>

#include "../Phatom-Engine/Phantom.h"
#include "../Phatom-Engine/ScreenManager.h"
#include "../Phatom-Engine/GameScreen.h"

#include "../Phatom-Engine/FadeAnimation.h"

//#include <iostream>

#include "TitleScreen.h"

class SplashScreen2 : public GameScreen
{
	public:
		SplashScreen2();
		~SplashScreen2();

		void LoadContent();
		void UnloadContent();

		void UpdateEvent(sf::Event event);
		void Update(double deltaTime);

		//void Update(sf::RenderWindow &window, sf::Event event);
		void Draw(sf::RenderWindow &window);

	private:
		//sf::String text;

		sf::Text text;
		sf::Font font;
		sf::Image image;
		std::vector<FadeAnimation*> fade;
		int imgNum;
};

