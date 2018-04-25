#include "LevelScreen.h"

#include "../Phatom-Engine/Phantom.h"
#include "../Phatom-Engine/SpriteRenderComponent.h"
#include "../Phatom-Engine/TransformComponent.h"
#include "../Phatom-Engine/Rigidbody2DComponent.h"
#include "../Phatom-Engine/ScriptComponent.h"

#include "Application.h"
#include "PlayerController.h"

LevelScreen::LevelScreen()
{
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

	/* Background */
	background = Phantom::_gameObjectManager.CreateObject();

	background->addComponent(ComponentTypes::TransformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(0.f, 0.f)));

	background->addComponent(ComponentTypes::SpriteRenderComponentType,
		std::make_shared<SpriteRenderComponent>("images/Walkway_00.png", sf::IntRect(0.f, 0.f, 951.f, 151.f)));

	// Setting background size 
	std::shared_ptr<SpriteRenderComponent> spriteComp =
		std::dynamic_pointer_cast<SpriteRenderComponent>(background->GetComponent(SpriteRenderComponentType));
	sf::Vector2u TextureSize = spriteComp->GetTexture().getSize();				  //Get size of texture.
	sf::Vector2u WindowSize = Application::GetInstance()._mainWindow.getSize();   //Get size of window.

	float ScaleX = (float)WindowSize.x / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

	spriteComp->SetScale(ScaleX, ScaleY); //Set scale.  

	/* Ground */
	ground = Phantom::_gameObjectManager.CreateObject();

	ground->addComponent(ComponentTypes::TransformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(0.f, 500.f)));

	ground->addComponent(ComponentTypes::SpriteRenderComponentType,
		std::make_shared<SpriteRenderComponent>("images/Street_01.png"));

	ground->addComponent(ComponentTypes::Rigidbody2DComponentType,
		std::make_shared<Rigidbody2DComponent>(0.f, 0.1f, false));

	/* Player */
	player = Phantom::_gameObjectManager.CreateObject();

	player->addComponent(ComponentTypes::TransformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(50.f, 50.f)));

	player->addComponent(ComponentTypes::SpriteRenderComponentType, 
		std::make_shared<SpriteRenderComponent>("images/CapAmerica_Idle_00.png", sf::IntRect(0.f, 0.f, 84.f, 82.f)));

	player->addComponent(ComponentTypes::Rigidbody2DComponentType,
		std::make_shared<Rigidbody2DComponent>(1.f, 1.f, true));

	player->addComponent(ComponentTypes::ScriptComponentType,
		std::make_shared<PlayerController>());

	player->name = "P1";


	/* Shield *
	shield = Phantom::_gameObjectManager.CreateObject();

	shield->addComponent(ComponentTypes::TransformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(50.f, 10.f)));

	shield->addComponent(ComponentTypes::SpriteRenderComponentType,
		std::make_shared<SpriteRenderComponent>("images/Shield_00.png"));

	shield->addComponent(ComponentTypes::Rigidbody2DComponentType,
		std::make_shared<Rigidbody2DComponent>(1.f, 1.f, false));

	//shield->addComponent(ComponentTypes::ScriptComponentType,
		//std::make_shared<PlayerController>());

	shield->SetParent(player);
	shield->name = "Shield";

	/* Player2 */
	player2 = Phantom::_gameObjectManager.CreateObject();

	player2->addComponent(ComponentTypes::TransformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(150.f, 50.f)));

	player2->addComponent(ComponentTypes::SpriteRenderComponentType,
		std::make_shared<SpriteRenderComponent>("images/CapAmerica_Idle_00.png", sf::IntRect(0.f, 0.f, 84.f, 82.f)));

	player2->addComponent(ComponentTypes::Rigidbody2DComponentType,
		std::make_shared<Rigidbody2DComponent>(1.f, 1.f, true));

	player2->addComponent(ComponentTypes::ScriptComponentType,
		std::make_shared<PlayerController>());
	player2->name = "P2";

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