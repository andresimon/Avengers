#include "GameObject.h"

#include "SpriteRenderComponent.h"

void GameObject::Awake() 
{
		
	std::map<ComponentTypes, std::shared_ptr<BaseComponent>>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
		(it->second)->Awake();
}

void GameObject::Start() 
{
	std::map<ComponentTypes, std::shared_ptr<BaseComponent>>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
		(it->second)->Start();
}

void GameObject::Update(float msec)
{/*
	if (m_Parent) { //This node has a parent...
		worldTransform = m_Parent->worldTransform * transform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = transform;
	}
	*/

	std::map<ComponentTypes, std::shared_ptr<BaseComponent>>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(it->second)->Update();
		(it->second)->Update(msec);
	}
}
/*
void GameObject::LateUpdate(float msec) {
	for (std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
		//(*i)->LateUpdate();
}
*/

std::shared_ptr<BaseComponent> GameObject::GetComponent(ComponentTypes type)
{
	std::map<ComponentTypes, std::shared_ptr<BaseComponent>>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		if (it->first == type){
			//printf("Found it!");
			return it->second;
		}
			
	}
	return nullptr;
}

void  GameObject::addComponent(ComponentTypes type, std::shared_ptr<BaseComponent> compPtr)
{
	GameObject* a = this;

	components.insert(std::pair<ComponentTypes, std::shared_ptr<BaseComponent>>(type, compPtr));
	compPtr->SetOwner(this);
}

void GameObject::AddChild(GameObject* child) {
	m_Children.push_back(child);
}

