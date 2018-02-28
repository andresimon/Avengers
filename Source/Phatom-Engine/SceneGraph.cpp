#include "SceneGraph.h"

SceneGraph::SceneGraph() {}

void SceneGraph::AddObject(GameObject* s)
{
	sceneObjects.push_back(s);
}

void SceneGraph::Update(float msec)
{
	for (std::vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); ++i)
	{
		(*i)->Update(msec);
	}
}