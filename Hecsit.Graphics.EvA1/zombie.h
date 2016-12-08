#pragma once
#include "body.h"

class Zombie : public Body
{
public:

	Zombie(TexHelper * texHelper, Position startPosition);
	void Draw() override;
	void Go(Position);
private:

	void UpdatePosition();
	void UpdateAnimation();
	void UpdateOrientation();
	void UpdateHeadPosition();

	TexProperty _headTexProp;
	DrawProperty _headDrawProp;
	Orientation _orientation;
	Position _finishPosition;
	HandTimer _headTimer;

	int DEFAULT_HEALTH = 100;
	float DEFAULT_SPEED = 0.002f;
};