#include "Rigidbody2DComponent.h"

#include "Phantom.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "../Avengers/Application.h"

struct Bound
{
	sf::Vector2f center;
	sf::Vector2f extents;
};

Rigidbody2DComponent::Rigidbody2DComponent(float mass, float bounciness, bool obeysGravity)
{
	this->mass = mass;
	this->bounciness = bounciness;
	this->obeysGravity = obeysGravity;

	this->gravity = sf::Vector2f(0.f, 9.8); // SFML origin coordenate is at left, top - so it increase downward 

	this->maxVelocity = sf::Vector2f(1000, 1000);

}

Rigidbody2DComponent::~Rigidbody2DComponent()
{
}

void Rigidbody2DComponent::SetObeysGravity(bool obey)
{
	this->obeysGravity = obey;
}

void Rigidbody2DComponent::SetMaxVelocity(sf::Vector2f maxVelocity)
{
	this->maxVelocity = maxVelocity;
}

sf::Vector2f Rigidbody2DComponent::GetCurrentVelocity()
{
	return currentVelocity;
}

void Rigidbody2DComponent::SetCurrentVelocity(sf::Vector2f currentVelocity)
{
	float currentVelocityX = fmin(currentVelocity.x, maxVelocity.x);
	float currentVelocityY = fmin(currentVelocity.y, maxVelocity.y);

	this->currentVelocity = sf::Vector2f(currentVelocityX, currentVelocityY);
}

AABB Rigidbody2DComponent::GetAABB()
{
	return this->aabb;
}

void Rigidbody2DComponent::SetAABB()
{
	std::shared_ptr<SpriteRenderComponent> tempSprite =
		std::dynamic_pointer_cast<SpriteRenderComponent>(m_Owner->GetComponent(SpriteRenderComponentType));

	if (tempSprite != nullptr)
	{
		sf::FloatRect AABB = tempSprite->GetSprite().getGlobalBounds();
		sf::Vector2f center(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
		sf::Vector2f extents(AABB.width / 2.f, AABB.height / 2.f);

		Bound bound;
		bound.center = center;
		bound.extents = extents;

		aabb.bLeft  = sf::Vector2f(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
		aabb.tRight = sf::Vector2f(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
	}
}

void Rigidbody2DComponent::Integrate(float dT)
{
	if (obeysGravity && !IsGrounded()) 
	{
		AddForce(gravity);
	}
	else 
	{
		if ( abs(currentVelocity.y) < 0.05f) currentVelocity.y = 0;
	}

	sf::Vector2f acceleration = totalForces / mass;
	if (mass == 0)
		acceleration = sf::Vector2f(0, 0);

	currentVelocity += acceleration * dT;

	std::shared_ptr<TransformComponent> tempTransform = 
		std::dynamic_pointer_cast<TransformComponent>(m_Owner->GetComponent(TransformComponentType));

	sf::Vector2f temp = tempTransform->getPosition();

	temp += currentVelocity * dT;
	tempTransform->move(temp.x, temp.y);

	SetAABB();

	totalForces = sf::Vector2f(0, 0);
}

void Rigidbody2DComponent::AddForce(sf::Vector2f force)
{
	totalForces += force;
}

bool Rigidbody2DComponent::IsGrounded()
{
	grounded = Phantom::_physicsManager.IsGrounded(this);
	return grounded;
}

void Rigidbody2DComponent::Awake()
{
	Phantom::_physicsManager.AddRigidBody(this);

	SetAABB();
}

void Rigidbody2DComponent::Update()
{
	std::shared_ptr<SpriteRenderComponent> spriteComp =
		std::dynamic_pointer_cast<SpriteRenderComponent>(m_Owner->GetComponent(SpriteRenderComponentType));
	
	if (spriteComp != nullptr)
	{
		sf::FloatRect a = spriteComp->GetSprite().getGlobalBounds();

		sf::VertexArray collider(sf::LinesStrip,5);
		collider[0].position = sf::Vector2f(a.left, a.top);
		collider[1].position = sf::Vector2f(a.left + a.width, a.top);
		collider[2].position = sf::Vector2f(a.left + a.width, a.top + a.height);
		collider[3].position = sf::Vector2f(a.left, a.top+a.height);
		collider[4].position = sf::Vector2f(a.left, a.top);

		for (unsigned int x = 0; x < collider.getVertexCount(); x++)
			collider[x].color = sf::Color::Green;
		/*
		collider[0].color = (sf::Color::Green);
		collider[1].color = (sf::Color::Green);
		collider[2].color = (sf::Color::Green);
		collider[3].color = (sf::Color::Green);
		collider[4].color = (sf::Color::Green);
		*/

		Application::GetInstance()._mainWindow.draw(collider);
	}
	

}

void Rigidbody2DComponent::LoadContent()
{
}
