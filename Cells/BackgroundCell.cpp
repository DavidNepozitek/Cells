#include "BackgroundCell.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

BackgroundCell::BackgroundCell(const float size): Cell(size), shape_(size)
{
	// Set initial acceleration
	const auto r1 = static_cast<float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	const auto r2 = static_cast<float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	accelerate(r1, r2);

	shape_.setFillColor(sf::Color(10, 50, 80, 80));
}

void BackgroundCell::draw_current(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}

void BackgroundCell::update_current(const sf::Time dt)
{
	// Set random mini-movements
	const auto r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	const auto r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	accelerate(r1 * 0.5f, r2 * 0.5f);
	move_with_resistance(dt);
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

void BackgroundCell::react_with(NeutralCell& other)
{
}
