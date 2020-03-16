#pragma once
#include "State.h"
#include "World.h"

class GameState: public State
{
public:
	GameState(StateStack& stack, const Context& context)
		: State(stack, context)
		, world_(*context.window, *context.progress, *context.settings)
	{
	}

	void		draw() override;
	bool		update(sf::Time dt) override;
	bool		handle_event(const sf::Event& event) override;

private:
	World world_;
};
