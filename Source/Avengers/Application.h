#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct ScreenSize
{
	int width;
	int height;
};

class Application
{
	public:
		~Application();
		static Application &GetInstance();

		static  ScreenSize size;
		static  std::string name;
		static  sf::RenderWindow _mainWindow;
	
	private:
		Application();

		Application(Application &const);
		void operator=(Application& const);

};
