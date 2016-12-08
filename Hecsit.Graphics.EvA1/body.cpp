#include "body.h"

Position Body::GetPos()
{
	return _drawProp.Start;
}

Size Body::GetSize()
{
	return _drawProp.Size;
}

bool Body::IsDestruct()
{
	return _isDestruct;
}

bool Body::IsDestructing()
{
	return _isDestructing;
}

void Body::Destruct()
{
	_isDestructing = true;
}

bool Body::ConfirmDrawProp()
{
	bool res = false;
	if (_drawProp.Start.X < -0.13 * 3.8)
	{
		_drawProp.Start.X = -0.13 * 3.8;
		res = true;
	}
	if (_drawProp.Start.X > 0.13 * 3.8)
	{
		_drawProp.Start.X = 0.13 * 3.8;
		res = true;
	}
	if (_drawProp.Start.Y < -0.07 * 5.2)
	{
		_drawProp.Start.Y = -0.07 * 5.2;
		res = true;
	}
	if (_drawProp.Start.Y > 0.07 * 2.3)
	{
		_drawProp.Start.Y = 0.07 * 2.3;
		res = true;
	}
	return res;
}

Body::Body(TexHelper * texHelper)
{
	_texHelper = texHelper;
	_texProp.Init();
	_poof.Init(_texHelper, Poof::Start);
	_drawProp.Init();
	_animationTimer.Init();
	_isDestructing = false;
	_isDestruct = false;
	_health = 100;
	_speed = 0.002;
	_wasAttacked = false;
}

void Body::UpdateHealth()
{
	if (_health <= 0)
	{
		if (!IsDestructing())
		{
			Destruct();
			_poof.Restart(Poof::Dead);
		}
		if (_poof.IsEnd())
		{
			_isDestruct = true;
		}
	}
}

void Body::TakeDamage(int damage)
{
	if (_health > 0)
	{
		_health -= damage;
		_wasAttacked = true;
		_poof.Restart(Poof::Blood);
	}
}

int  Body::GetHealth()
{
	return _health;
}