#pragma once
#include <cmath>

namespace Math {
	constexpr float Pi = 3.14159265359f; //180
	constexpr float TwoPi = 6.28318530718f; //360
	constexpr float HalfPi = 1.57079632679f; //90

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }

	inline float Sin(float radians) {
		return std::sinf(radians);
	}

	inline float Cos(float radians) {
		return std::cosf(radians);
	}

	inline float Sqrt(float radians) {
		return std::sqrtf(radians);
	}

	inline float Tan(float radians) {
		return std::tanf(radians);
	}

	inline float Atan2(float y, float x) {
		return std::atan2f(y, x);
	}

	template<typename T>
	T Max(T a, T b) {
		return (a > b) ? a : b;
	}

	template<typename T>
	T Min(T a, T b) {
		return (a < b) ? a : b;
	}

	template<typename T>
	T Abs(T value) {
		return (value < 0) ? -value : value;
	}

	template<typename T>
	T Clamp(T value, T min, T max) {
		return (value < min) ? min : (value > max) ? max : value;
	}

	inline int Wrap(int value, int max) {
		return value % max + ((value < 0) ? max : 0);
	}

	inline float Wrap(float value, float max) {
		return std::fmodf(value, max) + ((value < 0) ? max : 0);
	}
}