#pragma once
#include "State.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	void		draw() override;
	bool		update(sf::Time dt) override;
	bool		handle_event(const sf::Event& event) override;
	sf::Text	welcome_text;
	sf::Text	continue_text;
	sf::RectangleShape background;

private:

};
