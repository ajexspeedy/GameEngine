#pragma once
class Game
{
public:
	virtual ~Game() = default;
	
	virtual void LoadGame() = 0;
	virtual void CleanUp() = 0;
};

