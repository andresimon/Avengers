#pragma once

//#include <string>
//#include <iostream>

#include "ScreenManager.h"
#include "GameScreen.h"

#include "SplashScreen2.h"
#include "TitleScreen.h"
#include "LevelScreen.h"

#include "FadeAnimation.h"
#include "FileManager.h"

//#define ScreenWidth 800
//#define ScreenHeight 600

class ScreenManager
{
	public:
		~ScreenManager();
		static ScreenManager &GetInstance();

		void Initialize();

		void LoadContent();
		void UnloadContent();

		//void Update(sf::RenderWindow &window, sf::Event event);
		void UpdateEvent(sf::Event event);
		void Update(double deltaTime);

		void Draw(sf::RenderWindow &window);

		void AddScreen(GameScreen *screen);
		double GetAlpha();

	
	private:
		//GameScreen *currentScreen, *newScreen;

		ScreenManager();
		ScreenManager(ScreenManager& const);
		void operator=(ScreenManager& const);

		//std::string text;

		void Transition(double deltaTime);

		bool transitiond;
		FadeAnimation fade;

		GameScreen* newScreen;
		FileManager file;

		std::vector<std::vector<std::string> > attributes;
		std::vector<std::vector<std::string> > contents;
};

