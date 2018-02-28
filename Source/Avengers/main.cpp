#include <Windows.h>
#include "tchar.h"

#include "Phantom.h"
#include "SplashScreen.h"

static const LPCTSTR gameTitle = "Avengers";
static const float screenWidth = 1024.0f;
static const float screenHeight = 768.0f;

int main(int argc, _TCHAR* argv[])
{
	SplashScreen sc;

	Phantom::InitGraphics(gameTitle, screenWidth, screenHeight);

	sc.Show(Phantom::_mainWindow);

	if ( ! Phantom::Initialize(gameTitle) )
		return -1;

	Phantom::Start(gameTitle);
	return 0;
}

