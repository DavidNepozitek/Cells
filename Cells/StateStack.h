#pragma once
#include "State.h"
#include <SFML/System/NonCopyable.hpp>
#include <vector>
#include <map>
#include <functional>
#include "States.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};
public:
	explicit StateStack(State::Context context);
	template <typename T>
	void register_state(States::ID state_id);
	void update(sf::Time dt);
	void draw();
	void handle_event(const sf::Event& event);
	void push_state(States::ID state_id);
	void pop_state();
	void clear_states();
	bool is_empty() const;
private:
	State::ptr create_state(States::ID state_id);
	void apply_pending_changes();
	
	struct PendingChange
	{
		explicit PendingChange(Action action, States::ID stateID = States::None);
		Action action;
		States::ID stateID;
	};
	
	std::vector<State::ptr> stack_;
	std::vector<PendingChange> pending_list_;
	State::Context context_;
	std::map<States::ID, std::function<State::ptr()>> factories_;
};

template <typename T>
void StateStack::register_state(const States::ID state_id)
{
	factories_[state_id] = [this]()
	{
		return State::ptr(new T(*this, context_));
	};
}