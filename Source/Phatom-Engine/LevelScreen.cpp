#include "LevelScreen.h"

#include "Phantom.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "Rigidbody2DComponent.h"

#include "../Avengers/Application.h"

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

	background = Phantom::_gameObjectManager.CreateObject();

	background->addComponent(ComponentTypes::TranformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(0.f, 0.f)));

	background->addComponent(ComponentTypes::SpriteRenderComponentType,
		std::make_shared<SpriteRenderComponent>("images/Walkway_00.png", sf::IntRect(0.f, 0.f, 951.f, 151.f)));

	/* Setting background size */
	std::shared_ptr<SpriteRenderComponent> spriteComp =
		std::dynamic_pointer_cast<SpriteRenderComponent>(background->GetComponent(SpriteRenderComponentType));
	sf::Vector2u TextureSize = spriteComp->GetTexture().getSize();				  //Get size of texture.
	sf::Vector2u WindowSize = Application::GetInstance()._mainWindow.getSize();   //Get size of window.

	float ScaleX = (float)WindowSize.x / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

	spriteComp->SetScale(ScaleX, ScaleY); //Set scale.  

	ground = Phantom::_gameObjectManager.CreateObject();

	ground->addComponent(ComponentTypes::TranformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(0.f, 500.f)));

	ground->addComponent(ComponentTypes::SpriteRenderComponentType,
		std::make_shared<SpriteRenderComponent>("images/Street_01.png"));


	player = Phantom::_gameObjectManager.CreateObject();
	
	player->addComponent(ComponentTypes::TranformComponentType,
		std::make_shared<TransformComponent>(sf::Vector2f(50.f, 50.f)));

	player->addComponent(ComponentTypes::SpriteRenderComponentType, 
		std::make_shared<SpriteRenderComponent>("images/CapAmerica_Idle_00.png", sf::IntRect(0.f, 0.f, 84.f, 82.f)));

	player->addComponent(ComponentTypes::Rigidbody2DComponentType,
		std::make_shared<Rigidbody2DComponent>(1.f, 1.f, true));

}

void LevelScreen::UnloadContent()
{

}

void LevelScreen::UpdateEvent(sf::Event event)
{
	std::shared_ptr<TransformComponent> transform =
		std::dynamic_pointer_cast<TransformComponent>(player->GetComponent(TranformComponentType));

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