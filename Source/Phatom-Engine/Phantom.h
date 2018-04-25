#pragma once

#include <Windows.h>
#include <ctime>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameObjectManager.h"
#include "PhysicsManager.h"

class Phantom
{
	public:
		static void InitGraphics(LPCTSTR gameTitle, float width, float height);

		static void Start(LPCTSTR gameTitle, float ScreenWidth, float ScreenHeight);
		static void Initialize();
	//	static void Initialize(LPCTSTR gameTitle, float screenWidth, float screenHeight);

		static void Delay(float seconds);

		enum GameState {
			Uninitialized, CheckingResources, Initialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting
		};

		static GameState _gameState;
		
		static GameObjectManager _gameObjectManager;
		static PhysicsManager _physicsManager;

	private:
		static bool IsExiting();

		static void GameLoop(float ScreenWidth, float ScreenHeight, float deltaTime);

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
