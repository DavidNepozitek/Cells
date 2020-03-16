#include "Entity.h"

void Entity::set_velocity(const sf::Vector2f velocity)
{
	velocity_ = velocity;
}

void Entity::set_velocity(const float vx, const float vy)
{
	velocity_.x = vx;
	velocity_.y = vy;
}

sf::Vector2f Entity::get_velocity() const
{
	return velocity_;
}

void Entity::accelerate(const sf::Vector2f velocity)
{
	velocity_ += velocity;
}

void Entity::accelerate(const float vx, const float vy)
{
	velocity_.x += vx;
	velocity_.y += vy;
}

void Entity::update_current(const sf::Time dt)
{
	move(velocity_ * dt.asSeconds());
}