#pragma once
#include "Renderer.h"
#include <string>

class Font
{
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontSize);

	_TTF_Font* GetFont() const { return m_ttfFont; }
private:
	_TTF_Font* m_ttfFont{ nullptr };
};