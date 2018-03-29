#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::LoadContent()
{
	if (!font.loadFromFile("../../../Assets/fonts/American Captain.ttf"))
		std::cout << "Could not find the specified font " << std::endl;

	//text = "TitleScreen";

	//text.setString("Title Screen");
	//text.setFont(font);

	keys.push_back(sf::Keyboard::Z);
	keys.push_back(sf::Keyboard::Return);

	menu.LoadContent("Title");
}

void TitleScreen::UnloadContent()
{
	GameScreen::UnloadContent();

	menu.UnloadContent();
}

/*
void TitleScreen::Update(sf::RenderWindow &window, sf::Event event)
{
	input.Update(event);

	if (input.KeyPressed(keys))
	{
		ScreenManager::GetInstance().AddScreen(new SplashScreen2);
	}
}
*/

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
/*
	sf::Text text(text, font);
	text.setCharacterSize(30);
	//text.setStyle(sf::Text::Bold);
	text.setPosition(0, 0);
	*/

	window.draw(text);

	menu.Draw(window);
}

