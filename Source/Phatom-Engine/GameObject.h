#pragma once

#include <vector>
#include <map>

//#include <SFML/System/Time.hpp>

#include <memory>
#include "Matrices.h" // removed fter converting

#include "BaseComponent.h"

class GameObject 
{
	public:
		GameObject(int uniqueID) : m_UniqueID(uniqueID), m_Parent(NULL), name("NO NAME") {}
		~GameObject(void) {}

		int GetObjectID() const { return m_UniqueID; }

		void addComponent(ComponentTypes type, std::shared_ptr<BaseComponent> compPtr);

		inline void SetParent(GameObject* parent) { m_Parent = parent; }
		inline GameObject* GetParent() { return this->m_Parent;  }
		void AddChild(GameObject* child);

		void Update(float msec);
		void Awake();
		void Start();
/*
		void SetTransform(const Matrix4 &matrix) { transform = matrix; }
		Matrix4 GetTransform() { return transform; }
		Matrix4 GetWorldTransform() { return worldTransform; }
		*/

		std::shared_ptr<BaseComponent> GetComponent(ComponentTypes type);
		inline std::string GetName() { return this->name; }
		inline void SetName(std::string name) { this->name = name; }

	protected:
		std::string name;
		
//		Matrix4 worldTransform;
	//	Matrix4 transform;

		//std::vector<BaseComponent*> m_Components;

		std::map<ComponentTypes, std::shared_ptr<BaseComponent>> components;
		GameObject* m_Parent;

	private: 

		int m_UniqueID;

		//GameObject* m_Owner;
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
