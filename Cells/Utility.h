#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Entity.h"


inline void center_origin(sf::Text& text)
{
	const auto bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

inline float length(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}