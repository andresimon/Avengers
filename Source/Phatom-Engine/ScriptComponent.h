#pragma once

//#include <SFML/Graphics.hpp>

#include "BaseComponent.h"

class ScriptComponent : public BaseComponent
{
	public:
		ScriptComponent() {}
	//	~ScriptComponent() {};

		virtual void Update(float deltaTime) {}
	//	void Update(float deltaTime);
		virtual void Awake();
		virtual void Start();

	private:
	

};

