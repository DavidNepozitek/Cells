#include "World.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "BackgroundCell.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "FoodCell.h"
#include <iostream>
#include "Utility.h"

World::World(sf::RenderWindow& window)
	: window_(window)
	, world_view_(window.getDefaultView())
	, world_bounds_(0.f, 0.f, 1000.f, 1000.f)
{
	build_scene();
	player_cell_.setPosition(500, 500);
	auto view = window_.getView();
	
	window_.setView(view);
}

void World::update(sf::Time dt)
{
	handle_collisions();
	
	for (auto& cell : cells_)
	{
		cell->update(dt);
	}
	
	// Apply movements
	scene_graph_.update(dt);
	player_cell_.update(dt);

	if (player_cell_.lost_size > 3)
	{
		player_cell_.size -= sqrt(player_cell_.lost_size);
		std::cout << player_cell_.lost_size << std::endl;
		std::unique_ptr<FoodCell> cell(new FoodCell);
		cell->size = player_cell_.lost_size;
		cell->set_velocity(-player_cell_.last_move * 70.f);
		const auto pos = player_cell_.getPosition() + ((-player_cell_.last_move / length(player_cell_.last_move)) * (player_cell_.size + cell->size + 0.2f));
		
		cell->setPosition(pos);
		player_cell_.lost_size = 0;

		cells_.push_back(std::move(cell));
		player_cell_.last_move = sf::Vector2f();
	}
	
	cells_.erase(std::remove_if(cells_.begin(), cells_.end(), [](const std::unique_ptr<Cell>& cell) {return cell->death_marked && cell->size < 0.01; }),
	             cells_.end());
}

void World::draw() const
{
	//window_.setView(world_view_);
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
	
	//for (int i = 0; i < 200; ++i)
	//{
	//	auto x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.width));
	//	auto y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.height));
	//	auto size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5));

	//	std::unique_ptr<BackgroundCell> cell(new BackgroundCell);
	//	cell->size = size;
	//	cell->setPosition(x,y);

	//	cells_.push_back(std::move(cell));
	//}

	for (int i = 0; i < 50; ++i)
	{
		auto x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.width));
		auto y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / world_bounds_.height));
		auto size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6)) + 1;

		std::unique_ptr<FoodCell> cell(new FoodCell);
		cell->size = size;
		cell->setPosition(x, y);

		cells_.push_back(std::move(cell));
	}
}

float get_cells_distance(Cell& a, Cell& b)
{
	const auto pos_a = a.get_world_position();
	const auto pos_b = b.get_world_position();
	auto x = pos_a.x - pos_b.x;
	auto y = pos_a.y - pos_b.y;
	return sqrt( x*x + y*y) - a.size - b.size;
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
		
		const auto dist = get_cells_distance(cell, *other);

		if (dist < 0.01)
		{
			cell.react(*other);
		}
	}
}


void World::handle_bounds(Cell& cell) const
{
	auto pos = cell.getPosition();
	auto velocity = cell.get_velocity();
	if (pos.x < cell.size)
	{
		velocity.x = -velocity.x;
		pos.x = cell.size + 0.001;
	}
	else if (pos.y < cell.size)
	{
		velocity.y = -velocity.y;
		pos.y = cell.size + 0.001;
	}
	else if (pos.x > world_bounds_.width - cell.size)
	{
		velocity.x = -velocity.x;
		pos.x = world_bounds_.width - cell.size - 0.001;
	}
	else if (pos.y > world_bounds_.height - cell.size)
	{
		velocity.y = -velocity.y;
		pos.y = world_bounds_.height - cell.size - 0.001;
	}
	cell.setPosition(pos);
	cell.set_velocity(velocity);
}




