#pragma once
#include <queue>
#include "drawable.h"

class Drawer
{
public:
	Drawer();
	~Drawer();
	int Size();
	void Add(Drawable *);
	void Run();
private:
	std::queue<Drawable *> _drawQueue;
};

