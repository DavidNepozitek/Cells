#include "PlayerCell.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Utility.h"
#include "FoodCell.h"
#include "NeutralCell.h"
#include <SFML/Graphics/RectangleShape.hpp>

PlayerCell::PlayerCell(const float size): Cell(size)
{
	set_velocity(static_cast<float>(1.0), static_cast<float>(1.0));
}

void PlayerCell::draw_current(sf::RenderTarget& target, const sf::RenderStates states) const
{
	auto current_view = target.getView();
	
	current_view.setCenter(getPosition());
	target.setView(current_view);
	sf::CircleShape shape(size);
	shape.move(-size, -size);
	shape.setFillColor(sf::Color(100, 150, 250));

	target.draw(shape, states);

	//sf::RectangleShape line(sf::Vector2f(150.f, 5.f));
	//line.rotate(45.f);
	//target.draw(line, states);
}

void PlayerCell::update_current(const sf::Time dt)
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
	
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.y -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.y += 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += 5;

	accelerate(movement * dt.asSeconds() * 80.f);


	const auto ab = sqrt(movement.x * movement.x + movement.y * movement.y) * dt.asSeconds() * 3;

	last_move += movement * dt.asSeconds();
	lost_size += ab;

	move_with_resistance(dt);
}

void PlayerCell::react_with(BackgroundCell& other)
{
}

void PlayerCell::react_with(FoodCell& other)
{
	const auto dist = get_cells_distance(*this, other);

	if (dist > 0.01) return;
	
	if (other.death_marked) return;
	size += sqrt(other.size);
	other.death_marked = true;
}

void PlayerCell::react_with(PlayerCell& other)
{
	// Nope
}

void PlayerCell::react(Cell& cell)
{
	cell.react_with(*this);
}

PlayerCell::~PlayerCell()
= default;

void PlayerCell::react_with(NeutralCell& other)
{
	const auto dist = get_cells_distance(*this, other);

	if (other.size > size)
	{
		other.is_bigger = true;
	} else
	{
		other.is_bigger = false;
	}
	
	if (dist > 0.01) return;
	
	if (death_marked || other.death_marked) return;
	if (other.size > size)
	{
		other.size += sqrt(size);
		death_marked = true;
		
	} else
	{
		size += sqrt(other.size);
		other.death_marked = true;
	}
}
