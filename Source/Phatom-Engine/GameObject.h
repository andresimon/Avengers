#pragma once

#include <vector>

#include "Matrices.h" 

#include "BaseMessage.h"
#include "BaseComponent.h"

class GameObject 
{
	public:
		GameObject(int uniqueID) : m_UniqueID(uniqueID), m_Parent(NULL) {}
		~GameObject(void);

		int GetObjectID() const { return m_UniqueID; }

		void AddComponent(BaseComponent* component);

		bool SendMessage(BaseMessage* msg);

		void SetParent(GameObject& parent) { m_Parent = &parent; }
		void AddChild(GameObject* child);

		void Update(float msec);
		void Awake();
		void Start();
		void LateUpdate(float msec);

		void SetTransform(const Matrix4 &matrix) { transform = matrix; }
		Matrix4 GetTransform() { return transform; }
		Matrix4 GetWorldTransform() { return worldTransform; }

	protected:
		Matrix4 worldTransform;
		Matrix4 transform;

	private: 
		bool PassMessageToComponents(BaseMessage* msg);

		int m_UniqueID;

		GameObject* m_Parent;
		std::vector<GameObject*> m_Children;

		std::vector<BaseComponent*> m_Components;

public: // Members
	//Transform transform;    //local transform
};

///////
/*
#include <stdio.h>

#include "Transform.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <glm.hpp>
#include <matrix_transform.hpp>

*/
