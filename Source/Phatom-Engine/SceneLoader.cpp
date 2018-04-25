#include "SceneLoader.h"

#include <iostream>
#include <fstream>

//#include <cstdio> // assert

#include "JSON\prettywriter.h" 

#include <cstdlib> //EXIT_F

#include <JSON\istreamwrapper.h>
#include <JSON\error\en.h>
//#include <JSON\writer.h>
//#include <JSON\stringbuffer.h>
//#include <JSON\ostreamwrapper.h>

#include "Phantom.h"
#include "TransformComponent.h"
#include "SpriteRenderComponent.h"
#include "Rigidbody2DComponent.h"
#include "ScriptComponent.h"

#include <string>

void SceneLoader::operator=(SceneLoader & const) {}

SceneLoader & SceneLoader::GetInstance()
{
	static SceneLoader instance;
	return instance;
}

void SceneLoader::Initialize()
{
}

int SceneLoader::LoadContent(const char* fileName)
{
		////
	//std::ifstream ifs{ R"(C:\[George Brown College]\[06 - 2018 Winter]\GAME ENGINE DEVELOPMENT II CRN-48634-201702\test.json)" };
	std::ifstream ifs(fileName);
		if (!ifs.is_open())
		{
			std::cerr << fileName << "Could not open file for reading!\n";
			return EXIT_FAILURE;
		}

		IStreamWrapper isw{ ifs };

		Document document{};
		document.ParseStream(isw);

	
		if (document.HasParseError())
		{
			//std::cout << "Error  : " << document.GetParseError_En() << '\n'
			std::cout << "Error  : " << GetParseError_En(document.GetParseError()) << '\n'
				<< "Offset : " << document.GetErrorOffset() << '\n';
			return EXIT_FAILURE;
		}

		//std::unordered_map<std::string, std::string> _values;
		for (auto obj = document.MemberBegin(); obj != document.MemberEnd(); ++obj)
		{
			if (!obj->value.IsObject())
				continue;

			GameObject *go = Phantom::_gameObjectManager.CreateObject(obj->name.GetString());

			/* Transform */
			Value::ConstMemberIterator transform = obj->value.FindMember("Transform");
			if (transform != obj->value.MemberEnd())
			{
				if (ValidateTransform(obj->name.GetString(), transform))
				{
					float x = transform->value["Position"]["x"].GetFloat();
					float y = transform->value["Position"]["y"].GetFloat();

					go->addComponent(ComponentTypes::TransformComponentType,
						std::make_shared<TransformComponent>(sf::Vector2f(x,y)));
				}
			}
			
			/* SpriteRender */
			Value::ConstMemberIterator spRender = obj->value.FindMember("Sprite");
			if (spRender != obj->value.MemberEnd())
			{
				if (ValidateSpriteRender(obj->name.GetString(), spRender))
				{
					std:string image = spRender->value["Image"].GetString();

					if (ValidateSpriteRenderTexture(obj->name.GetString(), spRender))
					{
						float left   = spRender->value["TextureRect"]["left"].GetFloat();
						float top    = spRender->value["TextureRect"]["top"].GetFloat();
						float width  = spRender->value["TextureRect"]["width"].GetFloat();
						float height = spRender->value["TextureRect"]["height"].GetFloat();

						go->addComponent(ComponentTypes::SpriteRenderComponentType,
							std::make_shared<SpriteRenderComponent>(image, sf::IntRect(left, top, width, height)) );
					}
					else
					{
						go->addComponent(ComponentTypes::SpriteRenderComponentType,
							std::make_shared<SpriteRenderComponent>(image) );
					}
				}
			}

			/* Rigidbody */
			Value::ConstMemberIterator rigidbody = obj->value.FindMember("Rigidbody");
			if (rigidbody != obj->value.MemberEnd())
			{
				if (ValidateRigidbody(obj->name.GetString(), rigidbody))
				{
					float mass		 = rigidbody->value["Mass"].GetFloat();
					float bounciness = rigidbody->value["Bounciness"].GetFloat();
					bool gravity	 = rigidbody->value["Use_Gravity"].GetBool();

					go->addComponent(ComponentTypes::Rigidbody2DComponentType,
						std::make_shared<Rigidbody2DComponent>(mass, bounciness, gravity));
				}
			}
		}

	

		// Iterating object members
		static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
		for (Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr)
		{
			printf("Type of member %s is %s\n", itr->name.GetString(), kTypeNames[itr->value.GetType()]);
		}



	//	const std::string jsonStr{ buffer.GetString() };

	//	std::cout << jsonStr << '\n';
}

void SceneLoader::UnloadContent()
{
}

bool SceneLoader::ValidateTransform(std::string rootName, Value::ConstMemberIterator obj)
{
	bool result = true;
	const char* objName = rootName.c_str();

	// Validate Position key
	Value::ConstMemberIterator position = obj->value.FindMember("Position");
	if (position == obj->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid Transform component", objName);
		return false;
	}

	// Validate Position::x key
	Value::ConstMemberIterator posX = position->value.FindMember("x");
	if (posX == position->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid Transform component: missing Position x  \n", objName);
		result = false;
	}

	// Validate Position::y key
	Value::ConstMemberIterator posY = position->value.FindMember("y");
	if (posY == position->value.MemberEnd())
	{
		
		printf("Object %s  does not contain a valid Transform component: missing Position y \n", objName);
		result = false;
	}

	return result;
}

bool SceneLoader::ValidateSpriteRender(std::string rootName, Value::ConstMemberIterator obj)
{
	bool result = true;
	const char* objName = rootName.c_str();

	// Validate Image key
	Value::ConstMemberIterator image = obj->value.FindMember("Image");
	if (image == obj->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid SpriteRenderer component: missing image", objName);
		return false;
	}

	return result;
}

bool SceneLoader::ValidateSpriteRenderTexture(std::string rootName, Value::ConstMemberIterator obj)
{
	bool result = true;
	const char* objName = rootName.c_str();

	// Validate TextureRect key
	Value::ConstMemberIterator textureRect = obj->value.FindMember("TextureRect");
	if (textureRect == obj->value.MemberEnd())
	{
		return false;
	}

	// Validate TextureRect::left key
	Value::ConstMemberIterator left = textureRect->value.FindMember("left");
	if (left == textureRect->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid SpriteRenderer component: missing textureRect left \n", objName);
		result = false;
	}

	// Validate TextureRect::top key
	Value::ConstMemberIterator top = textureRect->value.FindMember("top");
	if (top == textureRect->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid SpriteRenderer component: missing textureRect top \n", objName);
		result = false;
	}

	// Validate TextureRect::width key
	Value::ConstMemberIterator width = textureRect->value.FindMember("width");
	if (width == textureRect->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid SpriteRenderer component: missing textureRect width \n", objName);
		result = false;
	}

	// Validate TextureRect::height key
	Value::ConstMemberIterator height = textureRect->value.FindMember("height");
	if (height == textureRect->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid SpriteRenderer component: missing textureRect height \n", objName);
		result = false;
	}

	return result;
}

bool SceneLoader::ValidateRigidbody(std::string rootName, Value::ConstMemberIterator obj)
{
	bool result = true;
	const char* objName = rootName.c_str();

	// Validate Mass key
	Value::ConstMemberIterator mass = obj->value.FindMember("Mass");
	if (mass == obj->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid Rigidbody component: missing mass \n", objName);
		result = false;
	}

	// Validate Bounciness key
	Value::ConstMemberIterator bounciness = obj->value.FindMember("Bounciness");
	if (bounciness == obj->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid Rigidbody component: missing bounciness \n", objName);
		result = false;
	}

	// Validate Gravity key
	Value::ConstMemberIterator gravity = obj->value.FindMember("Use_Gravity");
	if (gravity == obj->value.MemberEnd())
	{
		printf("Object %s  does not contain a valid Rigidbody component: missing use_gravity \n", objName);
		result = false;
	}

	return result;
}