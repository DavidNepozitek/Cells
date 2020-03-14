#include "Cell.h"

void Cell::move_with_resistance(sf::Time dt)
{
	auto v = get_velocity();
	auto v2 = v;
	v2.x *= abs(v2.x);
	v2.y *= abs(v2.y);
	auto resistance = (-v) * 0.0002f - v2 * 0.00009f;
	set_velocity(v + resistance);
	move(get_velocity() * dt.asSeconds());
}
