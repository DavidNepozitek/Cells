#include "NeutralCell.h"
#include "FoodCell.h"
#include "PlayerCell.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Utility.h"

void NeutralCell::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape shape(size);
	shape.move(-size, -size);
	shape.setFillColor(sf::Color(200, 50, 100));

	if (is_bigger)
	{
		shape.setOutlineColor(sf::Color(250, 20, 20));
	} else
	{
		shape.setOutlineColor(sf::Color(50, 200, 50));
	}

	shape.setOutlineThickness(2);

	target.draw(shape, states);
}

void NeutralCell::update_current(sf::Time dt)
{
	if (death_marked)
	{
		size -= dt.asSeconds() * size * 7;
		if (size < 0.5)
		{
			size = 0;
		}
		return;
	}

	const auto r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	const auto r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	accelerate((r1 * 120 * dt.asSeconds()) / size, (r2 * 120 * dt.asSeconds()) / size);
	accelerate(60 * dt.asSeconds() * get_velocity().x / (length(get_velocity()) * 9.f), 60 * dt.asSeconds() * get_velocity().y / (length(get_velocity()) * 9.f));
	move_with_resistance(dt);
}

NeutralCell::NeutralCell(const float size): Cell(size)
{
	const auto r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	const auto r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
	accelerate(r1 * 5, r2 * 5);
}

void NeutralCell::react_with(BackgroundCell& other)
{
}

void NeutralCell::react_with(FoodCell& other)
{
	if (death_marked || other.death_marked) return;
	
	const auto dist = get_cells_distance(*this, other);

	if (dist > 0.01) return;
	
	if (other.death_marked) return;
	size += sqrt(other.size);
	other.death_marked = true;
}

void NeutralCell::react_with(PlayerCell& other)
{
	other.react_with(*this);
}

void NeutralCell::react(Cell& cell)
{
	cell.react_with(*this);
}

NeutralCell::~NeutralCell()
= default;

void NeutralCell::react_with(NeutralCell& other)
{
	const auto dist = get_cells_distance(*this, other);

	if (dist > 0.01) return;
	
	if (death_marked || other.death_marked) return;
	if (other.size > size)
	{
		death_marked = true;
		other.size += sqrt(size);
	}
	else
	{
		other.death_marked = true;
		size += sqrt(other.size);
	}
}
