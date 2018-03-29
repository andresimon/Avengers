#include <Windows.h>

#include "tchar.h"

#include "Phantom.h"

static const LPCTSTR gameTitle = "Avengers";
static const float ScreenWidth = 1024.0f;
static const float ScreenHeight = 768.0f;

int main(int argc, _TCHAR* argv[])
{ 
	Phantom::Initialize(gameTitle, ScreenWidth, ScreenHeight);

	Phantom::Start(gameTitle, ScreenWidth, ScreenHeight);

	return 0;
}

