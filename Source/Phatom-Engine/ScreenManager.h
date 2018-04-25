#pragma once

//#include <string>
//#include <iostream>

#include "ScreenManager.h"
#include "GameScreen.h"

#include "../Avengers/SplashScreen2.h"
//#include "../Avengers/TitleScreen.h"
#include "../Avengers/LevelScreen.h"

#include "FadeAnimation.h"
#include "FileManager.h"

class ScreenManager
{
	public:
		~ScreenManager();
		static ScreenManager &GetInstance();

		void Initialize();

		void LoadContent();
		void UnloadContent();

		void UpdateEvent(sf::Event event);
		void Update(float deltaTime);

		void Draw(sf::RenderWindow &window);

		void AddScreen(GameScreen *screen);
		double GetAlpha();

	
	private:
		//GameScreen *currentScreen, *newScreen;

		ScreenManager();
		ScreenManager(ScreenManager& const);
		void operator=(ScreenManager& const);

		void Transition(double deltaTime);

		bool transitiond;
		FadeAnimation fade;

		GameScreen* newScreen;
		FileManager file;

		std::vector<std::vector<std::string> > attributes;
		std::vector<std::vector<std::string> > contents;
};

