#pragma once
#include "keyboard.h"
#include "state.h"
#include "texture.h"
#include "drawer.h"
#include "chiken.h"

class Game
{
public:
	Game();
	~Game();
	void Frame();
	GameState * GetGameState();
	KeyboardHandler * GetKeyboardHandler();
private:
	KeyboardHandler * _keyboardHandler;
	GameState * _gameState;
	Drawer * _drawer;
	TextureHelper * _textureHelper;
	Chiken * _chiken;
	void InitModules(GameState::State state);
};

