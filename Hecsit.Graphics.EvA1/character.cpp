#include "character.h"
#include <math.h>

void Character::UpdateAnimation()
{
	extern float TIME_PER_FRAME;

	UpdateHead();

	if (_move.OX != 0)
	{
		_texProp.Start.T = 1;
	}

	if (_move.OY != 0)
	{
		_texProp.Start.T = 2.0 / 3;
	}

	if(_move.OX != 0 || _move.OY != 0)
	{
		_animationTimer.Inc(TIME_PER_FRAME);
	}
	else
	{
		_texProp.Start.S = 0;
		_texProp.Start.T = 2.0 / 3;
	}

	if (_animationTimer.Time > 100)
	{
		_texProp.Start.S += 1.0 / 10;
		_animationTimer.Init();
		if(_texProp.Start.S > 1)
		{
			_texProp.Start.S = 1.0 / 10;
		}
	}
}

void Character::UpdateHead()
{
	_headDrawProp = _drawProp;
	_headDrawProp.Start.Y += _drawProp.Size.Height / 2.6;
	_headDrawProp.Size.Width /= 1.2;
	_headDrawProp.Size.Height /= 1.2;

	if(_look.OX == 0 && _look.OY == 0)
	{
		if(_move.OX != 0 || _move.OY != 0)
		{
			_look = _move;
		}
		else
		{
			_look.OY = -1;
		}
	}

	if (_look.OX != 0)
	{
		_headTexProp.Start.S = 2.0 / 10;
	}
	if (_look.OY > 0)
	{
		_headTexProp.Start.S = 4.0 / 10;
	}
	if (_look.OY < 0)
	{
		_headTexProp.Start.S = 0.0 / 10;
	}
}

void Character::UpdatePosition()
{
	float step = _speed;
	if (_move.OX != 0 && _move.OY != 0)
	{
		step *= sqrt(2) / 2;
	}
	if (_move.OX > 0)
	{
		_drawProp.Start.X += step;
	}
	if (_move.OX < 0)
	{
		_drawProp.Start.X -= step;
	}
	if (_move.OY > 0)
	{
		_drawProp.Start.Y += step;
	}
	if (_move.OY < 0)
	{
		_drawProp.Start.Y -= step;
	}

	ConfirmDrawProp();
	UpdateHead();
}

void Character::Drawing()
{
	if (_move.OX < 0)
	{
		_texHelper->DrawReflectX(_texProp, _drawProp, &_texHelper->character1);
	}
	else
	{
		_texHelper->Draw(_texProp, _drawProp, &_texHelper->character1);
	}

	if (_look.OX < 0)
	{
		_texHelper->DrawReflectX(_headTexProp, _headDrawProp, &_texHelper->character1);
	}
	else
	{
		_texHelper->Draw(_headTexProp, _headDrawProp, &_texHelper->character1);
	}
}

void Character::SetHead(Orientation pos)
{
	_look = pos;
}

void Character::SetMove(Orientation pos)
{
	_move = pos;
}

Orientation Character::GetLook()
{
	return _look;
}

void Character::Draw()
{	
	UpdateHealth();
	UpdateAnimation();
	if(!_isDestructing)
	{
		UpdatePosition();
		Drawing();
		if (_wasAttacked)
		{
			_poof.Draw(_drawProp);
			if (_poof.IsEnd())
			{
				_wasAttacked = false;
			}
		}
	}else
	{
		_poof.Draw(_drawProp);
	}

	_move.Init();
	_look.Init();
}

Character::Character(TexHelper * texProp) : Body(texProp)
{
	_speed = DEFAULT_SPEED;
	_drawProp.Init(0, -0.1, 0.1, 0.1);
	_texProp.Init(0, 2.0 / 3, 1.0 / 3, 1.0 / 10);
	_headTexProp.Init(0, 1.0 / 3, 1.0 / 3, 1.0 / 10);

	_headDrawProp = _drawProp;
	_headDrawProp.Start.Y += _drawProp.Size.Height / 2.6;
	_headDrawProp.Size.Width /= 1.2;
	_headDrawProp.Size.Height /= 1.2;

	_move.Init();
	_look.Init();
}

Character::~Character()
{
}