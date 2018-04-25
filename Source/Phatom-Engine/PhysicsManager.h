#pragma once

#include <SFML/Graphics.hpp>

#include <list>

#include "Rigidbody2DComponent.h"

struct CollisionPair
{
	Rigidbody2DComponent* rigidBodyA;
	Rigidbody2DComponent* rigidBodyB;
};

struct CollisionInfo
{
	sf::Vector2f collisionNormal;
	float penetration;
};

struct Collision
{
	Rigidbody2DComponent* rigidBodyA;
	Rigidbody2DComponent* rigidBodyB;
	sf::Vector2f collisionNormal;
	float penetration;
};


class PhysicsManager
{
	public:
		PhysicsManager() {};
		~PhysicsManager() {};

		//float groundedTol = 0.1f;
		float groundedTol;

		inline void AddRigidBody(Rigidbody2DComponent* rigidBody) { rigidBodies.push_back(rigidBody); }
		
		bool IsGrounded(Rigidbody2DComponent* rigidBody);

		void Update(float dt);

		void CheckCollisions();

		void ResolveCollisions();

	private:
		std::list<Rigidbody2DComponent*> rigidBodies;

		//std::map<CollisionPair, CollisionInfo> collisions;
		std::vector<Collision> collisions;
		void IntegrateBodies(float dT);
};
/*



	void PositionalCorrection(CollisionPair c) {
		const float percent = 0.2f;

		float invMassA, invMassB;
		if (c.rigidBodyA.mass == 0)
			invMassA = 0;
		else
			invMassA = 1 / c.rigidBodyA.mass;

		if (c.rigidBodyB.mass == 0)
			invMassB = 0;
		else
			invMassB = 1 / c.rigidBodyB.mass;

		Vector2 correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

		Vector2 temp = c.rigidBodyA.transform.position;
		temp -= invMassA * correction;
		c.rigidBodyA.transform.position = temp;

		temp = c.rigidBodyB.transform.position;
		temp += invMassB * correction;
		c.rigidBodyB.transform.position = temp;
	}

	void UpdatePhysics()
	{
		// .... 
		CheckCollisions();
		ResolveCollisions();
		IntegrateBodies(Time.fixedDeltaTime);
	}

	// Update is called once per frame
	void FixedUpdate() {
		UpdatePhysics();
	}
	*/


