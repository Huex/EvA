#include "state.h"


GameState::GameState(State state)
{
	SetStatus(state);
	InitEvents();
}


GameState::~GameState()
{
}

void GameState::SetStatus(State state)
{
	_status = state;
}

void GameState::InitEvents()
{
	_wasd.OX = 0;
	_wasd.OY = 0;

	_arrows.OX = 0;
	_arrows.OY = 0;

	_space = false;
}

GameState::State GameState::GetStatus()
{
	return _status;
}