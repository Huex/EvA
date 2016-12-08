#include "ui.h"
#include "font.h"

UI::UI(TexHelper * texHelper, GameState::State status)
{
	_texHelper = texHelper;
	_menuDrawProp.Init(0, 0.25, 0.65*0.4, 0.65);
	_menuTexProp.Init(0, 1, 1, 1);
	_fonDrawProp.Init(0,-0.5,1,1);
	_mainMenuDrawProp.Init(0, -0.2, 0.5, 0.5);
	_texProp.Init(0, 1, 1, 1);
	_cursorDrawProp.Init(-0.14, 0.04, 0.08, 0.08);
	SetStatus(status);
	_choice = Choice::NewGame;
	_currentNumber = 0;
	_score = 0;
}

void UI::Draw()
{
	switch(_gameState)
	{
	case(GameState::Menu):
		_texHelper->Draw(_texProp, _fonDrawProp, &_texHelper->splashes);
		_texHelper->Draw(_texProp, _mainMenuDrawProp, &_texHelper->main_menu);
		_texHelper->Draw(_texProp, _cursorDrawProp, &_texHelper->cursor);
		break;
	case(GameState::Pause):
		_texHelper->Draw(_texProp, _fonDrawProp, &_texHelper->splashes);
		_texHelper->Draw(TexProperty(0, 1, 1, 1), DrawProperty(0, -0.23, 0.45, 0.45), &_texHelper->win);
		DrawScore(_score);
		break;
	case(GameState::Game):
		_texHelper->Draw(_menuTexProp, _menuDrawProp, &_texHelper->in_game_menu);
		DrawScore(_score);
		break;
	}
}

void UI::SetStatus(GameState::State status)
{
	_gameState = status;
}

void UI::SetCursor(Choice choice)
{
	switch (choice)
	{
	case(End):
		_cursorDrawProp.Init(-0.065, -0.029, 0.08, 0.08);
		_choice = Choice::End;
		break;
	case(NewGame):
		_cursorDrawProp.Init(-0.14, 0.04, 0.08, 0.08);
		_choice = Choice::NewGame;
		break;
	}
}

UI::Choice UI::GetChoice()
{
	return _choice;
}

void UI::DrawScore(int score)
{
	if (score != 0)
	{
		if(_gameState == GameState::Pause)
		{
			float number = score % 10;
			if (number != 0)
			{
				number /= 10;
			}
			_texHelper->Draw(TexProperty(number, 1, 1, 1.0 / 10), DrawProperty(-_currentNumber*0.04 + 0.1, -0.05, 0.1, 0.1), &_texHelper->numerial);
			_currentNumber++;
			DrawScore(score / 10);
		}
		else
		{
			float number = score % 10;
			if (number != 0)
			{
				number /= 10;
			}
			_texHelper->Draw(TexProperty(number, 1, 1, 1.0 / 10), DrawProperty(-_currentNumber*0.04 + 0.1, 0.36, 0.1, 0.1), &_texHelper->numerial);
			_currentNumber++;
			DrawScore(score / 10);
		}	
	}
	else
	{
		_currentNumber = 0;
	}
}

void UI::IncScore(int score)
{
	_score += score;
}

void UI::InitScore()
{
	_score = 0;
}