#include "GameObject.h"

#include "SpriteRenderComponent.h"

GameObject::~GameObject(void)
{
}

void GameObject::Awake() {
	for (std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
		(*i)->Awake();
	}
	//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
	//        (*i)->Awake();
	//    }
}

void GameObject::Start() {
	for (std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
		(*i)->Start();
	}
	//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
	//        (*i)->Start();
	//    }
}

void GameObject::Update(float msec) 
{
	if (m_Parent) { //This node has a parent...
		worldTransform = m_Parent->worldTransform * transform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = transform;
	}

	for (std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
		(*i)->Update();
	}
	//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
	//        (*i)->Update(msec);
	//    }
	std::map<ComponentTypes, std::shared_ptr<BaseComponent>>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		//std::dynamic_pointer_cast<*it->first>(it->second)->render(renderTarget);
		(it->second)->Update();
	}
}

void GameObject::LateUpdate(float msec) {
	for (std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
		//(*i)->LateUpdate();
	}
	//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
	//        (*i)->LateUpdate(msec);
	//    }
}

std::shared_ptr<BaseComponent> GameObject::GetComponent(ComponentTypes type)
{
	std::map<ComponentTypes, std::shared_ptr<BaseComponent>>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		if (it->first == type)
			return it->second;
	}
	return nullptr;
}



void GameObject::AddComponent(BaseComponent* component)
{
	m_Components.push_back(component);
}


void  GameObject::addComponent(ComponentTypes type, std::shared_ptr<BaseComponent> compPtr)
{
	components.insert(std::pair<ComponentTypes, std::shared_ptr<BaseComponent>>(type, compPtr));
	compPtr->setParent(this);
}

void GameObject::AddChild(GameObject* child) {
	m_Children.push_back(child);
}

