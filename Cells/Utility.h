#pragma once
#include <cmath>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Entity.h"
#include "Cell.h"


inline void center_origin(sf::Text& text)
{
	const auto bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

inline float length(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

inline float get_cells_distance(Cell& a, Cell& b)
{
	const auto pos_a = a.get_world_position();
	const auto pos_b = b.get_world_position();
	const auto x = pos_a.x - pos_b.x;
	const auto y = pos_a.y - pos_b.y;
	return sqrt(x*x + y * y) - a.size - b.size;
}