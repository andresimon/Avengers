#pragma once

#include <JSON\document.h>
#include <JSON\reader.h>

//#include <iostream>
//#include <unordered_map>
#include <map>

#include "GameObject.h"

using namespace rapidjson;

using namespace std;
class SceneLoader
{
	public:
		inline ~SceneLoader() {};
		static SceneLoader &GetInstance();

		void Initialize();

		int LoadContent(const char* fileName);
		void UnloadContent();

		bool ValidateTransform(std::string rootName, Value::ConstMemberIterator obj);
		bool ValidateSpriteRender(std::string rootName, Value::ConstMemberIterator obj);
		bool ValidateSpriteRenderTexture(std::string rootName, Value::ConstMemberIterator obj);
		bool ValidateRigidbody(std::string rootName, Value::ConstMemberIterator obj);

		//void AddScreen(GameScreen *screen);

		std::map<std::string, GameObject> sceneObjects;

	private:
		inline SceneLoader() {}
		SceneLoader(SceneLoader& const);
		void operator=(SceneLoader& const);

	//	GameScreen* newScreen;
	//	FileManager file;

	//	std::vector<std::vector<std::string> > attributes;
		//std::vector<std::vector<std::string> > contents;
};


