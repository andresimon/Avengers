//
//  GameObjectManager.cpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#include "GameObjectManager.h"

#include <SFML/System/Time.hpp>


// Initialize our static unique objectID generator
int GameObjectManager::nextObjectID = 0;

void GameObjectManager::Awake() {
	for (std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
		(i->second)->Awake();
	}
}

void GameObjectManager::Start() {
	for (std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
		(i->second)->Start();
	}
}

GameObject * GameObjectManager::GetObjectByName(std::string name)
{
	for (std::map<int, GameObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it)
	{
		GameObject* go = it->second;
		if ( go->GetName() == name )
		{
			return go;
		}
	}
	return nullptr;
}

void GameObjectManager::Update(float msec) 
{
	for (std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
		(i->second)->Update(msec);
	}
}

/*
void GameObjectManager::LateUpdate(float msec) {
	for (std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
		(i->second)->LateUpdate(msec);
	}
}
*/

GameObject * GameObjectManager::CreateObject()
{
	GameObject* newObj = new GameObject(nextObjectID++);
	m_Objects[newObj->GetObjectID()] = newObj;

	return newObj;
}

GameObject * GameObjectManager::CreateObject(std::string name)
{
	GameObject * go = CreateObject();
	go->SetName(name);
	
	return go;
}

