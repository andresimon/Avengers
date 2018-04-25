#pragma once

#include <SFML/Graphics.hpp>

#include "BaseComponent.h"

struct AABB
{
	sf::Vector2f bLeft;
	sf::Vector2f tRight;
};

class Rigidbody2DComponent : public BaseComponent
{
	public:
		Rigidbody2DComponent(float mass, float bounciness, bool obeysGravity);
		~Rigidbody2DComponent();
		
		void SetObeysGravity(bool obey);

		void SetMaxVelocity(sf::Vector2f maxVelocity);
		sf::Vector2f GetCurrentVelocity();
		void SetCurrentVelocity(sf::Vector2f currentVelocity);

		inline float GetMass() { return this->mass; }
		inline void SetMass(float value) { this->mass = value; }
		inline float GetBounciness() { return this->bounciness; }
		inline void SetBounciness(float value) { this->bounciness = value;  }
		AABB GetAABB();
		void SetAABB();

		void Integrate(float dT);
		void AddForce(sf::Vector2f force);
		bool IsGrounded();
		
		void Awake();
		void Update();

	private:
		sf::Sprite sprite;
		sf::IntRect rectShape;

		void LoadContent();

		float mass;						// Mass of the RigidBody
		float bounciness;				// The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
		bool obeysGravity;
		sf::Vector2f gravity;			// The gravity vector applied to this body

		sf::Vector2f maxVelocity;		// The maximum allowed velocity for this object

		sf::Vector2f currentVelocity;  // The current velocity the body is moving at

		bool grounded;

		sf::Vector2f totalForces;

		AABB aabb;

};

/*
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PhysicsRBody : MonoBehaviour
{
	

	public void Stop()
	{
		currentVelocity = Vector2.zero;
		totalForces = Vector2.zero;
	}

	
	void SetAABB()
	{
		
	}

*/
