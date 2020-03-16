#include "Cell.h"

Cell::Cell(const float size): size(size)
{
	
}

void Cell::move_with_resistance(const sf::Time dt)
{
	const auto v = get_velocity();
	auto v2 = v;
	v2.x *= abs(v2.x);
	v2.y *= abs(v2.y);
	const auto resistance = (-v) * 0.00009f - v2 * 0.00002f;
	set_velocity(v + resistance);
	move(get_velocity() * dt.asSeconds());
}
