#pragma once

#include <SFML/Graphics.hpp>

#include <list>

#include "Rigidbody2DComponent.h"

struct CollisionPair
{
	Rigidbody2DComponent rigidBodyA;
	Rigidbody2DComponent rigidBodyB;
};

struct CollisionInfo
{
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

		inline void AddRigidBody(Rigidbody2DComponent rigidBody) { rigidBodies.push_back(rigidBody); }
		
		bool IsGrounded(Rigidbody2DComponent rigidBody);

		void Update(float dt);

	private:
		std::list<Rigidbody2DComponent> rigidBodies;

		void IntegrateBodies(float dT);
};
/*

	private Dictionary<CollisionPair, CollisionInfo> collisions = new Dictionary<CollisionPair, CollisionInfo>();


	

	void CheckCollisions()
	{
		foreach(PhysicsRBody bodyA in rigidBodies.GetRange(0, rigidBodies.Count - 1))
		{
			foreach(PhysicsRBody bodyB in rigidBodies.GetRange(rigidBodies.IndexOf(bodyA), rigidBodies.Count - rigidBodies.IndexOf(bodyA)))
			{
				if (bodyA != bodyB)
				{
					CollisionPair pair = new CollisionPair();
					CollisionInfo colInfo = new CollisionInfo();
					pair.rigidBodyA = bodyA; pair.rigidBodyB = bodyB;

					Vector2 distance = bodyB.transform.position - bodyA.transform.position;

					Vector2 halfSizeA = (bodyA.aabb.tRight - bodyA.aabb.bLeft) / 2;
					Vector2 halfSizeB = (bodyB.aabb.tRight - bodyB.aabb.bLeft) / 2;

					Vector2 gap = new Vector2(Mathf.Abs(distance.x), Mathf.Abs(distance.y)) - (halfSizeA + halfSizeB);

					// Seperating Axis Theorem test
					if (gap.x < 0 && gap.y < 0)
					{
						Debug.LogWarning("Collided!!!");


						if (collisions.ContainsKey(pair)) {
							collisions.Remove(pair);
						}

						if (gap.x > gap.y) {
							if (distance.x > 0)
							{
								// ... Update collision normal
								colInfo.collisionNormal.x = 1.0f;
							}
							else
							{
								// ... Update collision normal
								colInfo.collisionNormal.x = -1.0f;
							}
							colInfo.penetration = gap.x;
						}
						else {
							if (distance.y > 0)
							{
								// ... Update collision normal
								colInfo.collisionNormal.y = 1.0f;
							}
							else
							{
								// ... Update collision normal
								colInfo.collisionNormal.y = -1.0f;
							}
							colInfo.penetration = gap.y;
						}
						collisions.Add(pair, colInfo);
					}
					else if (collisions.ContainsKey(pair)) {
						Debug.Log("removed");
						collisions.Remove(pair);
					}

				}
			}
		}
	}

	void ResolveCollisions()
	{
		foreach(CollisionPair pair in collisions.Keys)
		{


			float minBounce = Mathf.Min(pair.rigidBodyA.bounciness, pair.rigidBodyB.bounciness);
			float velAlongNormal = Vector2.Dot(pair.rigidBodyB.CurrentVelocity - pair.rigidBodyA.CurrentVelocity, collisions[pair].collisionNormal);
			if (velAlongNormal > 0) continue;

			float j = -(1 + minBounce) * velAlongNormal;
			float invMassA, invMassB;
			if (pair.rigidBodyA.mass == 0)
				invMassA = 0;
			else
				invMassA = 1 / pair.rigidBodyA.mass;

			if (pair.rigidBodyB.mass == 0)
				invMassB = 0;
			else
				invMassB = 1 / pair.rigidBodyB.mass;

			j /= invMassA + invMassB;

			Vector2 impulse = j * collisions[pair].collisionNormal;

			// ... update velocities
			if (pair.rigidBodyA.mass > 0.0f)
				pair.rigidBodyA.CurrentVelocity -= 1 / pair.rigidBodyA.mass * impulse;
			if (pair.rigidBodyB.mass > 0.0f)
				pair.rigidBodyB.CurrentVelocity += 1 / pair.rigidBodyB.mass * impulse;

			if (Mathf.Abs(collisions[pair].penetration) > 0.01f)
			{
				PositionalCorrection(pair);
			}
		}
	}

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


