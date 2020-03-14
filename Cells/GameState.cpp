#include "GameState.h"

bool GameState::update(sf::Time dt)
{
	world_.update(dt);

	return true;
}

bool GameState::handle_event(const sf::Event& event)
{
	// Game input handling

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		request_stack_push(States::Menu);


	
	return true;
}

void GameState::draw()
{
	world_.draw();
}
