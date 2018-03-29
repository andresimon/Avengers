#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update(sf::Event event)
{
	this->event = event;
}

bool InputManager::KeyPressed(sf::Keyboard::Key key)
{
	//return (event.key.code == key && event.type == sf::Event::KeyPressed);
	return (sf::Keyboard::isKeyPressed(key));
}

bool InputManager::KeyPressed(std::vector<sf::Keyboard::Key> keys)
{
	for (unsigned int i = 0; i < keys.size(); i++)
	{
		if ( KeyPressed(keys[i]) ) return true;
	}
	return false;
}

bool InputManager::KeyReleased(int key)
{
	return (event.key.code == key && event.type == sf::Event::KeyReleased);
}

bool InputManager::KeyReleased(std::vector<int> keys)
{

	for (unsigned int i = 0; i < keys.size(); i++)
	{
		if ( KeyReleased(keys[i]) ) return true;
	}
	return false;
}

/*
bool InputManager::KeyDown(sf::RenderWindow &window, int key)
{
	return (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) key));
	//return (window.GetInput().IsKeyDown(key));
}

bool InputManager::KeyDown(sf::RenderWindow &window, std::vector<int> keys)
{

	for (unsigned int i = 0; i < keys.size(); i++)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) keys[i]) )
			//if ( window.GetInput().IsKeyDown(keys[i]) )
			return true;
	}
	return false;
}
*/


