#include "stdafx.h"
#include "game.h"

Game::~Game()
{
}


GameState * Game::GetGameState()
{
	return _gameState;
}

KeyboardHandler * Game::GetKeyboardHandler()
{
	return _keyboardHandler;
}

Game::Game()
{
	InitModules(GameState::Menu);
}

void Game::InitModules(GameState::State state)
{
	_gameState = new GameState();
	_keyboardHandler = new KeyboardHandler(_gameState);
	_drawer = new Drawer();
	_textureHelper = new TextureHelper();
	_chiken = new Chiken(_textureHelper);

	switch (state)
	{
	case(GameState::Menu):
		_gameState->SetStatus(GameState::Menu);
		break;
	case(GameState::Game):
		_gameState->SetStatus(GameState::Game);
		break;
	case(GameState::Pause):
		_gameState->SetStatus(GameState::Pause);
		break;
	}

}

void Game::Frame()
{
	if(_gameState->GetEvents()->goDown)
	{
		if (_chiken->dy > -1)_chiken->dy -= 1;
	}
	if (_gameState->GetEvents()->goLeft)
	{
		if (_chiken->dx > -1)_chiken->dx -= 1;
	}
	if (_gameState->GetEvents()->goUp)
	{
		if (_chiken->dy < 1)_chiken->dy += 1;
	}
	
	if (_gameState->GetEvents()->goRight)
	{
		if (_chiken->dx < 1)_chiken->dx += 1;
	}
	_drawer->Add(_chiken);
	_drawer->Run();
}
