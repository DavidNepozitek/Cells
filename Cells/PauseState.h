#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class Time;
	class Event;
}

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	void		draw() override;
	bool		update(sf::Time dt) override;

	~PauseState() override;
	bool handle_event(const sf::Event& event) override;
private:
	sf::RectangleShape			background_;
	sf::Text			continue_text_;
};
