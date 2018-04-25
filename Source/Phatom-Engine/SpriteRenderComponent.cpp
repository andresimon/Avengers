#include "SpriteRenderComponent.h"

#include "TransformComponent.h"
#include "GameObject.h"

#include "../Avengers/Application.h"

SpriteRenderComponent::SpriteRenderComponent(std::string fileName)
{
	this->fileName = fileName;
	this->rectShape = sf::IntRect();

	LoadContent();
}

SpriteRenderComponent::SpriteRenderComponent(std::string fileName, sf::IntRect rectShape)
{
	this->fileName = fileName;
	this->rectShape = rectShape;

	LoadContent();
	this->sprite.setTextureRect(this->rectShape);
	
}

void SpriteRenderComponent::LoadContent()
{
	std::string assetsFolder = "../../../Assets/";
	std::string fullFileName = assetsFolder.append(this->fileName);

	if (!this->texture.loadFromFile(fullFileName))
	{
		std::cout << "Could not find the specified image at SpriteRenderComponent.cpp" << std::endl;
		return;
	}

	this->sprite.setTexture(this->texture);
}

void SpriteRenderComponent::SetPosition(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
}

void SpriteRenderComponent::Update()
{
	std::shared_ptr<TransformComponent> transform =
		std::dynamic_pointer_cast<TransformComponent>(m_Owner->GetComponent(TransformComponentType));

	if (transform != nullptr)
	{
		sf::Vector2f pos = transform->getPosition();
		sprite.setPosition(transform->getPosition());
	}
	
	Application::GetInstance()._mainWindow.draw(sprite);
}

void SpriteRenderComponent::SetScale(float x, float y)
{
	sprite.setScale(x, y);
}
