#include "Game.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameEndState.h"


Game::Game(sf::ContextSettings& settings, GameSettings& game_settings, GameProgress& progress):
window_(sf::VideoMode(900, 600), "The Hungry Cell", sf::Style::Default, settings),
state_stack_(State::Context(window_, font_holder_, game_settings, progress))
{
	window_.setKeyRepeatEnabled(false);
	window_.setView(window_.getDefaultView());
	
	register_states();

	font_holder_.load(Fonts::Arial, "Fonts/arial.ttf");

	// Initialize the State Stack with MenuState
	state_stack_.push_state(States::Menu);
}

void Game::run()
{
	sf::Clock clock;
	
	while (window_.isOpen())
	{
		const auto dt = clock.restart();

		process_input();
		if (!is_paused_)
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
		// Pause the game when focus is lost
		if (event.type == sf::Event::GainedFocus)
			is_paused_ = false;
		else if (event.type == sf::Event::LostFocus)
			is_paused_ = true;
		state_stack_.handle_event(event);

		if (event.type == sf::Event::Closed)
			window_.close();

		if (event.type == sf::Event::Resized)
		{
			// Scale the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			window_.setView(sf::View(visibleArea));
		}
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

	window_.display();
}


void Game::register_states()
{
	state_stack_.register_state<MenuState>(States::Menu);
	state_stack_.register_state<GameState>(States::Game);
	state_stack_.register_state<PauseState>(States::Pause);
	state_stack_.register_state<GameEndState>(States::End);
}