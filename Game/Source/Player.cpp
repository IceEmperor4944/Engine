#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"

#include <iostream>

void Player::Update(float dt) {
	Vector2 direction{ 0,0 };
	if (INPUT.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
	if (INPUT.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;

	if (INPUT.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (INPUT.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

	/*if (INPUT.GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (INPUT.GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(100) * dt;*/


	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)RENDERER.GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)RENDERER.GetHeight());

	//fire
	m_fireTimer -= dt;
	if (INPUT.GetMouseButtonDown(0) && m_fireTimer <= 0 /*&& !INPUT.GetPrevKeyDown(SDL_SCANCODE_SPACE)*/) {
		for (int i = 0; i < m_shotCount; i++) {
			AUDIO.PlaySound("beep.wav");

			m_fireTimer = 0.5f * m_fireModifier;

			//shoot at mouse pos
			Vector2 direction = INPUT.GetMousePosition() - m_transform.position;
			float angle = direction.Angle() + Math::DegToRad(360 / m_shotCount * (float)i);

			Model* model = new Model{ GameData::bulletPoints, Color{ 1, 1, 0 } };
			/*Vector2 v1{ m_transform.position.x + (16 * m_transform.scale), m_transform.position.y + (16 * m_transform.scale) };
		Vector2 v2{ m_transform.position.x + (16 * m_transform.scale), m_transform.position.y - (16 * m_transform.scale) };
		Transform transform1{ v1.Rotate(m_transform.rotation), m_transform.rotation, 1.0f };
		Transform transform2{ v2.Rotate(m_transform.rotation), m_transform.rotation, 1.0f };

		Bullet* bullet1 = new Bullet(800, transform1, model);
		Bullet* bullet2 = new Bullet(800, transform2, model);
		bullet1->SetLifespan(1.0f);
		bullet2->SetLifespan(1.0f);
		bullet1->SetTag("Player");
		bullet2->SetTag("Player");
		m_scene->AddActor(bullet1);
		m_scene->AddActor(bullet2);*/

			Transform transform{ m_transform.position, angle, 1.0f };
			auto bullet = std::make_unique<Bullet>(800.0f, transform, model, false);
			bullet->SetLifespan(1.0f);
			bullet->SetTag("Bullet");
			m_scene->AddActor(std::move(bullet));
		}
	}

	if (INPUT.GetMouseButtonDown(2) && m_fireTimer <= 0 && !INPUT.GetPrevMouseButtonDown(2) && m_scene->GetGame()->GetBombs() > 0) {
		m_fireTimer = 1.5f * m_fireModifier;

		//shoot at mouse pos
		Vector2 direction = INPUT.GetMousePosition() - m_transform.position;
		float angle = direction.Angle();

		Model* model = new Model{ GameData::bigBulletPoints, Color{ 0, 1, 1 } };
		
		Transform transform{ m_transform.position, angle, 1.0f };
		auto bigBullet = std::make_unique<Bullet>(800.0f, transform, model, true);
		bigBullet->SetLifespan(1.0f);
		bigBullet->SetTag("Bullet");
		m_scene->AddActor(std::move(bigBullet));
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor) {
	if (actor->GetTag() == "Enemy") {
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
	}
}