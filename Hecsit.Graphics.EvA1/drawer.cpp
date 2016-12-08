#include "drawer.h"

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
