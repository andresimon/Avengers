#include "PhysicsManager.h"

#include <iostream> // test

bool PhysicsManager::IsGrounded(Rigidbody2DComponent rigidBody)
{
	std::list<Rigidbody2DComponent> ::iterator it;
	for (it = rigidBodies.begin(); it != rigidBodies.end(); ++it)
	{
		Rigidbody2DComponent& rb = *it;
		if (&rb != &rigidBody) 
		{
			if (rigidBody.GetAABB().bLeft.x < rb.GetAABB().tRight.x
				&& rigidBody.GetAABB().tRight.x > rb.GetAABB().bLeft.x
				&& abs(rigidBody.GetAABB().bLeft.y - rb.GetAABB().tRight.y) <= groundedTol)
			{
				if (abs(rigidBody.GetCurrentVelocity().y) < groundedTol) return true;
			}
		}
	}
	return false;
}

void PhysicsManager::Update(float dt)
{
	std::list<Rigidbody2DComponent> ::iterator it;
	for (it = rigidBodies.begin(); it != rigidBodies.end(); ++it)
		std::cout << '\t' << it->GetCurrentVelocity().x;
	std::cout << '\n';


	IntegrateBodies(dt);
}

void PhysicsManager::IntegrateBodies(float dT)
{
	std::list<Rigidbody2DComponent> ::iterator it;

	for (it = rigidBodies.begin(); it != rigidBodies.end(); ++it)
		it->Integrate(dT);
}
