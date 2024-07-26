#include "Bullet.h"
#include "Engine.h"
#include "GameData.h"
#include "Scene.h"

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
	if (actor->GetTag() == "Enemy" && m_isBig) {
		AUDIO.PlaySound("fireball.wav");
		for (int i = 1; i <= 12; i++) {
			float angle = Math::DegToRad(i * 30.0f);

			Model* model = new Model{ GameData::bulletPoints, Color{ 0, 1, 1 } };

			Transform transform{ m_transform.position, angle, 1.0f };
			auto bullet = std::make_unique<Bullet>(800.0f, transform, model, false);
			bullet->SetLifespan(1.0f);
			bullet->SetTag("Bullet");
			m_scene->AddActor(std::move(bullet));
		}
	}
}
