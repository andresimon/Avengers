#include <Windows.h>
#include "tchar.h"

#include "Phantom.h"
#include "SplashScreen.h"

static const LPCTSTR gameTitle = "Avengers";

int main(int argc, _TCHAR* argv[])
{
	SplashScreen sc;

	Phantom::InitGraphics(gameTitle);

	sc.Show(Phantom::_mainWindow);

	//if ( ! Phantom::Initialize(gameTitle) )
	//	return -1;

	Phantom::Start(gameTitle);
	return 0;
}

//#include <SFML/Graphics.hpp>
/*
int main()
{
sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
sf::CircleShape shape(100.f);
shape.setFillColor(sf::Color::Green);

while (window.isOpen())
{
sf::Event event;
while (window.pollEvent(event))
{
if (event.type == sf::Event::Closed)
window.close();
}

window.clear();
window.draw(shape);
window.display();
}

return 0;
}
*/