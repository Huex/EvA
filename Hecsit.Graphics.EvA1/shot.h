#pragma once
#include "body.h"

class Shot : public Body
{
public:

	Shot(TexHelper * texHelper, Orientation orientation, Position startPosition);
	void Draw() override;
	bool ConfirmDrawProp() override;
	float GetRange();
	void SetRange(float);

private:

	void UpdatePosition();
	void UpdatePoofAnimation();

	Orientation _orientation;
	TexProperty _poofTexProp;

	float _speed;
	float _range;
	float _travelRange;
	float _dropTravelRange;

	float DEFAULT_RANGE = 0.15f;
	float DEFAULT_SPEED = 0.0099f;
	float DEFAULT_DROP_RANGE = 0.9f;
};