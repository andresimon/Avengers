#include "Phantom.h"

#include "ScreenManager.h"

#include "../Avengers/Application.h"

Phantom::GameState Phantom::_gameState;
GameObjectManager Phantom::_gameObjectManager;
PhysicsManager Phantom::_physicsManager;
sf::Clock Phantom::clock;

/*
void Phantom::Initialize(LPCTSTR gameTitle, float screenWidth, float screenHeight)
{
	Phantom::InitGraphics(gameTitle, screenWidth, screenHeight);
	
	ScreenManager::GetInstance().Initialize();
	ScreenManager::GetInstance().LoadContent();

	if ( !SystemRequirements::CheckResources(gameTitle) )
		exit;

	_gameState = Initialized;

	return;
}
*/

void Phantom::Initialize()
{
	ScreenSize size = Application::GetInstance().size;
	LPCTSTR gameTitle = Application::GetInstance().name.c_str();
	Phantom::InitGraphics(gameTitle, size.width, size.height);

	//ScreenManager::GetInstance().Initialize();
	//ScreenManager::GetInstance().LoadContent();

	//if (!SystemRequirements::CheckResources(gameTitle))
		//exit;

	_gameState = Initialized;

	return;
}

void Phantom::Start(LPCTSTR gameTitle, float ScreenWidth, float ScreenHeight)
{
	if (_gameState != Initialized)
		return;

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	
	sf::RectangleShape fade(sf::Vector2f(ScreenWidth, ScreenHeight));
	fade.setFillColor(sf::Color(0, 0, 0, 255));

	ScreenManager::GetInstance().Initialize();
	ScreenManager::GetInstance().LoadContent();

	_gameState = Phantom::Initialized;

	_gameObjectManager.Awake();
	_gameObjectManager.Start();

	while (_gameState != Phantom::Exiting)
	{
		float deltaTime = clock.restart().asSeconds();
		GameLoop(ScreenWidth, ScreenHeight, deltaTime);
	}

	Application::_mainWindow.close();
}

void Phantom::InitGraphics(LPCTSTR gameTitle, float width, float height)
{
	if (_gameState != Uninitialized)
		return;

	sf::RenderWindow _mainWindow;
	ScreenSize size = Application::size;

	Application::_mainWindow.create(sf::VideoMode(size.width, size.height, 32), Application::name);
}

bool Phantom::IsExiting()
{
	return false;// isExiting;
}

void Phantom::GameLoop(float ScreenWidth, float ScreenHeight, float deltaTime)
{
	sf::Event event;

	while (Application::_mainWindow.pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed )
	//		(event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			//Window.close();
			_gameState = Phantom::Exiting;
			break;
		}

		ScreenManager::GetInstance().UpdateEvent(event);

		//_gameObjectManager.Update(deltaTime);

	}

	Application::_mainWindow.clear();

	if (_gameState == Playing)
	{

		// update all systems
		_gameObjectManager.Update(deltaTime); // change to tick later

									  // late update all systems
		//_gameObjectManager.LateUpdate(deltaTime); // change to tick later
		_physicsManager.Update(deltaTime);
	}
	ScreenManager::GetInstance().Update(deltaTime);

	sf::RectangleShape fade(sf::Vector2f(ScreenWidth, ScreenHeight));
//	fade.setFillColor(sf::Color(0, 0, 0, 255 * ScreenManager::GetInstance().GetAlpha()));

	ScreenManager::GetInstance().Draw(Application::GetInstance()._mainWindow);
	//Application::_mainWindow.draw(fade);

	Application::GetInstance()._mainWindow.display();

}



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

//////////////////////
/*

void Clarity::GameLoop() {
	// update all systems
	_gameObjectManager.Update(0); // change to tick later

								  // late update all systems
	_gameObjectManager.LateUpdate(0); // change to tick later
}

void Clarity::LevelLoaded() {
	_gameObjectManager.Awake();
	// awake other systems

	_gameObjectManager.Start();
	// start other systems
}

void Clarity::Start(void)
{
	if (_gameState != Initialized)
		return;

	std::cout << "Initialized";
	//_mainWindow.Create(sf::VideoMode(1024,768,32),"GameName");
	_gameState = Clarity::Playing;

	while (!IsExiting())
	{
		GameLoop();
	}

	//_mainWindow.Close();
}

bool Clarity::IsExiting() {
	return true;
}
*/
