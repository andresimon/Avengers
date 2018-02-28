#include "Phantom.h"

bool Phantom::Initialize(LPCTSTR gameTitle)
{
	return SystemRequirements::CheckResources(gameTitle);
}

void Phantom::Start(LPCTSTR gameTitle)
{
	if (_gameState != Uninitialized)
		return;

	//_mainWindow.create(sf::VideoMode(1024, 768, 32), gameTitle);

	_gameState = Phantom::Playing;

	while (!IsExiting())
	{
		GameLoop();
	}
	_mainWindow.close();
}

void Phantom::InitGraphics(LPCTSTR gameTitle, float width, float height)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(width, height, 32), gameTitle);
}

bool Phantom::IsExiting()
{
	return false;
}

void Phantom::GameLoop() 
{
	SceneGraph* level1 = new SceneGraph();

	GameObject* player = new GameObject();

	level1->AddObject(player);

}

Phantom::GameState Phantom::_gameState;

sf::RenderWindow Phantom::_mainWindow;

void Phantom::Delay(float seconds)
{
	sf::Clock clock; // starts the clock

	clock.restart();

	float time = 0;
	float ElapsedTime = 0;
	clock.restart();

	while ( time < seconds )
	{
		// Reset the clock
		time += clock.restart().asSeconds();
	}
}

