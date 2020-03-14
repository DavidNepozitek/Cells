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

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::RectangleShape			background_;
	sf::Text			text_;
	sf::Text			instructions_;
};
