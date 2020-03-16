#pragma once
#include "Cell.h"

class NeutralCell: public Cell
{
	void draw_current(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update_current(sf::Time dt) override;
public:
	explicit NeutralCell(float size);
	bool is_bigger{};
	void react_with(BackgroundCell& other) override;
	void react_with(FoodCell& other) override;
	void react_with(PlayerCell& other) override;
	void react(Cell& cell) override;
	~NeutralCell() override;
	void react_with(NeutralCell& other) override;
};
