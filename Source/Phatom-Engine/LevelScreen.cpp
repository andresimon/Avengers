#include "LevelScreen.h"

LevelScreen::LevelScreen()
{
	//ctor
}

LevelScreen::~LevelScreen()
{
	//dtor
}

void LevelScreen::LoadContent()
{
	if (!font.loadFromFile("../../../Assets/fonts/American Captain.ttf"))
		std::cout << "Could not find the specified font at LevelScreen.cpp" << std::endl;

	text.setString("First Level");
	text.setFont(font);

	player = Phantom::_gameObjectManager.CreateObject();
	
	SpriteRender spriteRender("images/Avengers_Logo_00.png");
	player->AddComponent(&spriteRender);

}

void LevelScreen::UnloadContent()
{

}

void LevelScreen::UpdateEvent(sf::Event event)
{
	input.Update(event);
	//character.updateEvent(input);
}

void LevelScreen::Update(double deltaTime)
{
	//character.update(deltaTime);
}

void LevelScreen::Draw(sf::RenderWindow& window)
{
	window.draw(text);
	//character.draw(window);
}