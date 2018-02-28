#pragma once

#include <Windows.h>

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
#include "SceneGraph.h"

class Phantom
{
	public:
		static void InitGraphics(LPCTSTR gameTitle, float width, float height);

		static void Start(LPCTSTR gameTitle);
		static bool Initialize(LPCTSTR gameTitle);

		static void Delay(float seconds);

		enum GameState {
			Uninitialized, CheckingResources, Initialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting
		};

		static GameState _gameState;

		static sf::RenderWindow _mainWindow;

	private:
		static bool IsExiting();
		static void GameLoop();

		

		
		

	



};
