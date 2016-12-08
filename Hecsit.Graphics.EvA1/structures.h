#pragma once

struct Orientation
{
	void Init(float ox, float oy)
	{
		OX = ox;
		OY = oy;
	}
	void Init()
	{
		Init(0, 0);
	}
	Orientation(float ox, float oy)
	{
		Init(ox, oy);
	}
	Orientation()
	{
		Init();
	}
	float OX;
	float OY;
};

struct Position
{
	void Init(float x, float y)
	{
		X = x;
		Y = y;
	}
	void Init()
	{
		Init(0, 0);
	}
	Position(float x, float y)
	{
		Init(x, y);
	}
	Position()
	{
		Init();
	}
	float X;
	float Y;
};

struct Coord
{
	void Init(float s, float t)
	{
		S = s;
		T = t;
	}
	void Init()
	{
		Init(0, 0);
	}
	Coord()
	{
		Init();
	}
	Coord(float s, float t)
	{
		Init(s, t);
	}
	float S;
	float T;
};

struct Size
{
	void Init(float h, float w)
	{
		Height = h;
		Width = w;
	}
	void Init()
	{
		Init(0, 0);
	}
	Size()
	{
		Init();
	}
	Size(float h, float w)
	{
		Init(h, w);
	}
	float Width;
	float Height;
};

struct TexProperty
{
	void Init(float s, float t, float hight, float width)
	{
		Start.Init(s, t);
		Size.Init(hight, width);
	}
	void Init()
	{
		Start.Init();
		Size.Init();
	}
	TexProperty()
	{
		Init();
	}
	TexProperty(float s, float t, float hight, float width)
	{
		Init(s, t, hight, width);
	}
	Coord Start;
	Size Size;
};

struct DrawProperty
{
	void Init(float x, float y, float hight, float width)
	{
		Start.Init(x, y);
		Size.Init(hight, width);
	}
	void Init()
	{
		Init(0, 0, 0, 0);
	}
	DrawProperty()
	{
		Init();
	}
	DrawProperty(float x, float y, float hight, float width)
	{
		Init(x, y, hight, width);
	}
	Position Start;
	Size Size;
};

struct HandTimer
{
	HandTimer operator=(const HandTimer& timer)
	{
		HandTimer res;
		res.Init(timer.Time);
		return res;
	}
	const int MAX_TIME = 99999998;
	HandTimer()
	{
		Init();
	}
	void Init(float time)
	{
		Time = time;
	}
	void Init()
	{
		Init(0);
	}
	void Inc(float time)
	{
		Time += time;
		if (Time > MAX_TIME)
		{
			Time = MAX_TIME;
		}
	}
	float Time;
};

struct TexImage
{
	void Init()
	{
		ImageData = nullptr;
		BPP = 0;
		Width = 0;
		Height = 0;
		ID = 0;
		Type = 0;
		Format = 0;
	}
	TexImage()
	{
		Init();
	}
	unsigned char *ImageData;
	unsigned int  BPP;
	unsigned int Width, Height;
	unsigned int ID;
	unsigned int Type;
	unsigned int Format;
};