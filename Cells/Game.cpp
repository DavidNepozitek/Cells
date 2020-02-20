#include "Game.h"
#include "MenuState.h"


Game::Game()
	: window_(sf::VideoMode(640, 480), "The Hungry Cell", sf::Style::Close)
	, state_stack_(State::Context(window_, font_holder_))
{
	window_.setKeyRepeatEnabled(false);

	register_states();

	font_holder_.load(Fonts::Arial, "Fonts/arial.ttf");
	
	state_stack_.push_state(States::Menu);
}

void Game::run()
{
	sf::Clock clock;
	
	while (window_.isOpen())
	{
		const auto dt = clock.restart();

		process_input();
		update(dt);

		// Check inside this loop, because stack might be empty before update() call
		if (state_stack_.is_empty())
			window_.close();
		
		render();
	}
}

void Game::process_input()
{
	sf::Event event{};
	while (window_.pollEvent(event))
	{
		state_stack_.handle_event(event);

		if (event.type == sf::Event::Closed)
			window_.close();
	}
}

void Game::update(const sf::Time dt)
{
	state_stack_.update(dt);
}

void Game::render()
{
	window_.clear();

	state_stack_.draw();

	window_.setView(window_.getDefaultView());
	
	//mWindow.draw(mStatisticsText);

	window_.display();
}


void Game::register_states()
{
	state_stack_.register_state<MenuState>(States::Menu);
}