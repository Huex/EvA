#pragma once
class Drawable
{
public:
	virtual void Draw() = 0;
};

struct Color
{
	int R;
	int G;
	int B;
};

struct Position
{
	float X;
	float Y;
	float Z;
};

struct Coord
{
	float s;
	float t;
};
