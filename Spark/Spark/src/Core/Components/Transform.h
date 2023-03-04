#pragma once
#include "pch.h"

#include "Core/Actor.h"


class GPUContext;


class Actor;

class Component {
public:
	bool priorityRendering = false;
	virtual void BeginPlay(Actor* actor);
	virtual void Update(Actor* actor);
	virtual void Render(GPUContext* context, Actor* actor);
};

class Transform : public Component {
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	virtual void BeginPlay(Actor* actor) {}
	virtual void Update(Actor* actor) {}
	virtual void Render(GPUContext* context, Actor* actor) {}
	glm::vec3 getForward() {
		return glm::vec3(cos(this->rotation.x) * sin(this->rotation.y), -sin(this->rotation.x), cos(this->rotation.x) * cos(this->rotation.y));
	}
	glm::vec3 getRight() {
		return glm::vec3(cos(this->rotation.y), 0, -sin(this->rotation.y));
	}
	glm::vec3 getUp() {
		return glm::cross(this->getForward(), this->getRight());
	}
};


class Actor {
public:
	Transform* transform;
	std::vector<Component*> components;
	void addComponent(Component* component);
};

