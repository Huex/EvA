#pragma once
#include "structures.h"

class GameState
{
public:
	enum State
	{
		Game,
		Menu,
		Pause
	};

	GameState(State);
	~GameState();

	Orientation _wasd, _arrows;

	bool _space;

	State GetStatus();
	void SetStatus(State);
	void InitEvents();
private:
	State _status;
};


