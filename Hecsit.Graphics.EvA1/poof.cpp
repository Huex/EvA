#include "poof.h"
#include <random>
#include <ctime>

void Poof::UpdateAnimation()
{
	extern float TIME_PER_FRAME;

	_animationTimer.Inc(TIME_PER_FRAME);
	if (_animationTimer.Time > 40)
	{
		_texProp.Start.S += 1.0 / 4;
		_animationTimer.Init();
	}
	if (_texProp.Start.S > 3.0 / 4)
	{
		_texProp.Start.T += 1.0 / 4;
		_texProp.Start.S = 0;
	}
	if (_texProp.Start.T > 1)
	{
		_texProp.Start.T = 1.0 / 4;
		_texProp.Start.S = 0;
		_animationTimer.Init();
		_end = true;
	}
}

void Poof::Draw(DrawProperty drawProp)
{
	
	if (!IsEnd())
	{
		srand(time(0));
		int r = rand() % 3;
		switch(_current)
		{
		case(Blood):
			switch (r)
			{
			case(0):
				_texHelper->Draw(_texProp, drawProp, &_texHelper->effect_blood_poof);
				break;
			case(1):
				_texHelper->Draw(_texProp, drawProp, &_texHelper->effect_blood_poof2);
				break;
			case(2):
				_texHelper->Draw(_texProp, drawProp, &_texHelper->effect_blood_poof3);
				break;
			}
			break;
		case(Dead):
			_texHelper->Draw(_texProp, drawProp, &_texHelper->effect_dead_poof);
			break;
		case(Start):
			_texHelper->Draw(_texProp, drawProp, &_texHelper->effect_start_poof);
			break;
		}

		UpdateAnimation();
	}
}

bool Poof::IsEnd()
{
	return _end;
}

void Poof::Restart(Type type)
{
	_current = type;
	_animationTimer.Init();
	_texProp.Init(0, 1.0 / 4, 1.0 / 4, 1.0 / 4);
	_end = false;
}

void Poof::Init(TexHelper * texHelper, Type type)
{
	_texHelper = texHelper;
	Restart(type);
}
