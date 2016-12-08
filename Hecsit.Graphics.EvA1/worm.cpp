#include "worm.h"
#include <math.h>
#include <random>
#include <ctime>

void Worm::Draw()
{
	UpdateHealth();
	UpdateOrientation();
	if (!_isDestructing)
	{
		UpdatePosition();
		ConfirmDrawProp();
		if (_orientation.OX < 0)
		{
			_texHelper->DrawReflectX(_texProp, _drawProp, &_texHelper->monster_worm);
		}
		else
		{
			_texHelper->Draw(_texProp, _drawProp, &_texHelper->monster_worm);
		}
		UpdateAnimation();
		if (_wasAttacked)
		{
			_poof.Draw(_drawProp);
			if (_poof.IsEnd())
			{
				_wasAttacked = false;
			}
		}
	}
	else
	{
		_poof.Draw(_drawProp);
	}
}

bool Worm::ConfirmDrawProp()
{
	bool res = false;
	if (_drawProp.Start.X < -0.13 * 3.8)
	{
		_drawProp.Start.X = -0.13 * 3.8;
		_orientation.OX = 1;
		res = true;
	}
	if (_drawProp.Start.X > 0.13 * 3.8)
	{
		_drawProp.Start.X = 0.13 * 3.8;
		_orientation.OX = -1;
		res = true;
	}
	if (_drawProp.Start.Y < -0.07 * 5.2)
	{
		_drawProp.Start.Y = -0.07 * 5.2;
		_orientation.OY = 1;
		res = true;
	}
	if (_drawProp.Start.Y > 0.07 * 2.3)
	{
		_drawProp.Start.Y = 0.07 * 2.3;
		_orientation.OY = -1;
		res = true;
	}
	if(res == true)
	{
		_isAttack = false;
	}
	return res;
}

Worm::Worm(TexHelper * texHelper, Position startPosition) : Body(texHelper)
{
	_isAttack = false;
	_health = DEFAULT_HEALTH;
	_speed = DEFAULT_SPEED;
	_orientation.Init();
	_chargeTimer.Init();
	_orientationTimer.Init();
	_drawProp.Init(startPosition.X, startPosition.Y, 0.1, 0.1);
	_texProp.Init(0, 1.0 / 3, 1.0 / 3, 1.0 / 6);
}

void Worm::UpdatePosition()
{
		float step = _speed;
		if(_isAttack)
		{
			step = _speed*10;
		}
		if (_orientation.OX != 0 && _orientation.OY != 0)
		{
			step *= sqrt(2) / 2;
		}
		if (_orientation.OX > 0)
		{
			_drawProp.Start.X += step;
		}
		if (_orientation.OX < 0)
		{
			_drawProp.Start.X -= step;
		}
		if (_orientation.OY > 0)
		{
			_drawProp.Start.Y += step;
		}
		if (_orientation.OY < 0)
		{
			_drawProp.Start.Y -= step;
		}
}

void Worm::UpdateAnimation()
{
	extern float TIME_PER_FRAME;
	_animationTimer.Inc(TIME_PER_FRAME);
	_chargeTimer.Inc(TIME_PER_FRAME);
	if (_orientation.OY != 0 || _orientation.OX != 0)
	{
		if (_orientation.OY > 0)
		{
			_texProp.Start.T = 2.0 / 3;
		}
		if (_orientation.OY < 0)
		{
			_texProp.Start.T = 1;
		}
		if (_orientation.OX != 0)
		{
			_texProp.Start.T = 1.0 / 3;
		}
		if (_animationTimer.Time > 80)
		{
			_texProp.Start.S += 1.0 / 6;
			_animationTimer.Init();
		}
		if (_texProp.Start.S > 5.0 / 6)
		{
			_texProp.Start.S = 0;
		}
	}
}

void Worm::UpdateOrientation()
{
	if (!_isAttack) {
		extern float TIME_PER_FRAME;
		_orientationTimer.Inc(TIME_PER_FRAME);
		srand(time(0));
		if (_orientation.OX != 0 || _orientation.OY != 0)
		{
			if (_orientationTimer.Time > (rand() % 6 + 1) * 500)
			{
				if (rand() % 2)
				{
					_orientation.OX = -2 * (rand() % 2) + 1;
					_orientation.OY = 0;
				}
				else
				{
					_orientation.OY = -2 * (rand() % 2) + 1;
					_orientation.OX = 0;
				}

				_orientationTimer.Init();
			}
		}else
		{
			if (rand() % 2)
			{
				_orientation.OX = -2 * (rand() % 2) + 1;
				_orientation.OY = 0;
			}
			else
			{
				_orientation.OY = -2 * (rand() % 2) + 1;
				_orientation.OX = 0;
			}
		}
	}
}

bool Worm::IsAttack()
{
	return _isAttack;
}

void Worm::Attack(Orientation orientation)
{
	if (_chargeTimer.Time > 2000)
	{
		_orientation = orientation;
		_isAttack = true;
		_chargeTimer.Init();
	}
}