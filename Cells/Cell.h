#pragma once
#include "Entity.h"

class NeutralCell;
class PlayerCell;
class FoodCell;
class BackgroundCell;

class Cell: public Entity
{
public:
	explicit Cell(float size);
	float size;
	bool death_marked{};

	virtual void react_with(BackgroundCell& other) = 0;
	virtual void react_with(FoodCell& other) = 0;
	virtual void react_with(PlayerCell& other) = 0;
	virtual void react_with(NeutralCell& other) = 0;

	virtual void react(Cell& cell) = 0;
	void move_with_resistance(sf::Time dt);
};
