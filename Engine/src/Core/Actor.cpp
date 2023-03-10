#include "CoreFramework.h"


void Component::BeginPlay(Actor* actor)
{
}

void Component::Update(Actor* actor)
{
}

void Component::Render(GPUContext* context, Actor* actor)
{
}


void Actor::addComponent(Component* component)
{
	this->components.push_back(component);
}