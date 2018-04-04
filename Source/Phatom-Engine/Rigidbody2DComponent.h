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

		AABB GetAABB();
		void Integrate(float dT);
		void AddForce(sf::Vector2f force);
		bool IsGrounded();
		

	///////////////
		void Update();

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::IntRect rectShape;

		std::string fileName;

		void LoadContent();

		float mass = 1.f;				// Mass of the RigidBody
		float bounciness = 1.f;			// The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
		bool obeysGravity = true;
		sf::Vector2f gravity;			// The gravity vector applied to this body

		sf::Vector2f maxVelocity;		// The maximum allowed velocity for this object

		sf::Vector2f currentVelocity;  // The current velocity the body is moving at

		bool grounded;

		sf::Vector2f totalForces;

		AABB aabb;

		//PhysicsEngine engine;

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

	public bool IsGrounded()
	{
		grounded = engine.IsGrounded(this);
		return grounded;
	}

	
	void SetAABB()
	{
		Bounds bound = new Bounds(new Vector2(0, 0), new Vector2(1, 1));
		Renderer renderer = GetComponent<Renderer>();

		if (renderer)
		{
			bound = renderer.bounds;
		}

		aabb.bLeft = new Vector2(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
		aabb.tRight = new Vector2(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
	}

	void Start()
	{
		SetAABB();
		engine = GameObject.FindWithTag("PhysicsEngine").GetComponent<PhysicsEngine>();

		engine.AddRigidBody(this);
	}

	
	
*/
