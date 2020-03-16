#pragma once

class GameProgress
{
public:
	GameProgress(const bool has_won, const int level)
		: has_won(has_won),
		  level(level)
	{
	}

	bool has_won;
	int level;
};
