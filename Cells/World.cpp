#include "World.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "BackgroundCell.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "FoodCell.h"
#include <iostream>
#include "Utility.h"
#include "NeutralCell.h"

World::World(sf::RenderWindow& window, GameProgress& game_progress, GameSettings& settings)
	: game_progress(game_progress)
	, game_settings(settings)
	, window_(window)
	, world_view_(window.getDefaultView())
	, world_bounds_(0.f, 0.f, 1500.f, 1500.f)
	, player_cell_(60)
{
	build_scene();
	player_cell_.setPosition(world_bounds_.width / 2, world_bounds_.height / 2);
	auto view = window_.getView();
	
	window_.setView(view);
}

void World::update(const sf::Time dt)
{
	handle_collisions();

	auto max_size = 0.f;

	// Update all cells in the world
	for (auto& cell : cells_)
	{
		if (cell->size > max_size)
			max_size = cell->size;
		
		cell->update(dt);
	}
	
	// Apply movements
	scene_graph_.update(dt);
	player_cell_.update(dt);

	// Create a food cell when the player moves
	if (player_cell_.lost_size > 3)
	{
		player_cell_.size -= sqrt(player_cell_.lost_size);
		std::unique_ptr<FoodCell> cell(new FoodCell(player_cell_.lost_size));
		cell->set_velocity(-player_cell_.last_move * 20.f);
		const auto pos = player_cell_.getPosition() + ((-player_cell_.last_move / length(player_cell_.last_move)) * (player_cell_.size + cell->size + 0.5f));
		
		cell->setPosition(pos);
		player_cell_.lost_size = 0;

		cells_.push_back(std::move(cell));
		player_cell_.last_move = sf::Vector2f();
	}

	// Erase small cells
	cells_.erase(std::remove_if(cells_.begin(), cells_.end(), [](const std::unique_ptr<Cell>& cell) {return cell->death_marked && cell->size < 0.01; }),
	             cells_.end());

	// Game lost when player size is small
	if (player_cell_.size < 1)
	{
		has_ended = true;
		game_progress.has_won = false;
	}

	// Game win when player is the biggest
	if (player_cell_.size > max_size)
	{
		has_ended = true;
		game_progress.has_won = true;
	}
}

void World::draw() const
{
	// Draw bounds
	sf::RectangleShape bounds(sf::Vector2f(world_bounds_.width, world_bounds_.height));
	bounds.setOutlineThickness(3.f);
	bounds.setOutlineColor(sf::Color(20, 50, 100, 150));
	bounds.setFillColor(sf::Color(0, 0, 0, 0));
	window_.draw(bounds);
	
	window_.draw(scene_graph_);
	
	for(auto& cell : cells_)
	{
		window_.draw(*cell);
	}

	window_.draw(player_cell_);
}

bool World::handle_event(const sf::Event& event)
{
	return false;
}


void World::build_scene()
{
	srand(game_progress.level + 1);

	// Create background cells
	for (auto i = 0; i < 200; ++i)
	{
		const auto x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.width));
		const auto y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.height));
		const auto size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5));

		std::unique_ptr<BackgroundCell> cell(new BackgroundCell(size));
		cell->setPosition(x,y);

		scene_graph_.attach_child(std::move(cell));
	}

	// Create food cells
	for (auto i = 0; i < 200 / (game_progress.level); ++i)
	{
		const auto x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.width));
		const auto y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.height));
		const auto size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 8)) + 1;

		std::unique_ptr<FoodCell> cell(new FoodCell(size));
		cell->setPosition(x, y);

		cells_.push_back(std::move(cell));
	}

	// Create smaller normal cells
	for (auto i = 0; i < 35; ++i)
	{
		const auto x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.width));
		const auto y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.height));
		const auto size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 35)) + game_progress.level * 2;

		if (abs(x - world_bounds_.width / 2) < size || abs(y - world_bounds_.height / 2) < size) continue;

		std::unique_ptr<NeutralCell> cell(new NeutralCell(size));
		cell->setPosition(x, y);

		cells_.push_back(std::move(cell));
	}

	// Create bigger normal cells
	for (auto i = 0; i < 10; ++i)
	{
		const auto x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.width));
		const auto y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.height));
		const auto size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 20)) + 50 + game_progress.level * 2;

		if (abs(x - world_bounds_.width / 2) < size + 60 || abs(y - world_bounds_.height / 2) < size + 60) continue;

		std::unique_ptr<NeutralCell> cell(new NeutralCell(size));
		cell->setPosition(x, y);

		cells_.push_back(std::move(cell));
	}
}



void World::handle_collisions()
{
	handle_bounds(player_cell_);
	handle_reactions(player_cell_);
	
	for (auto& cell : cells_)
	{
		handle_bounds(*cell);
		handle_reactions(*cell);
	}
}


void World::handle_reactions(Cell& cell) const
{
	for (auto& other : cells_)
	{
		if (&*other == &cell) continue;

		cell.react(*other);
	}
}


void World::handle_bounds(Cell& cell) const
{
	// Handle bouncing of the walls
	auto pos = cell.getPosition();
	auto velocity = cell.get_velocity();
	if (pos.x < cell.size)
	{
		velocity.x = -velocity.x;
		pos.x = cell.size + 0.001f;
	}
	else if (pos.y < cell.size)
	{
		velocity.y = -velocity.y;
		pos.y = cell.size + 0.001f;
	}
	else if (pos.x > world_bounds_.width - cell.size)
	{
		velocity.x = -velocity.x;
		pos.x = world_bounds_.width - cell.size - 0.001f;
	}
	else if (pos.y > world_bounds_.height - cell.size)
	{
		velocity.y = -velocity.y;
		pos.y = world_bounds_.height - cell.size - 0.001f;
	}
	cell.setPosition(pos);
	cell.set_velocity(velocity);
}

