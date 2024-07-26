#pragma once

class Engine;
class Renderer;
class Scene;

class Game {
public:
	Game() = default;
	Game(Engine* engine) : m_engine{ engine } {}

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(Renderer& renderer) = 0;

	int GetLevel() const { return m_level; }
	void AddLevel() {  m_level++; }

	int GetBombs() const { return m_bombs; }
	void AddBomb() { m_bombs++; }
protected:
	int m_level = 0;
	int m_bombs = 0;

	Engine* m_engine{ nullptr };
	Scene* m_scene{ nullptr };
};