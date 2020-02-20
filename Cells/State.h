﻿#pragma once
#include "States.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include "ResourceHolder.h"
#include "Fonts.hpp"

namespace sf
{
	class RenderWindow;
}

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, FontHolder& fonts);

		sf::RenderWindow*	window;
		FontHolder* font_holder;
	};


public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handle_event(const sf::Event& event) = 0;


protected:
	void				request_stack_push(States::ID state_id) const;
	void				request_stack_pop() const;
	void				request_state_clear() const;

	Context				get_context() const;


private:
	StateStack*			stack_;
	Context				context_;
};