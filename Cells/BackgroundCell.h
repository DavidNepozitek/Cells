﻿#pragma once
#include "Cell.h"
#include <SFML/Graphics/CircleShape.hpp>

class BackgroundCell: public Cell
{
public:
	BackgroundCell(float size);

private:
	void draw_current(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update_current(sf::Time dt) override;
	sf::CircleShape	shape_;
public:
	void react_with(BackgroundCell& other) override;
	void react_with(FoodCell& other) override;
	void react_with(PlayerCell& other) override;
	void react(Cell& cell) override;
	~BackgroundCell() override;
	void react_with(NeutralCell& other) override;
};
