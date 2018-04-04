#pragma once

#include "GameObject.h"

#include "iostream"
#include <map>
#include <iterator>

class GameObjectManager
{
	public:
		GameObject* CreateObject();

		void Update(float msec);
		void Awake();
		void Start();
		void LateUpdate(float msec);

	private:
		std::map<int, GameObject*> m_Objects;
		static int nextObjectID;
};
