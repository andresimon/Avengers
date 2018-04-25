#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
	Phantom::_gameState = Phantom::ShowingMenu;
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::LoadContent()
{
	if (!font.loadFromFile("../../../Assets/fonts/American Captain.ttf"))
		std::cout << "Could not find the specified font " << std::endl;

	keys.push_back(sf::Keyboard::Z);
	keys.push_back(sf::Keyboard::Return);

	menu.LoadContent("Title");
}

void TitleScreen::UnloadContent()
{
	GameScreen::UnloadContent();

	menu.UnloadContent();
}

void TitleScreen::UpdateEvent(sf::Event event)
{
	if (input.KeyPressed(keys) && menu.GetItem() == 0)
		ScreenManager::GetInstance().AddScreen(new LevelScreen);

	input.Update(event);

	menu.UpdateEvent(input);
}

void TitleScreen::Update(double deltaTime)
{
	menu.Update(deltaTime);
}

void TitleScreen::Draw(sf::RenderWindow & window)
{
	window.draw(text);

	menu.Draw(window);
}

