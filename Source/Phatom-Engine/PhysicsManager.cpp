#include "PhysicsManager.h"

#include <algorithm>

#include "TransformComponent.h"
#include "GameObject.h"

#include "Vectors.h"

//#include <iterator>

bool PhysicsManager::IsGrounded(Rigidbody2DComponent* rigidBody)
{
	std::list<Rigidbody2DComponent*> ::iterator it;
	for (it = rigidBodies.begin(); it != rigidBodies.end(); ++it)
	{
		Rigidbody2DComponent* rb = *it;
		if (rb != rigidBody) 
		{
			if (rigidBody->GetAABB().bLeft.x < rb->GetAABB().tRight.x
				&& rigidBody->GetAABB().tRight.x > rb->GetAABB().bLeft.x
				&& abs(rigidBody->GetAABB().bLeft.y - rb->GetAABB().tRight.y) <= groundedTol)
			{
				if (abs(rigidBody->GetCurrentVelocity().y) < groundedTol) return true;
			}
		}
	}
	return false;
}

void PhysicsManager::Update(float dt)
{
	CheckCollisions();
	ResolveCollisions();
	IntegrateBodies(dt);
}

void PhysicsManager::CheckCollisions()
{
	std::list<Rigidbody2DComponent*>::iterator itA = rigidBodies.begin();

//	unsigned int index = 0;
	
	if (rigidBodies.size() == 0) return;

	for ( unsigned int a = 0; a <= rigidBodies.size()-1; a++)
	{
		Rigidbody2DComponent* bodyA = *itA;
	
		unsigned int index = a + 1;
		//std::cout << index << std::endl;


		std::list<Rigidbody2DComponent*>::iterator itB = rigidBodies.begin();
		std::advance(itB, index);
		for (unsigned int b = index; b < rigidBodies.size() ; b++)
		//	for (unsigned int b = index; b <= rigidBodies.size() - index; b++)
		{
			Rigidbody2DComponent* bodyB = *itB;

			//std::cout << "Checking " << bodyA->GetOwner()->name << " with " << bodyB->GetOwner()->name << std::endl;

			if (bodyA != bodyB)
			{
				CollisionPair pair;
				CollisionInfo colInfo;
				pair.rigidBodyA = bodyA; pair.rigidBodyB = bodyB;

				std::shared_ptr<TransformComponent> tempTransformA =
					std::dynamic_pointer_cast<TransformComponent>(bodyA->GetOwner()->GetComponent(TransformComponentType));

				sf::Vector2f tempPosA = tempTransformA->getPosition();

				std::shared_ptr<TransformComponent> tempTransformB =
					std::dynamic_pointer_cast<TransformComponent>(bodyB->GetOwner()->GetComponent(TransformComponentType));

				sf::Vector2f tempPosB = tempTransformB->getPosition();

				sf::Vector2f distance = tempPosB - tempPosA;

				sf::Vector2f halfSizeA = (bodyA->GetAABB().tRight - bodyA->GetAABB().bLeft) / 2.f;
				sf::Vector2f halfSizeB = (bodyB->GetAABB().tRight - bodyB->GetAABB().bLeft) / 2.f;

				sf::Vector2f gap = sf::Vector2f(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

				// Seperating Axis Theorem test
				if (gap.x < 0 && gap.y < 0)
				{
					if (bodyA->GetOwner()->GetName() != "NO NAME")
					std::cout << "Collided!!!" << bodyA->GetOwner()->GetName() << " with " << bodyB->GetOwner()->GetName() << std::endl;

				//	if (collisions.ContainsKey(pair)) {
				//		collisions.Remove(pair);
				//	}

					std::vector<Collision>::iterator it;
					for (it = collisions.begin(); it != collisions.end(); ++it)
					{
						if ( it->rigidBodyA == pair.rigidBodyA &&
							 it->rigidBodyB == pair.rigidBodyB )
						{
							collisions.erase(it);
							break;
						}
					}

					if (gap.x > gap.y) 
					{
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
					else 
					{
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

					//collisions.insert(std::make_pair(&pair, &colInfo));
					Collision temp;
					temp.rigidBodyA = pair.rigidBodyA;
					temp.rigidBodyB = pair.rigidBodyB;
					temp.collisionNormal = colInfo.collisionNormal;
					temp.penetration = colInfo.penetration;
					collisions.push_back(temp);
					
				}
			//	else if (collisions.ContainsKey(pair)) {
				//	Debug.Log("removed");
				//	collisions.Remove(pair);
				//}
				else
				{
					std::vector<Collision>::iterator it;
					for (it = collisions.begin(); it != collisions.end(); ++it)
					{
						if (it->rigidBodyA == pair.rigidBodyA &&
							it->rigidBodyB == pair.rigidBodyB)
						{
							collisions.erase(it);
							printf("removed");
							break;
						}
					}
				}
			}

			std::advance(itB, 1);
		}

		std::advance(itA, 1);
		//index++;
	}
	
}

void PhysicsManager::ResolveCollisions()
{
	//std::map<CollisionPair, CollisionInfo>::iterator it;
	std::vector<Collision>::iterator it;
	for (it = collisions.begin(); it != collisions.end(); ++it)
	{
		CollisionPair pair;
		pair.rigidBodyA = it->rigidBodyA;
		pair.rigidBodyB = it->rigidBodyB;
		CollisionInfo colInfo;
		colInfo.collisionNormal = it->collisionNormal;
		colInfo.penetration = it->penetration;

		float minBounce = fmin(pair.rigidBodyA->GetBounciness(), pair.rigidBodyB->GetBounciness());

		sf::Vector2f temp = pair.rigidBodyB->GetCurrentVelocity() - pair.rigidBodyA->GetCurrentVelocity();
		Vector2 vecTemp  = Vector2(temp.x, temp.y);
		Vector2 infoTemp = Vector2(colInfo.collisionNormal.x, colInfo.collisionNormal.y);
		float velAlongNormal = vecTemp.dot(infoTemp);
		if (velAlongNormal > 0) continue;

		float j = -(1 + minBounce) * velAlongNormal;

		float oMassA = pair.rigidBodyA->GetMass();
		float oMassB = pair.rigidBodyB->GetMass();
		float invMassA, invMassB;

		if (oMassA == 0)
			invMassA = 0;
		else
			invMassA = 1 / oMassA;

		if (oMassB == 0)
			invMassB = 0;
		else
			invMassB = 1 / oMassB;

		j /= invMassA + invMassB;

		sf::Vector2f impulse = j * colInfo.collisionNormal;

		// ... update velocities
		if ( oMassA > 0.0f )
			pair.rigidBodyA->SetCurrentVelocity(pair.rigidBodyA->GetCurrentVelocity() -  1 / oMassA * impulse);

		if ( oMassB > 0.0f )
			pair.rigidBodyB->SetCurrentVelocity(pair.rigidBodyB->GetCurrentVelocity() + 1 / oMassB * impulse);

		if ( abs(colInfo.penetration) > 0.01f)
		{
			//PositionalCorrection(pair);
		}

	}
}

void PhysicsManager::IntegrateBodies(float dT)
{
	std::list<Rigidbody2DComponent*> ::iterator it;

	for (it = rigidBodies.begin(); it != rigidBodies.end(); ++it) 
		(*it)->Integrate(dT);
}
