#pragma once
#include "Cell.h"

class PlayerCell : public Cell
{
	
public:
	explicit PlayerCell(float size);
	void			draw_current(sf::RenderTarget& target, sf::RenderStates states) const override;
	void			update_current(sf::Time dt) override;
	void react_with(BackgroundCell& other) override;
	void react_with(FoodCell& other) override;
	void react_with(PlayerCell& other) override;
	void react(Cell& cell) override;
	~PlayerCell() override;
	void react_with(NeutralCell& other) override;
	sf::Vector2f last_move;
	float		 lost_size{};
};
