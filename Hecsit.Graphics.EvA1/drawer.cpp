#include "stdafx.h"
#include "drawer.h"


Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}

int Drawer::Size()
{
	return _drawQueue.size();
}

void Drawer::Add(Drawable * drawable)
{
	_drawQueue.push(drawable);
}

void Drawer::Run()
{
	while (!_drawQueue.empty())
	{
		_drawQueue.front()->Draw();
		_drawQueue.pop();
	}
}
