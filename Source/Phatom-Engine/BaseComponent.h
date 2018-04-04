#pragma once

//
//  BaseComponent.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

//#include <stdio.h>
#include <memory>

#include "BaseMessage.h"

#include "ComponentTypes.h"

class GameObject;

class BaseComponent 
{
	public:
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

		inline void setParent(GameObject* parent) { this->m_Parent = parent; }

	//	inline void SetParent(GameObject* parent) { m_Parent = parent; }
	
	protected:
		int parentID;
		GameObject* m_Parent;

		
};