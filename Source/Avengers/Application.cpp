#include "Application.h"

ScreenSize	Application::size;
std::string Application::name;
sf::RenderWindow Application::_mainWindow;

/*
Application::Application(int width, int height, std::string name)
{
	this->size = ScreenSize{ width, height };
	this->name = name;
}
*/

Application::Application()
{
}

Application::~Application()
{
}


void Application::operator=(Application & const)
{
}


Application &Application::GetInstance()
{
	static Application instance;
	return instance;
}
