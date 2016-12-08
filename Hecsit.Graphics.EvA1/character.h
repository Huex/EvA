#pragma once
#include "texture.h"
#include "body.h"

class Character : public Body
{
private:
	DrawProperty _headDrawProp;
    TexProperty _headTexProp;

	Orientation _move;
	Orientation _look;

	float _speed;
	const float DEFAULT_SPEED = 0.005;

	void UpdateAnimation();
	void UpdateHead();
	void UpdatePosition();
	void Drawing();	

public:
	void SetHead(Orientation orientation);
	void SetMove(Orientation orientation);
	Orientation GetLook();
	void Draw() override;
	Character(TexHelper * texHelper);
	~Character();
};