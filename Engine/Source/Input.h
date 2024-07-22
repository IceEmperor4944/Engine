#pragma once

#include "Vector2.h"
#include <vector>
#include <array>

class Input {
public:
	Input() = default;
	~Input() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	bool GetKeyDown(uint8_t key) { return m_keyboardState[key]; }
	bool GetPrevKeyDown(uint8_t key) { return m_prevKeyboardState[key]; }

	Vector2 GetMousePosition() { return m_mousePosition; }
	bool GetMouseButtonDown(uint8_t button) { return m_mouseButtonState[button]; }
	bool GetPrevMouseButtonDown(uint8_t button) { return m_prevMouseButtonState[button]; }
private:
	std::vector<uint8_t> m_keyboardState;
	std::vector<uint8_t> m_prevKeyboardState;

	Vector2 m_mousePosition{ 0,0 };
	std::array<uint8_t, 3> m_mouseButtonState{ 0,0,0 };
	std::array<uint8_t, 3> m_prevMouseButtonState{ 0,0,0 };
};