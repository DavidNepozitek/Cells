#include "StateStack.h"
#include <cassert>


StateStack::StateStack(const State::Context context)
	: context_(context)
{
}

void StateStack::update(const sf::Time dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	apply_pending_changes();
}

void StateStack::draw()
{
	// Draw all active states from bottom to top
	for(auto& state : stack_)
		state->draw();
}

void StateStack::handle_event(const sf::Event& event)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr)
	{
		if (!(*itr)->handle_event(event))
			break;
	}

	apply_pending_changes();
}

void StateStack::push_state(States::ID state_id)
{
	pending_list_.emplace_back(Push, state_id);
}

void StateStack::pop_state()
{
	pending_list_.emplace_back(Pop);
}

void StateStack::clear_states()
{
	pending_list_.emplace_back(Clear);
}

bool StateStack::is_empty() const
{
	return stack_.empty();
}

State::ptr StateStack::create_state(const States::ID state_id)
{
	const auto found = factories_.find(state_id);
	assert(found != factories_.end());

	return found->second();
}

void StateStack::apply_pending_changes()
{
	for(auto change : pending_list_)
	{
		switch (change.action)
		{
		case Push:
			stack_.push_back(create_state(change.state_id));
			break;

		case Pop:
			stack_.pop_back();
			break;

		case Clear:
			stack_.clear();
			break;
		}
	}

	pending_list_.clear();
}

StateStack::PendingChange::PendingChange(const Action action, const States::ID state_id) : action(action), state_id(state_id)
{
}