#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow) 
{
	sf::Texture image;

	if (image.loadFromFile("../../../Assets/images/Avengers_Logo_00.png") != true) 
	{
		return;
	}
	sf::Sprite sprite(image);

	renderWindow.draw(sprite);

	// Declare and load a font
	sf::Font font;
	font.loadFromFile("../../../Assets/fonts/American Captain.ttf");
	
	sf::Text text("Checking System Resource ...", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);

	float posX = (renderWindow.getSize().x - text.getLocalBounds().width) / 2; // centered
	float posY = renderWindow.getSize().y - 50;
	text.setPosition(posX, posY);
	renderWindow.draw(text);

	renderWindow.display();

	Phantom::Delay(3.0f);

	sf::Event event;
	while (Phantom::_mainWindow.isOpen() && Phantom::_gameState == Phantom::GameState::CheckingResources)
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