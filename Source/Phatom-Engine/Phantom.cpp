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

void Phantom::InitGraphics(LPCTSTR gameTitle)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), gameTitle);
}

bool Phantom::IsExiting()
{
	return false;
}

void Phantom::GameLoop() {}

Phantom::GameState Phantom::_gameState;

sf::RenderWindow Phantom::_mainWindow;



