#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Font.h"
#include "Text.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[]) {
	g_engine.Initilize();

	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		game->Update(TIME.GetDeltaTime());

		// clear screen
		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();

		game->Draw(RENDERER);
		PS.Draw(RENDERER);

		RENDERER.EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}

/*
	std::vector<Particle> particles;
	float offset = 0;

	//actor
	Model* model = new Model{ GameData::shipPoints, Color{1, 1, 1} };
	Scene* scene = new Scene();

	Transform transform{ {400,300}, 0, 3 };
	Player* player = new Player(800, transform, model);
	player->SetDamping(2.5f);
	player->SetTag("Player");
	scene->AddActor(player);
	
	float spawnTimer = 2;

	//main loop
	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		//input
		//update
		//draw

		//INPUT
		spawnTimer -= TIME.GetDeltaTime();
		if (spawnTimer <= 0) {
			auto* enemyModel = new Model{ GameData::shipPoints, Color{1, 0, 0} };
			auto* enemy = new Enemy(400, { {RENDERER.GetWidth(),RENDERER.GetHeight()}, 0, 2 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);

			spawnTimer = 2;
		}

		//UPDATE
		scene->Update(TIME.GetDeltaTime());

		Vector2 mousePosition = INPUT.GetMousePosition();
		if (INPUT.GetMouseButtonDown(0)) {
			for (int i = 0; i < 20; i++) {
				particles.push_back(Particle{ mousePosition,
					{randomf(-100.0f,100.0f),
					randomf(-100.0f,100.0f)},
					randomf(1,5),
					static_cast<uint8_t>(random(0,255)),
					static_cast<uint8_t>(random(0,255)),
					static_cast<uint8_t>(random(0,255)),
					static_cast<uint8_t>(random(0,255))
					});
			}
		}

		for (Particle& particle : particles) {
			particle.Update(TIME.GetDeltaTime());

			if (particle.position.x > 1000) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 1000;
			if (particle.position.y > 1000) particle.position.y = 0;
			if (particle.position.y < 0) particle.position.y = 1000;
		}

		//if (INPUT.GetKeyDown(SDL_SCANCODE_Q) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_Q)) { AUDIO.PlaySound("bass.wav"); }
		//if (INPUT.GetKeyDown(SDL_SCANCODE_W) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_W)) { AUDIO.PlaySound("clap.wav"); }
		//if (INPUT.GetKeyDown(SDL_SCANCODE_E) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_E)) { AUDIO.PlaySound("close-hat.wav"); }
		//if (INPUT.GetKeyDown(SDL_SCANCODE_R) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_R)) { AUDIO.PlaySound("cowbell.wav"); }
		//if (INPUT.GetKeyDown(SDL_SCANCODE_T) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_T)) { AUDIO.PlaySound("snare.wav"); }
		//if (INPUT.GetKeyDown(SDL_SCANCODE_Y) && !INPUT.GetPrevKeyDown(SDL_SCANCODE_Y)) { AUDIO.PlaySound("open-hat.wav"); }

		////DRAW
		// clear screen
		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();

		RENDERER.SetColor(255, 255, 255, 0);
		for (Particle particle : particles) {
			particle.Draw(RENDERER);
		}

		RENDERER.SetColor(255, 255, 255, 0);
		scene->Draw(RENDERER);

		// show screen
		RENDERER.EndFrame();
	}

	return 0;
}
*/