#pragma once

#include <Windows.h>
#include <ctime>

//#include <stdio.h>

//#include <iostream>
//#include <direct.h>
//#include <locale>  
//#include <iomanip>  
//#include <intrin.h>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

#include "SystemRequirements.h"
#include "ScreenManager.h"
#include "GameObjectManager.h"
#include "SpriteRender.h"

class Phantom
{
	public:
		static void InitGraphics(LPCTSTR gameTitle, float width, float height);

		static void Start(LPCTSTR gameTitle, float ScreenWidth, float ScreenHeight);
		static void Initialize(LPCTSTR gameTitle, float screenWidth, float screenHeight);

		static void Delay(float seconds);

		enum GameState {
			Uninitialized, CheckingResources, Initialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting
		};

		static GameState _gameState;
		
		static GameObjectManager _gameObjectManager;

		static sf::RenderWindow _mainWindow;

	private:
		static bool IsExiting();

		static void GameLoop(float ScreenWidth, float ScreenHeight);

		static sf::Clock clock;

};

/*
#include <stdio.h>
#include <iostream>
#include "GameObjectManager.hpp"

class Clarity
{
public:

private:
	static void LevelLoaded();


	//System Instances
	//static sf::RenderWindow _mainWindow;
};
*/
