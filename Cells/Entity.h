#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include "SceneNode.h"


class Entity : public SceneNode
{
public:
	void				set_velocity(sf::Vector2f velocity);
	void				set_velocity(float vx, float vy);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float vx, float vy);
	sf::Vector2f		get_velocity() const;


private:
	void		update_current(sf::Time dt) override;


private:
	sf::Vector2f		velocity_;
};
