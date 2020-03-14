#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include "SceneNode.h"
#include "PlayerCell.h"

namespace sf {
	class Event;
	class RenderWindow;
	class Time;
}

class World: sf::NonCopyable
{
public:
	explicit							World(sf::RenderWindow& window);
	void								update(sf::Time dt);
	void								draw() const;
	bool								handle_event(const sf::Event& event);
private:
	sf::RenderWindow&					window_;
	sf::View							world_view_;
	SceneNode							scene_graph_;
	sf::FloatRect						world_bounds_;
	std::vector<std::unique_ptr<Cell>>	cells_;

	void								build_scene();
	PlayerCell							player_cell_;
	void								handle_collisions();
	void								handle_bounds(Cell& cell) const;
	void								handle_reactions(Cell& cell) const;
}; 