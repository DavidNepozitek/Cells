#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateStack.h"

class Game
{
	void					process_input();
	void					update(sf::Time dt);
	void					render();
	void					register_states();

	sf::RenderWindow		window_;
	StateStack				state_stack_;
	FontHolder				font_holder_;
public:
	Game();
	void run();
};
