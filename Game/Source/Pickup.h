#pragma once
#include "Actor.h"

class Pickup : public Actor {
public:
	Pickup() = default;
	Pickup(const Transform& transform) : Actor(transform) {}
	Pickup(const Transform& transform, Model* model, int type) : Actor(transform, model), m_type{ type } {}
	
	void OnCollision(Actor* actor) override;
protected:
	int m_type = 0;
};