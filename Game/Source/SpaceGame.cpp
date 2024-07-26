#include "SpaceGame.h"
#include "Engine.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "GameData.h"
#include "Font.h"
#include "Text.h"

bool SpaceGame::Initialize() {
    m_scene = new Scene(this);
    m_font = new Font();
    m_font->Load("arcadeclassic.ttf", 20);

    m_fontLarge = new Font();
    m_fontLarge->Load("arcadeclassic.ttf", 70);

    m_textLevel = new Text(m_font);
    m_textBombs = new Text(m_font);
    m_textTitle = new Text(m_fontLarge);

    return true;
}

void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt) {
    switch (m_state)
    {
    case State::Title:
        
        if (INPUT.GetKeyDown(SDL_SCANCODE_SPACE)) {
            m_state = State::StartGame;
        }
        break;
    case State::StartGame:
        m_level = 0;
        m_bombs = 0;

        AUDIO.PlaySound("song.wav");

        m_state = State::StartLevel;
        break;
    case State::StartLevel:
        m_scene->RemoveAll();
        {
            Transform transform{ {400,300}, 0, 3 };
            Model* model = new Model{ GameData::playerPoints, Color{1, 1, 1} };
            auto player = std::make_unique<Player>(800.0f, transform, model);
            player->SetDamping(2.5f);
            player->SetTag("Player");
            m_scene->AddActor(std::move(player));
        }

        m_spawnTime = 3;
        m_spawnTimer = m_spawnTime;

        m_state = State::Game;
        break;
    case State::Game:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0) {
            m_spawnTime *= 0.99f;
            m_spawnTimer = m_spawnTime;

            //create enemy
            auto* enemyModel = new Model{ GameData::enemyPoints, Color{1, 0, 0} };
            auto enemy = std::make_unique<Enemy>(400.0f, Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, enemyModel);
            enemy->SetDamping(1.0f);
            enemy->SetTag("Enemy");
            m_scene->AddActor(std::move(enemy));

            // create pickup
            auto* pickupModel = new Model{ GameData::pickupPoints, Color{1, 0, 1} };
            auto pickup = std::make_unique<Pickup>(Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, pickupModel, 1);
            pickup->SetTag("Pickup");
            m_scene->AddActor(std::move(pickup));

            m_pickupCount--;
        }

        if (m_pickupCount == 5 /*|| m_pickupCount == 7*/) {
            // create bomb
            auto* bombModel = new Model{ GameData::pickupPoints, Color{0, 1, 0} };
            auto bombPick = std::make_unique<Pickup>(Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, bombModel, 2);
            bombPick->SetTag("Pickup");
            m_scene->AddActor(std::move(bombPick));

            m_pickupCount = 4;
        }

        if (m_pickupCount == 1) {
            // create splitter
            auto* shotModel = new Model{ GameData::pickupPoints, Color{0, 0, 1} };
            auto shot = std::make_unique<Pickup>(Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, shotModel, 3);
            shot->SetTag("Pickup");
            m_scene->AddActor(std::move(shot));

            m_pickupCount = 11;
        }

        break;
    case State::PlayerDead:
        /*m_stateTimer -= dt;
        if (m_stateTimer <= 0) m_state = State::StartLevel;*/
        break;
    case State::GameOver:
        m_scene->RemoveAll();

        m_stateTimer -= dt;
        if (m_stateTimer <= 0) m_state = State::Title;
        break;
    default:
        break;
    }

    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer) {
    switch (m_state)
    {
    case State::Title:
        //draw title text
        m_textTitle->Create(renderer, "Cubis", { 1, 0, 0, 1 });
        m_textTitle->Draw(renderer, renderer.GetWidth() / 2, renderer.GetHeight() / 2);
        break;
    case State::Game:
    {
        //draw level
        std::string text = "Level " + std::to_string(m_level);
        m_textLevel->Create(renderer, text, { 0, 1, 0, 1 });
        m_textLevel->Draw(renderer, 20, 20);

        //draw bombs
        text = "Bombs " + std::to_string(m_bombs);
        m_textLevel->Create(renderer, text, { 0, 1, 0, 1 });
        m_textLevel->Draw(renderer, RENDERER.GetWidth() - 100, 20);
    }
        break;
    case State::GameOver:
        //draw game over text
        m_textTitle->Create(renderer, "Game Over", { 1, 0, 0, 1 });
        m_textTitle->Draw(renderer, renderer.GetWidth() / 2, renderer.GetHeight() / 2);
        break;
    default:
        break;
    }

    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDeath() {
    m_stateTimer = 5.0f;
    AUDIO.PlaySound("trombone.wav");
    m_state = State::GameOver;
}