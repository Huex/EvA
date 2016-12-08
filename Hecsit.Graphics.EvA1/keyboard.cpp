#include "keyboard.h"
#include <OpenGL/glut.h>

Keyboard::Keyboard(GameState * gameState)
{
	_gameState = gameState;
}

void Keyboard::SpecialUp(int key, int, int)
{
	switch (key)
	{
	case(GLUT_KEY_UP):
		_gameState->_arrows.OY -= 1;
		break;
	case(GLUT_KEY_DOWN):
		_gameState->_arrows.OY += 1;
		break;
	case(GLUT_KEY_LEFT):
		_gameState->_arrows.OX += 1;
		break;
	case(GLUT_KEY_RIGHT):
		_gameState->_arrows.OX -= 1;
		break;
	}
}

void Keyboard::SpecialDown(int key, int, int)
{
	switch (key)
	{
	case(GLUT_KEY_UP):
		_gameState->_arrows.OY += 1;
		break;
	case(GLUT_KEY_DOWN):
		_gameState->_arrows.OY -= 1;
		break;
	case(GLUT_KEY_LEFT):
		_gameState->_arrows.OX -= 1;
		break;
	case(GLUT_KEY_RIGHT):
		_gameState->_arrows.OX += 1;
		break;
	}
}

void Keyboard::Up(unsigned char key, int, int)
{
	switch (key)
	{
	case('w'):
		_gameState->_wasd.OY -= 1;
		break;
	case('s'):
		_gameState->_wasd.OY += 1;
		break;
	case('a'):
		_gameState->_wasd.OX += 1;
		break;
	case('d'):
		_gameState->_wasd.OX -= 1;
		break;
	case(' '):
		_gameState->_space = false;
		break;
	}
}

void Keyboard::Down(unsigned char key, int, int)
{
	switch (key)
	{
	case('w'):
		_gameState->_wasd.OY += 1;
		break;
	case('s'):
		_gameState->_wasd.OY -= 1;
		break;
	case('a'):
		_gameState->_wasd.OX -= 1;
		break;
	case('d'):
		_gameState->_wasd.OX += 1;
		break;
	case(' '):
		_gameState->_space = true;
		break;
	case('\t'):
		_gameState->_space = true;
		break;
	}
}

Keyboard::~Keyboard()
{
}
