#include "SplashScreen2.h"

SplashScreen2::SplashScreen2()
{
	Phantom::_gameState = Phantom::ShowingSplash;
}

SplashScreen2::~SplashScreen2()
{
}

void SplashScreen2::LoadContent()
{
	imgNum = 0;

	if (!font.loadFromFile("../../../Assets/fonts/American Captain.ttf"))
		std::cout << "Could not find the specified font " << std::endl;

	//text = "SplashScreen";
	text.setString("Splash Screen");
	text.setFont(font);

	keys.push_back(sf::Keyboard::Z);
	keys.push_back(sf::Keyboard::Return);

	//file.LoadContent("load/splash.txt", attr, content);
	file.LoadContent("../../../Source/Phatom-Engine/load/splash.txt", attr, content);
	for (unsigned i = 0; i < attr.size(); ++i)
	{
		for (unsigned j = 0; j < attr[i].size(); ++j)
		{
			std::string att = attr[i][j];

			if (att == "image")
			{
				sf::Vector2f pos(0, 0);
				image.loadFromFile(content[i][j]);
				//                std::cout << "Content " << content[i][j] << std::endl;
				fade.push_back(new FadeAnimation);
				fade[fade.size() - 1]->LoadContent("", image, pos);
				fade[fade.size() - 1]->SetValue(fade[fade.size() - 1]->GetActive(), true);
				fade[fade.size() - 1]->SetValue(fade[fade.size() - 1]->GetScale(), 1.0);
			}
		}
	}
}

void SplashScreen2::UnloadContent()
{
	GameScreen::UnloadContent();

	for (unsigned i = 0; i < fade.size(); ++i)
	{
		fade[i]->UnloadContent();
		delete fade[i];
	}

	fade.clear();
}

/*
void SplashScreen2::Update(sf::RenderWindow &window, sf::Event event)
{
	input.Update(event);	

	if (input.KeyPressed(keys))
	{
		ScreenManager::GetInstance().AddScreen(new TitleScreen);
	}
}
*/

void SplashScreen2::UpdateEvent(sf::Event event)
{
	input.Update(event);
}

void SplashScreen2::Update(double deltaTime)
{
	if (fade[imgNum]->GetAlpha() <= 0.0)
		imgNum++;

	if (imgNum != fade.size() - 1)
		fade[imgNum]->Update(deltaTime);

	//if (input.KeyPressed(keys) || imgNum >= fade.size() - 1)
	if (input.KeyPressed(keys) )
		ScreenManager::GetInstance().AddScreen(new TitleScreen);
}


void SplashScreen2::Draw(sf::RenderWindow & window)
{
	/*
	sf::Text text(text, font);
	text.setCharacterSize(30);
	//text.setStyle(sf::Text::Bold);
	text.setPosition(0, 0);
	*/

	//window.draw(text);
	fade[imgNum]->Draw(window);
}
