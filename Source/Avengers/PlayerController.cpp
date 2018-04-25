#include "PlayerController.h"

PlayerController::PlayerController()
{
}

void PlayerController::Update(float msec)
{
	
}

void PlayerController::Awake()
{
	name = "PLAYERCONTROLLER";
}

void PlayerController::Start()
{ 
	teste();
}

void PlayerController::teste()
{
	printf("teste \n");
}