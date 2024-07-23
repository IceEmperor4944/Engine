#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt) {
	//create particle trail
	Particle::Data data{
		m_transform.position,
		Vector2{1,0}.Rotate(randomf(Math::TwoPi)) * 50,
		randomf(0.5f, 2.0f),
		255, 255, 255, 255
	};
	PS.AddParticle(data);

	m_velocity = Vector2{ 1,0 }.Rotate(m_transform.rotation) * m_speed;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)RENDERER.GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)RENDERER.GetHeight());

	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor) {

}
