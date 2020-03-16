#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include "SceneNode.h"
#include "PlayerCell.h"
#include "GameProgress.h"
#include "GameSettings.h"

namespace sf {
	class Event;
	class RenderWindow;
	class Time;
}

/**
 * \brief Represents the game world (its state, entities etc.)
 */
class World: sf::NonCopyable
{
public:
	explicit							World(sf::RenderWindow& window, GameProgress& game_progress, GameSettings& settings);
	void								update(sf::Time dt);
	void								draw() const;
	static bool								handle_event(const sf::Event& event);
	bool								has_ended{};
	GameProgress&						game_progress;
	GameSettings&						game_settings;
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