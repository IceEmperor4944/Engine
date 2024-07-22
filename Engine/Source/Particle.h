#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle {
	Vector2	position{ 0,0 };
	Vector2 velocity{ 0,0 };
	float lifespan = 0;

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 0;

	Particle() = default;
	Particle(Vector2 pos, Vector2 vel, float lifespan, uint8_t r, uint8_t g, uint8_t b, uint8_t a) : position{ pos }, velocity{ vel }, lifespan{ lifespan }, r{ r }, g{ g }, b{ b }, a{ a } {}
	
	void Update(float dt);
	void Draw(Renderer& renderer);
};