#include "GameEndState.h"
#include "Utility.h"
#include <SFML/Graphics/RenderWindow.hpp>

GameEndState::GameEndState(StateStack& stack, const Context& context)
	: State(stack, context)
{
	continue_text_.setFont(context.font_holder->get(Fonts::Arial));
	continue_text_.setCharacterSize(16);
	center_origin(continue_text_);
	continue_text_.setPosition(context.window->getView().getSize() / 2.f);

	background_ = sf::RectangleShape(context.window->getView().getSize());
	background_.setFillColor(sf::Color(0, 15, 30));
	title_text_.setFont(context.font_holder->get(Fonts::Arial));
}


GameEndState::~GameEndState()
= default;

void GameEndState::draw()
{
	auto& window = *get_context().window;

	
	center_origin(title_text_);
	title_text_.setPosition((window.getView().getSize() / 2.f) + sf::Vector2f(0, -60));

	const auto progress = get_context().progress;
	if (progress->has_won)
	{
		title_text_.setString("Congratulations! You have passed this level!");
		continue_text_.setString("Press [Enter] to continue to the level " + std::to_string(get_context().progress->level + 1));
	}
	else
	{
		const auto main_text = "Ouch :/ Level " + std::to_string(get_context().progress->level) + " was too hard for you!";
		title_text_.setString(main_text);
		continue_text_.setString("Press [Enter] and try it again");
	}

	
	auto view = window.getView();
	view.setCenter(view.getSize() / 2.f);
	window.setView(view);

	background_.setSize(window.getView().getSize());
	center_origin(continue_text_);
	continue_text_.setPosition(window.getView().getSize() / 2.f);


	window.draw(background_);
	window.draw(continue_text_);
	window.draw(title_text_);
}

bool GameEndState::update(sf::Time dt)
{
	return false;
}

bool GameEndState::handle_event(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
	{
		auto progress = get_context().progress;
		if (progress->has_won)
		{
			progress->level += 1;
			
		}
		
		progress->has_won = false;
		request_stack_pop();
		request_stack_pop();
		request_stack_push(States::Game);
	}
	return false;
}
