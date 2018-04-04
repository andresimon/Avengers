#include "Rigidbody2DComponent.h"

#include "Phantom.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "../Avengers/Application.h"

Rigidbody2DComponent::Rigidbody2DComponent(float mass, float bounciness, bool obeysGravity)
{
	this->mass = mass;
	this->bounciness = bounciness;
	this->obeysGravity = obeysGravity;

	this->gravity = sf::Vector2f(0.f, -9.8);

	this->maxVelocity = sf::Vector2f(10, 10);

	/////
	//SetAABB();
	//engine = GameObject.FindWithTag("PhysicsEngine").GetComponent<PhysicsEngine>();
	Phantom::_physicsManager.AddRigidBody(*this);
	//engine.AddRigidBody(this);
	/////

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
		std::dynamic_pointer_cast<TransformComponent>(m_Parent->GetComponent(TranformComponentType));
	sf::Vector2f temp = tempTransform->getPosition();

	temp += currentVelocity * dT;
	tempTransform->move(temp.x, temp.y);
//	SetAABB();

	totalForces = sf::Vector2f(0, 0);
}

void Rigidbody2DComponent::AddForce(sf::Vector2f force)
{
	totalForces += force;
}

bool Rigidbody2DComponent::IsGrounded()
{
	grounded = Phantom::_physicsManager.IsGrounded(*this);
	return grounded;
}

void Rigidbody2DComponent::Update()
{
	std::shared_ptr<SpriteRenderComponent> spriteComp =
		std::dynamic_pointer_cast<SpriteRenderComponent>(m_Parent->GetComponent(SpriteRenderComponentType));
	
	sf::FloatRect rectSize = spriteComp->GetSprite().getGlobalBounds();
	sf::RectangleShape a(sf::Vector2f(rectSize.width, rectSize.height));
	a.setPosition(rectSize.left, rectSize.top);
	a.setOutlineColor(sf::Color::Green);

	Application::GetInstance()._mainWindow.draw(a);
}

void Rigidbody2DComponent::LoadContent()
{
}
