#pragma once
#include "body.h"

class Worm : public Body
{
public:
	void Draw() override;
	Worm(TexHelper * texHelper, Position startPosition);
	void Attack(Orientation orientation);
	bool IsAttack();
	bool ConfirmDrawProp() override;

private:
	void UpdatePosition();
	void UpdateAnimation();
	void UpdateOrientation();

	Orientation _orientation;
	HandTimer _chargeTimer;
	HandTimer _orientationTimer;

	float DEFAULT_SPEED = 0.001f;
	int DEFAULT_HEALTH = 100;
	bool _isAttack;
};