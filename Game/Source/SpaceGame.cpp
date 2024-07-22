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

    m_textScore = new Text(m_font);
    m_textLives = new Text(m_font);
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
        m_score = 0;
        m_lives = 3;

        m_state = State::StartLevel;
        break;
    case State::StartLevel:
        m_scene->RemoveAll();
        {
            Transform transform{ {400,300}, 0, 3 };
            Model* model = new Model{ GameData::playerPoints, Color{1, 1, 1} };
            Player* player = new Player(800, transform, model);
            player->SetDamping(2.5f);
            player->SetTag("Player");
            m_scene->AddActor(player);
        }

        m_spawnTime = 3;
        m_spawnTimer = m_spawnTime;

        m_state = State:: Game;
        break;
    case State::Game:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0) {
            m_spawnTime *= 0.9f;
            m_spawnTimer = m_spawnTime;

            //create enemy
            auto* enemyModel = new Model{ GameData::enemyPoints, Color{1, 0, 0} };
            auto* enemy = new Enemy(400, { {random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, enemyModel);
            enemy->SetDamping(1.0f);
            enemy->SetTag("Enemy");
            m_scene->AddActor(enemy);

            // create pickup
            auto* pickupModel = new Model{ GameData::pickupPoints, Color{1, 0, 1} };
            auto* pickup = new Pickup({ {random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, pickupModel);
            pickup->SetTag("Pickup");
            m_scene->AddActor(pickup);
        }
        break;
    case State::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) m_state = State::StartLevel;
        break;
    case State::GameOver:
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
        m_textTitle->Create(renderer, "Pew! Pew!", { 1, 0, 0, 1 });
        m_textTitle->Draw(renderer, renderer.GetWidth() / 2, renderer.GetHeight() / 2);
        break;
    case State::Game:
    {
        //draw score
        std::string text = "Score " + std::to_string(m_score);
        m_textScore->Create(renderer, text, { 0, 1, 0, 1 });
        m_textScore->Draw(renderer, 20, 20);
        //draw lives
        text = "Lives " + std::to_string(m_lives);
        m_textLives->Create(renderer, text, { 0, 1, 0, 1 });
        m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);
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
    m_lives--;
    m_state = (m_lives == 0) ? State::GameOver : State::PlayerDead;
    m_stateTimer = 3;
}