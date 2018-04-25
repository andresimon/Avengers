#include "TransformComponent.h"

#include "GameObject.h"

void TransformComponent::move(float x, float y)
{
	float xOffset, yOffset;
	Matrix4 mTemp;
	GameObject* parent = m_Owner->GetParent();

	if (parent)
	{
		std::shared_ptr<TransformComponent> parentTransform =
			std::dynamic_pointer_cast<TransformComponent>(parent->GetComponent(TransformComponentType));

		mTemp = parentTransform->worldTransform * this->transform;
		xOffset = x - mTemp[12];
		yOffset = y - mTemp[13];
	}
	else
	{
		xOffset = x - this->transform[12];
		yOffset = y - this->transform[13];
	}
	this->transform.translate(xOffset, yOffset, 0);
}

sf::Vector2f const TransformComponent::getPosition()
{
	return sf::Vector2f(worldTransform[12], worldTransform[13]);
}

void TransformComponent::Update(float deltaTime)
{
	GameObject* parent = m_Owner->GetParent();

	if ( parent )
	{ 
		//This node has a parent...
		std::shared_ptr<TransformComponent> parentTransform =
			std::dynamic_pointer_cast<TransformComponent>(parent->GetComponent(TransformComponentType));

		this->worldTransform = parentTransform->worldTransform * transform;
		this->position = sf::Vector2f(worldTransform[12], worldTransform[13]);
	}
	else 
	{ 
		//Root node, world transform is local transform!
		this->worldTransform = transform;
	}
}
