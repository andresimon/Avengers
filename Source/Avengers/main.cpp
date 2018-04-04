#include <Windows.h>

#include "tchar.h"

#include "Phantom.h"
#include "Application.h"

static const LPCTSTR gameTitle = "Avengers";
static const std::string name = "Avengers";
static const float ScreenWidth = 1024.0f;
static const float ScreenHeight = 768.0f;

int main(int argc, _TCHAR* argv[])
{ 
	//Application _app(ScreenWidth, ScreenHeight, gameTitle);
	Application::GetInstance().name = name;
	Application::GetInstance().size.width = ScreenWidth;
	Application::GetInstance().size.height = ScreenHeight;

	//Phantom::Initialize(gameTitle, ScreenWidth, ScreenHeight);
	Phantom::Initialize();

	Phantom::Start(gameTitle, ScreenWidth, ScreenHeight);

	return 0;
}

