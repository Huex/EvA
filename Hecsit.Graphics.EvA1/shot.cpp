#include "shot.h"
#include <math.h>

Shot::Shot(TexHelper *texDrawer, Orientation orientation, Position startPosition) : Body(texDrawer)
{
	_orientation = orientation;
	
	_travelRange = 0;
	_dropTravelRange = 0;

	_drawProp.Init(startPosition.X, startPosition.Y, 0.1, 0.1);
	_texProp.Init(0, 1, 1, 1.0 / 5);
	_poofTexProp.Init(0, 1, 1, 1.0 / 7);
	_speed = DEFAULT_SPEED;
	_range = DEFAULT_RANGE;
}

void Shot::Draw()
{
	if(!_isDestructing)
	{
		UpdatePosition();
		_texHelper->Draw(_texProp, _drawProp, &_texHelper->stone_shot);
	}
	else
	{
		_texHelper->Draw(_poofTexProp, _drawProp, &_texHelper->effect_poof);
		UpdatePoofAnimation();
	}
}

void Shot::UpdatePosition()
{
	float step = _speed;
	if(_travelRange > _range)
	{
		_dropTravelRange += 0.05;
		if (_orientation.OX != 0 && _orientation.OY != 0)
		{
			step *= sqrt(2) / 2;
		}
		if (_orientation.OX > 0)
		{
			_drawProp.Start.Y -= step/6;
			_drawProp.Start.X += step*0.75;
		}
		if (_orientation.OX < 0)
		{
			_drawProp.Start.Y -= step /6;
			_drawProp.Start.X -= step*0.75;
		}
		if (_orientation.OY > 0)
		{
			_drawProp.Start.Y += step/2;
		}
		if (_orientation.OY < 0)
		{
			_drawProp.Start.Y -= step/2;
		}
		if(_dropTravelRange > DEFAULT_DROP_RANGE)
		{
			Destruct();
			_travelRange = 0;
		}
	}
	else
	{
		if (_orientation.OX != 0 && _orientation.OY != 0)
		{
			step *= sqrt(2) / 2;
		}
		if (_orientation.OX > 0)
		{
			_drawProp.Start.X += step;
			_travelRange += step;
		}
		if (_orientation.OX < 0)
		{
			_drawProp.Start.X -= step;
			_travelRange += step;
		}
		if (_orientation.OY > 0)
		{
			_drawProp.Start.Y += step;
			_travelRange += step;
		}
		if (_orientation.OY < 0)
		{
			_drawProp.Start.Y -= step;
			_travelRange += step;
		}
	}
}

void Shot::UpdatePoofAnimation()
{
	extern float TIME_PER_FRAME;
	_animationTimer.Inc(TIME_PER_FRAME);
	if(_animationTimer.Time > 40)
	{
		_poofTexProp.Start.S += 1.0 / 7;
		_animationTimer.Init();
	}
	
	if (_poofTexProp.Start.S > 6.0 / 7)
	{
		_poofTexProp.Start.S = 6.0 / 7;
		_isDestruct = true;
	}
}

bool Shot::ConfirmDrawProp()
{
	bool res = false;
	if (_drawProp.Start.X < -0.13 * 4.2)
	{
		_drawProp.Start.X = -0.13 * 4.2;
		res = true;
	}
	if (_drawProp.Start.X > 0.13 * 4.2)
	{
		_drawProp.Start.X = 0.13 * 4.2;
		res = true;
	}
	if (_drawProp.Start.Y < -0.07 * 6.5)
	{
		_drawProp.Start.Y = -0.07 * 6.5;
		res = true;
	}
	if (_drawProp.Start.Y > 0.07 * 2.8)
	{
		_drawProp.Start.Y = 0.07 * 2.8;
		res = true;
	}
	return res;
}

float Shot::GetRange()
{
	return _range;
}

void Shot::SetRange(float range)
{
	_range = range;
}