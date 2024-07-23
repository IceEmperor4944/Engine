#pragma once
#include "Particle.h"
#include <vector>

class ParticleSystem {
public:
	ParticleSystem(int maxSize = 500) {
		m_particles.resize(maxSize);
	}

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddParticle(const Particle::Data& data);
private:
	Particle* GetFreeParticle();
private:
	std::vector<Particle> m_particles; //pool of particles
};