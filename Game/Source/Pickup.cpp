#include "Pickup.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"

void Pickup::OnCollision(Actor* actor) {
	switch (m_type) {
	case 1:
		if (actor->GetTag() == "Player") {
			dynamic_cast<Player*>(actor)->SetFireModifier(0.9f);
			m_destroyed = true;
		}
		break;
	case 2:
		if (actor->GetTag() == "Player") {
			m_scene->GetGame()->AddBomb();
			m_destroyed = true;
		}
		break;
	case 3:
		if (actor->GetTag() == "Player") {
			dynamic_cast<Player*>(actor)->AddShot();
			m_destroyed = true;
		}
		break;
	default:
		break;
	}
}