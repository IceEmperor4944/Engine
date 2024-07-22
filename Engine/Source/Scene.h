#pragma once
#include <list>

class Renderer;
class Actor;
class Game;

class Scene {
public:
	//Scene() = default;
	Scene(Game* game) : m_game{ game } {}

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(Actor* actor);
	void RemoveAll();

	template<typename T>
	T* GetActor();

	Game* GetGame() { return m_game; }
protected:
	std::list<Actor*> m_actors;

	Game* m_game{ nullptr };
};

template<typename T>
T* Scene::GetActor() {
	for (Actor* actor : m_actors) {
		T* result = dynamic_cast<T*>(actor);
		if (result) return result;
	}
	
	return nullptr;
}