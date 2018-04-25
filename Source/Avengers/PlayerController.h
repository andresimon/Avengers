#pragma once

#include "ScriptComponent.h"

#include <string>

class PlayerController : public ScriptComponent
{
public:
	PlayerController();
	~PlayerController() {};

	void Update(float msec);
	void Awake();
	void Start();

	std::string name;

private:
	void teste();
};
