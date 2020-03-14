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
	center_origin(continue_text);
	continue_text.setPosition(context.window->getView().getSize() / 2.f);


	welcome_text.setFont(context.font_holder->get(Fonts::Arial));
	welcome_text.setString("Welcome to The Hungry Cell");
	center_origin(welcome_text);
	welcome_text.setPosition((context.window->getView().getSize() / 2.f) + sf::Vector2f(0, -60));


	background = sf::RectangleShape(context.window->getView().getSize());
	background.setFillColor(sf::Color(0, 15, 30));
	
	//mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
}

void MenuState::draw()
{
	sf::RenderWindow& window = *get_context().window;

	center_origin(continue_text);
	continue_text.setPosition(window.getView().getSize() / 2.f);

	center_origin(welcome_text);
	welcome_text.setPosition((window.getView().getSize() / 2.f) + sf::Vector2f(0, -60));

	background.setSize(window.getView().getSize());
	
	window.draw(background);
	window.draw(welcome_text);
	window.draw(continue_text);

	//if (mShowText)
	//	window.draw(mText);
}

bool MenuState::update(sf::Time dt)
{
	//mTextEffectTime += dt;

	//if (mTextEffectTime >= sf::seconds(0.5f))
	//{
	//	mShowText = !mShowText;
	//	mTextEffectTime = sf::Time::Zero;
	//}

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