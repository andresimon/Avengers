#pragma once

//#include <stdio.h>
#include "GameObject.h"
#include "iostream"
#include <map>
//#include <list>
#include <iterator>

class GameObjectManager
{
	public:
		bool SendMessage(BaseMessage* msg);
		GameObject* CreateObject();

		void Update(float msec);
		void Awake();
		void Start();
		void LateUpdate(float msec);

	private:
		std::map<int, GameObject*> m_Objects;
		static int nextObjectID;
};
