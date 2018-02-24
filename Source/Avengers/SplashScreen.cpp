#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow) 
{
	sf::Texture image;

	if (image.loadFromFile("../../../Assets/images/Avengers_Logo.jpg") != true) 
	{
		return;
	}


	sf::Sprite sprite(image);
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	
	while (Phantom::_gameState != Phantom::GameState::Initialized) 
	{
		while (Phantom::_mainWindow.pollEvent(event)) 
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed) {
				return;
			}
		}
	}
}