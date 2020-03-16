#include "MenuState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include "StateStack.h"
#include <SFML/Graphics/Text.hpp>
#include "Utility.h"
#include <SFML/Graphics/RectangleShape.hpp>


MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
{

	continue_text.setFont(context.font_holder->get(Fonts::Arial));
	continue_text.setString("Press [Enter] to start the game");
	continue_text.setCharacterSize(16);


	controls_text.setFont(context.font_holder->get(Fonts::Arial));
	controls_text.setString("Consume smaller cells and become the biggest one!\n\nUse arrows or WASD to control the cell\n\nPress [P] to pause the game\n\nPress [R] to restart the game");
	controls_text.setCharacterSize(16);
	controls_text.setFillColor(sf::Color(255, 255, 255, 150));
	
	welcome_text.setFont(context.font_holder->get(Fonts::Arial));
	welcome_text.setString("Welcome to The Hungry Cell");

	background = sf::RectangleShape(context.window->getView().getSize());
	background.setFillColor(sf::Color(0, 15, 30));
}

void MenuState::draw()
{
	auto& window = *get_context().window;

	center_origin(continue_text);
	continue_text.setPosition(window.getView().getSize() / 2.f);

	center_origin(welcome_text);
	welcome_text.setPosition((window.getView().getSize() / 2.f) + sf::Vector2f(0, -60));

	center_origin(controls_text);
	auto pos = window.getView().getSize() / 2.f;
	pos.y += 120;
	controls_text.setPosition(pos);

	background.setSize(window.getView().getSize());
	
	window.draw(background);
		window.draw(welcome_text);

		window.draw(controls_text);

	window.draw(continue_text);
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handle_event(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
	{
		request_stack_pop();
		request_stack_push(States::Game);
	}

	return true;
}