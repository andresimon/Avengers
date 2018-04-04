#pragma once

#include <vector>
#include <map>

#include "Matrices.h" 

#include "BaseComponent.h"

class GameObject 
{
	public:
		GameObject(int uniqueID) : m_UniqueID(uniqueID), m_Parent(NULL) {}
		~GameObject(void);

		int GetObjectID() const { return m_UniqueID; }

		void AddComponent(BaseComponent* component);
		void addComponent(ComponentTypes type, std::shared_ptr<BaseComponent> compPtr);

		void SetParent(GameObject& parent) { m_Parent = &parent; }
		void AddChild(GameObject* child);

		void Update(float msec);
		void Awake();
		void Start();
		void LateUpdate(float msec);

		void SetTransform(const Matrix4 &matrix) { transform = matrix; }
		Matrix4 GetTransform() { return transform; }
		Matrix4 GetWorldTransform() { return worldTransform; }

		std::shared_ptr<BaseComponent> GetComponent(ComponentTypes type);

	protected:
		Matrix4 worldTransform;
		Matrix4 transform;

		std::vector<BaseComponent*> m_Components;

		std::map<ComponentTypes, std::shared_ptr<BaseComponent>> components;

	private: 

		int m_UniqueID;

		GameObject* m_Parent;
		std::vector<GameObject*> m_Children;

		

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
