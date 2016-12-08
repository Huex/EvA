#pragma once
#include "drawable.h"
#include "structures.h"
#include "texture.h"

class Poof
{
public:
	enum Type
	{
		Blood,
		Start,
		Dead,
	};
	void Draw(DrawProperty drawProp);
	bool IsEnd();
	void Restart(Type type);
	void Init(TexHelper * texHelper, Type type);
private:
	HandTimer _animationTimer;
	TexHelper * _texHelper;
	TexProperty _texProp;
	Type _current;	
	bool _end;
	void UpdateAnimation();
};