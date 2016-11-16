#include "stdafx.h"
#include "keyboard.h"

KeyboardHandler::KeyboardHandler(GameState * gameState)
{
	_gameState = gameState;
}

void KeyboardHandler::SpecialUp(int key, int, int)
{
	switch (key)
	{
	case(GLUT_KEY_UP):
		_gameState->GetEvents()->goUp = false;
		break;
	case(GLUT_KEY_DOWN):
		_gameState->GetEvents()->goDown = false;
		break;
	case(GLUT_KEY_LEFT):
		_gameState->GetEvents()->goLeft = false;
		break;
	case(GLUT_KEY_RIGHT):
		_gameState->GetEvents()->goRight = false;
		break;
	}
}

void KeyboardHandler::SpecialDown(int key, int, int)
{
	switch (key)
	{
	case(GLUT_KEY_UP):
		_gameState->GetEvents()->goUp = true;
		break;
	case(GLUT_KEY_DOWN):
		_gameState->GetEvents()->goDown = true;
		break;
	case(GLUT_KEY_LEFT):
		_gameState->GetEvents()->goLeft = true;
		break;
	case(GLUT_KEY_RIGHT):
		_gameState->GetEvents()->goRight = true;
		break;
	}
}

void KeyboardHandler::Up(unsigned char, int, int)
{
}

void KeyboardHandler::Down(unsigned char, int, int)
{
}

KeyboardHandler::~KeyboardHandler()
{
}
