#pragma once
#include "State.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class GameEndState: public State
{
public:
	GameEndState(StateStack& stack, const Context& context);

	~GameEndState() override;
	void draw() override;
	bool update(sf::Time dt) override;
	bool handle_event(const sf::Event& event) override;
private:
	sf::RectangleShape			background_;
	sf::Text				 continue_text_;
	sf::Text					title_text_;
};
