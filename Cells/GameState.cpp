#include "GameState.h"

bool GameState::update(const sf::Time dt)
{
	world_.update(dt);

	if (world_.has_ended)
	{
		request_stack_push(States::End);
	}
	
	return true;
}

bool GameState::handle_event(const sf::Event& event)
{
	// Game input handling

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		request_stack_push(States::Pause);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
	{
		request_stack_pop();
		request_stack_push(States::Game);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
	{
		world_.game_progress.has_won = true;
		world_.has_ended = true;
	}
	
	return true;
}

void GameState::draw()
{
	world_.draw();
}
