#include "PlayerCell.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Utility.h"
#include "FoodCell.h"

PlayerCell::PlayerCell()
{
	set_velocity(static_cast<float>(1.0), static_cast<float>(1.0));
	size = 50;
}

void PlayerCell::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto current_view = target.getView();
	
	current_view.setCenter(getPosition());
	target.setView(current_view);
	sf::CircleShape shape(size);
	shape.move(-size, -size);
	shape.setFillColor(sf::Color(100, 150, 250));

	target.draw(shape, states);
}

void PlayerCell::update_current(sf::Time dt)
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += 5;

	accelerate(movement * 0.5f);
	
	

	auto ab = sqrt(movement.x * movement.x + movement.y * movement.y) * dt.asSeconds() * 4;

	last_move += movement * dt.asSeconds();
	lost_size += ab;

	move_with_resistance(dt);
}

void PlayerCell::react_with(BackgroundCell& other)
{
}

void PlayerCell::react_with(FoodCell& other)
{
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
