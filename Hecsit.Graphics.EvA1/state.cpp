#include "stdafx.h"
#include "state.h"


GameState::GameState()
{
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
	_events.goDown = false;
	_events.goUp = false;
	_events.goLeft = false;
	_events.goRight = false;
}

GameState::State GameState::GetStatus()
{
	return _status;
}

GameState::ActivatedEvents * GameState::GetEvents()
{
	return &_events;
}