#pragma once

#include <vector>

#include "GameObject.h"

class SceneGraph
{
	public:

		SceneGraph();

		std::vector<GameObject*> sceneObjects;

		void AddObject(GameObject* s);

		void Update(float msec);

};


