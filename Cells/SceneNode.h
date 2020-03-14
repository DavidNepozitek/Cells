#pragma once
#include <vector>
#include <memory>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>


namespace sf {
	class RenderStates;
	class RenderTarget;
	class Time;
}

class SceneNode : public sf::Transformable, public sf::Drawable, sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	SceneNode();
	void					attach_child(Ptr child);
	Ptr						detach_child(const SceneNode& node);

	void					update(sf::Time dt);

	sf::Vector2f			get_world_position() const;
	sf::Transform			get_world_transform() const;
private:
	std::vector<Ptr> children_;
	SceneNode* parent_;

	virtual void			update_current(sf::Time dt);
	void					update_children(sf::Time dt);

	void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void			draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
	void					draw_children(sf::RenderTarget& target, sf::RenderStates states) const;
};
