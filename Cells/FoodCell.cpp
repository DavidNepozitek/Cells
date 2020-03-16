#include "FoodCell.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "PlayerCell.h"
#include "NeutralCell.h"
#include "Utility.h"

FoodCell::FoodCell(const float size): Cell(size)
{
	
}

void FoodCell::draw_current(sf::RenderTarget& target, const sf::RenderStates states) const
{
	sf::CircleShape shape(size);
	shape.move(-size, -size);
	shape.setFillColor(sf::Color(100, 250, 150));

	target.draw(shape, states);
}

void FoodCell::update_current(const sf::Time dt)
{
	if (death_marked)
	{
		size -= dt.asSeconds() * size * 5;
	}
	
	move_with_resistance(dt);
}

void FoodCell::react_with(BackgroundCell& other)
{
}

void FoodCell::react_with(FoodCell& other)
{
	const auto dist = get_cells_distance(*this, other);

	if (dist > 0.01) return;
	
	if (death_marked || other.death_marked) return;
	if (other.size >= size)
	{
		other.size += sqrt(size);
		death_marked = true;
	} else
	{
		size += sqrt(other.size);
		other.death_marked = true;
	}
}

void FoodCell::react_with(PlayerCell& other)
{
	other.react_with(*this);
}

void FoodCell::react(Cell& cell)
{
	cell.react_with(*this);
}

FoodCell::~FoodCell()
= default;

void FoodCell::react_with(NeutralCell& other)
{
	other.react_with(*this);
}
