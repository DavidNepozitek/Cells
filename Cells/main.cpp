#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	try
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		GameSettings game_settings{};
		GameProgress game_progress(false, 1);

		
		Game game(settings, game_settings, game_progress);
		game.run();
	} catch (const std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	
	return 0;
}
