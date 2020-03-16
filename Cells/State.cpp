#include "State.h"
#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, FontHolder& fonts, GameSettings& game_settings, GameProgress& progress)
	: window(&window), font_holder(&fonts), settings(&game_settings), progress(&progress)
{

}

State::State(StateStack& stack, const Context context)
	: stack_(&stack)
	, context_(context)
{
}

State::~State() = default;

void State::request_stack_push(const States::ID state_id) const
{
	stack_->push_state(state_id);
}

void State::request_stack_pop() const
{
	stack_->pop_state();
}

void State::request_state_clear() const
{
	stack_->clear_states();
}

State::Context State::get_context() const
{
	return context_;
}