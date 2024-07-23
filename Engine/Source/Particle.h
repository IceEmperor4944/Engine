#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle {
	struct Data {
		Vector2	position{ 0,0 };
		Vector2 velocity{ 0,0 };
		float lifespan = 0;
		uint8_t r{ 255 }, g{ 255 }, b{ 255 }, a{ 0 };
	};

	Vector2	position{ 0,0 };
	Vector2 velocity{ 0,0 };
	float lifespan = 0;
	uint8_t r{ 255 }, g{ 255 }, b{ 255 }, a{ 0 };
	bool isActive{ false };

	Particle() = default;
	Particle(Vector2 pos, Vector2 vel, float lifespan, uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
		position{ pos },
			velocity{ vel },
			lifespan{ lifespan },
			r{ r }, g{ g }, b{ b }, a{ a }
	{}
	
	void Initialize(const Data& data);

	void Update(float dt);
	void Draw(Renderer& renderer);
};