#pragma once
#include "Actor.h"

class Pickup : public Actor {
public:
	Pickup() = default;
	Pickup(const Transform& transform) : Actor(transform) {}
	Pickup(const Transform& transform, Model* model) : Actor(transform, model) {}
	
	void OnCollision(Actor* actor) override;
protected:

};