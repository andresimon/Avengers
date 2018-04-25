#pragma once

#include "GameObject.h"

#include "iostream"
#include <map>
#include <iterator>

class GameObjectManager
{
	public:
		GameObject * CreateObject();
		GameObject * CreateObject(std::string name);

		void Update(float msec);
		void Awake();
		void Start();
		
		//void LateUpdate(float msec);

		GameObject* GetObjectByName(std::string name);

	private:
		std::map<int, GameObject*> m_Objects;
		static int nextObjectID;
};
