#pragma once
#include "drawable.h"
#include "texture.h"
#include "state.h"

class UI : public Drawable
{
public:
	enum Choice
	{
		NewGame,
		End
	};
	UI(TexHelper * texHelper, GameState::State status);
	void Draw() override;
	void SetStatus(GameState::State status);
	void SetCursor(Choice choice);
	Choice GetChoice();
	void DrawScore(int score);
	void IncScore(int score);
	void InitScore();
private:
	TexHelper * _texHelper;
	TexProperty _menuTexProp;
	DrawProperty _menuDrawProp;

	DrawProperty _mainMenuDrawProp;
	DrawProperty _fonDrawProp;
	DrawProperty _cursorDrawProp;
	TexProperty _texProp;

	GameState::State _gameState;
	Choice _choice;
	int _currentNumber;
	int _score;
};