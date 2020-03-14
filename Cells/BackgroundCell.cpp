#include "BackgroundCell.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

BackgroundCell::BackgroundCell()
{
	float r1 = static_cast<float> (rand()) / static_cast <float> (RAND_MAX) - 0.5;
	float r2 = static_cast<float> (rand()) / static_cast <float> (RAND_MAX) - 0.5;
	accelerate(r1 * 10, r2 * 10);
}

void BackgroundCell::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape shape(size);

	shape.setFillColor(sf::Color(10, 50, 80,80));
	
	
	target.draw(shape, states);
}

void BackgroundCell::update_current(sf::Time dt)
{
	float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	accelerate(r1, r2);
}

void BackgroundCell::react_with(BackgroundCell& other)
{
}

void BackgroundCell::react_with(FoodCell& other)
{
}

void BackgroundCell::react_with(PlayerCell& other)
{
}

void BackgroundCell::react(Cell& cell)
{
}

BackgroundCell::~BackgroundCell()
= default;
