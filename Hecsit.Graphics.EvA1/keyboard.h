#pragma once
#include "state.h"

class KeyboardHandler
{
private:
	GameState * _gameState;
public:
	KeyboardHandler(GameState *);
	void SpecialUp(int, int, int);
	void SpecialDown(int, int, int);
	void Up(unsigned char, int, int);
	void Down(unsigned char, int, int);
	~KeyboardHandler();
};

