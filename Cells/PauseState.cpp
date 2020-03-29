#include "PauseState.h"
#include "Utility.h"
#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateStack& stack, Context context): State(stack, context)
{

	continue_text_.setFont(context.font_holder->get(Fonts::Arial));
	continue_text_.setString("Press [P] to continue");
	continue_text_.setCharacterSize(16);
	center_origin(continue_text_);
	continue_text_.setPosition(context.window->getView().getSize() / 2.f);

	background_ = sf::RectangleShape(context.window->getView().getSize());
	background_.setFillColor(sf::Color(0, 15, 30));
}

void PauseState::draw()
{
	auto& window = *get_context().window;

	auto view = window.getView();
	view.setCenter(view.getSize() / 2.f);
	window.setView(view);
	
	background_.setSize(window.getView().getSize());
	center_origin(continue_text_);
	continue_text_.setPosition(window.getView().getSize() / 2.f);

	
	window.draw(background_);
	window.draw(continue_text_);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handle_event(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		request_stack_pop();
	return false;
}
