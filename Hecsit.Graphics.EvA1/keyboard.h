#pragma once
#include "state.h"

class Keyboard
{
private:
	GameState * _gameState;
public:
	Keyboard(GameState *);
	void SpecialUp(int, int, int);
	void SpecialDown(int, int, int);
	void Up(unsigned char, int, int);
	void Down(unsigned char, int, int);
	~Keyboard();
};

