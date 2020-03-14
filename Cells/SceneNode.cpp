#include "SceneNode.h"
#include <cassert>
#include <SFML/System/Time.hpp>

SceneNode::SceneNode()
{
	parent_ = nullptr;
}

void SceneNode::attach_child(Ptr child)
{
	child->parent_ = this;
	children_.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detach_child(const SceneNode& node)
{
	const auto found = std::find_if(children_.begin(), children_.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != children_.end());

	auto result = std::move(*found);
	result->parent_ = nullptr;
	children_.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	update_current(dt);
	update_children(dt);
}

void SceneNode::update_current(sf::Time)
{
	// Do nothing by default
}

void SceneNode::update_children(sf::Time dt)
{
	for (auto& child : children_)
	{
		child->update(dt);
	}	
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	draw_current(target, states);
	draw_children(target, states);
}

void SceneNode::draw_current(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::draw_children(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& child : children_)
	{
		child->draw(target, states);
	}	
}

sf::Vector2f SceneNode::get_world_position() const
{
	return get_world_transform() * sf::Vector2f();
}

sf::Transform SceneNode::get_world_transform() const
{
	auto transform = sf::Transform::Identity;

	for (auto node = this; node != nullptr; node = node->parent_)
		transform = node->getTransform() * transform;

	return transform;
}
