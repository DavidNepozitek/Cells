#include "Entity.h"

void Entity::set_velocity(sf::Vector2f velocity)
{
	velocity_ = velocity;
}

void Entity::set_velocity(float vx, float vy)
{
	velocity_.x = vx;
	velocity_.y = vy;
}

sf::Vector2f Entity::get_velocity() const
{
	return velocity_;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	velocity_ += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	velocity_.x += vx;
	velocity_.y += vy;
}

void Entity::update_current(sf::Time dt)
{
	move(velocity_ * dt.asSeconds());
}