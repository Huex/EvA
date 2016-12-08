#pragma once
#include "drawable.h"
#include "texture.h"

class Room :
	public Drawable
{
private:
	TexHelper * _texHelper;
	DrawProperty _drawProp;
	TexProperty _texProp;
public:
	void Draw() override;
	Room(TexHelper * texHelper);
	~Room();
};

