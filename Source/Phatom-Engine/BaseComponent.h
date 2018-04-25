#pragma once

//#include <memory>

#include "ComponentTypes.h"

class GameObject;

class BaseComponent 
{
	public:
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void Update(float deltaTime) {}
		virtual void LateUpdate() {}

		inline GameObject* GetOwner() { return this->m_Owner; }
		inline void SetOwner(GameObject* owner) { this->m_Owner = owner; }

	protected:
		//int parentID;
		GameObject* m_Owner;

		
};