#include "ScreenManager.h"

GameScreen *currentScreen, *newScreen;

ScreenManager::ScreenManager()
{
}

void ScreenManager::operator=(ScreenManager & const)
{
}

ScreenManager::~ScreenManager()
{
}

ScreenManager &ScreenManager::GetInstance()
{
	static ScreenManager instance;
	return instance;
}

void ScreenManager::Initialize()
{
	//currentScreen = new LevelScreen();
	currentScreen = new SplashScreen2();
	
	transitiond = false;
	//file.loadContent("load/splash.txt", attributes, contents);

}

void ScreenManager::LoadContent()
{
	currentScreen->LoadContent();

	sf::Image image;
	sf::Vector2f pos;

	fade.LoadContent("", image, pos);
	fade.SetAlpha(0.0);
}

void ScreenManager::UnloadContent()
{

}

/*
void ScreenManager::Update(sf::RenderWindow &window, sf::Event event)
{
	currentScreen->Update(window, event);
}
*/

void ScreenManager::UpdateEvent(sf::Event event)
{
	currentScreen->UpdateEvent(event);
}

void ScreenManager::Update(float deltaTime)
{
	if (!transitiond)
		currentScreen->Update(deltaTime);

	Transition(deltaTime);
}

void ScreenManager::Draw(sf::RenderWindow & window)
{
	currentScreen->Draw(window);
}

void ScreenManager::AddScreen(GameScreen * screen)
{
	/*
	currentScreen->UnloadContent();
	delete currentScreen;

	currentScreen = screen;
	currentScreen->LoadContent();
	*/

	transitiond = true;
	newScreen = screen;
	fade.SetValue(fade.GetActive(), true);
	fade.SetAlpha(0.0);
}

double ScreenManager::GetAlpha()
{
	return fade.GetAlpha();
}

void ScreenManager::Transition(double deltaTime)
{
	if (transitiond)
	{
		fade.Update(deltaTime);
		if (fade.GetAlpha() >= 1.0)
		{
			currentScreen->UnloadContent();
			delete currentScreen;
			currentScreen = newScreen;
			currentScreen->LoadContent();
			newScreen = NULL;
		}
		else if (fade.GetAlpha() <= 0.0)
		{
			transitiond = false;
			fade.SetValue(fade.GetActive(), false);
		}
	}
}




