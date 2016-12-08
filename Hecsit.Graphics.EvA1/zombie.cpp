#include "zombie.h"
#include <math.h>
#include <iostream>

Zombie::Zombie(TexHelper * texHelper, Position startPosition) : Body(texHelper)
{
	_speed = DEFAULT_SPEED;
	_health = DEFAULT_HEALTH;
	_headTimer.Init();
	_drawProp.Init(startPosition.X, startPosition.Y, 0.1, 0.1);
	_texProp.Init(0, 1.0 / 3, 1.0 / 3, 1.0 / 10);
	UpdateHeadPosition();
	_headDrawProp.Size.Height = _drawProp.Size.Height * 0.8;
	_headDrawProp.Size.Width = _drawProp.Size.Width* 0.8;
	_headTexProp.Init(0, 1, 1.0 / 3, 1.0 / 10);
	_finishPosition.Init();
}

void Zombie::Draw()
{
	UpdateHealth();
	UpdateOrientation();
	if(!_isDestructing)
	{
		UpdatePosition();
		UpdateAnimation();
		if (_orientation.OX < 0)
		{
			_texHelper->DrawReflectX(_texProp, _drawProp, &_texHelper->monster_zombie);
		}
		else
		{
			_texHelper->Draw(_texProp, _drawProp, &_texHelper->monster_zombie);
		}
		_texHelper->Draw(_headTexProp, _headDrawProp, &_texHelper->monster_zombie);
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

void Zombie::Go(Position position)
{
	_finishPosition = position;
}

void Zombie::UpdatePosition()
{
	float step = _speed;
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
	UpdateHeadPosition();
}

void Zombie::UpdateAnimation()
{
	extern float TIME_PER_FRAME;
	_headTimer.Inc(TIME_PER_FRAME);
	if (_orientation.OX != 0)
	{
		_texProp.Start.T = 2.0 / 3;
	}
	if (_orientation.OY != 0)
	{
		_texProp.Start.T = 1.0 / 3;
	}
	if(_orientation.OX != 0 || _orientation.OY != 0)
	{
		_animationTimer.Inc(TIME_PER_FRAME);
	}
	else
	{
		_texProp.Start.S = 0;
		_texProp.Start.T = 1.0 / 3;
	}
	if (_animationTimer.Time > 100)
	{
		_texProp.Start.S += 1.0 / 10;
		_animationTimer.Init();
		if (_texProp.Start.S > 1)
		{
			_texProp.Start.S = 1.0 / 10;
		}
	}
	if(_headTimer.Time > 450)
	{
		_headTexProp.Start.S += 1.0 / 10;
		if (_headTexProp.Start.S > 3.0 / 10)
		{
			_headTexProp.Start.S = 0;
		}
		_headTimer.Init();
	}
}

void Zombie::UpdateOrientation()
{
	if(_drawProp.Start.X - _finishPosition.X < -0.025)
	{
		_orientation.OX = 1;
	}
	if (_drawProp.Start.X - _finishPosition.X > 0.025)
	{
		_orientation.OX = -1;
	}
	if (_drawProp.Start.X - _finishPosition.X > -0.025 && _drawProp.Start.X - _finishPosition.X < 0.025)
	{
		_orientation.OX = 0;
	}
	if (_drawProp.Start.Y - _finishPosition.Y < -0.025)
	{
		_orientation.OY = 1;
	}
	if (_drawProp.Start.Y - _finishPosition.Y > 0.025)
	{
		_orientation.OY = -1;
	}
	if (_drawProp.Start.Y - _finishPosition.Y > -0.025 && _drawProp.Start.Y - _finishPosition.Y < 0.025)
	{
		_orientation.OY = 0;
	}
}

void Zombie::UpdateHeadPosition()
{
	_headDrawProp.Start.X = _drawProp.Start.X;
	_headDrawProp.Start.Y = _drawProp.Start.Y + 0.035;
}
