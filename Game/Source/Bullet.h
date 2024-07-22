#pragma once
#include "Actor.h"

class Bullet : public Actor {
public:
	Bullet() = default;
	Bullet(const Transform& transform) : Actor(transform) {}
	Bullet(const Transform& transform, Model* model) : Actor(transform, model) {}
	Bullet(float speed, const Transform& transform, Model* model) : Actor(transform, model), m_speed{ speed } {}

	void Update(float dt) override;
	virtual void OnCollision(Actor* actor);
private:
	float m_speed = 0;
};