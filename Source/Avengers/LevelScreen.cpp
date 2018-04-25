#include "LevelScreen.h"

#include "../Phatom-Engine/Phantom.h"
#include "../Phatom-Engine/SpriteRenderComponent.h"
#include "../Phatom-Engine/TransformComponent.h"
#include "../Phatom-Engine/Rigidbody2DComponent.h"
#include "../Phatom-Engine/ScriptComponent.h"
#include "../Phatom-Engine/SceneLoader.h"

#include "Application.h"
#include "PlayerController.h"

LevelScreen::LevelScreen()
{
	Phantom::_gameState = Phantom::Playing ;

	
}

LevelScreen::~LevelScreen()
{
}

void LevelScreen::LoadContent()
{
	if (!font.loadFromFile("../../../Assets/fonts/American Captain.ttf"))
		std::cout << "Could not find the specified font at LevelScreen.cpp" << std::endl;

	text.setString("First Level");
	text.setFont(font);
	
	SceneLoader::GetInstance().LoadContent("../scenes/level1.json");

	background = Phantom::_gameObjectManager.GetObjectByName("Background");
	
	player = Phantom::_gameObjectManager.GetObjectByName("Player");
	player->addComponent(ComponentTypes::ScriptComponentType, std::make_shared<PlayerController>());

	shield = Phantom::_gameObjectManager.GetObjectByName("Shield");
	shield->SetParent(player);

	
	// Setting background size 
	std::shared_ptr<SpriteRenderComponent> spriteComp =
		std::dynamic_pointer_cast<SpriteRenderComponent>(background->GetComponent(SpriteRenderComponentType));
	sf::Vector2u TextureSize = spriteComp->GetTexture().getSize();				  //Get size of texture.
	sf::Vector2u WindowSize = Application::GetInstance()._mainWindow.getSize();   //Get size of window.

	float ScaleX = (float)WindowSize.x / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

	spriteComp->SetScale(ScaleX, ScaleY); //Set scale.  

	Phantom::_gameObjectManager.Awake();
	Phantom::_gameObjectManager.Start();
}

void LevelScreen::UnloadContent()
{

}

void LevelScreen::UpdateEvent(sf::Event event)
{
	std::shared_ptr<TransformComponent> transform =
		std::dynamic_pointer_cast<TransformComponent>(player->GetComponent(TransformComponentType));

	if (transform != nullptr)
	{
		if (input.KeyPressed((sf::Keyboard::Left)) || input.KeyPressed(sf::Keyboard::A))
		{
			sf::Vector2f pos = transform->getPosition();
			transform->move(pos.x - 1.f, pos.y);
		}
		if (input.KeyPressed((sf::Keyboard::Right)) || input.KeyPressed(sf::Keyboard::D))
		{
			sf::Vector2f pos = transform->getPosition();
			transform->move(pos.x +1.f , pos.y);
		}
	}


	input.Update(event);
	//character.updateEvent(input);
}

void LevelScreen::Update(double deltaTime)
{
	//character.update(deltaTime);
}

void LevelScreen::Draw(sf::RenderWindow& window)
{
	window.draw(text);
	//character.draw(window);
}