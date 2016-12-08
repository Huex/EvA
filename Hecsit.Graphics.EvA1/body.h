#pragma once
#include "drawable.h"
#include "texture.h"
#include "structures.h"
#include "poof.h"

class Body : public Drawable
{
protected:
	TexHelper * _texHelper;
	TexProperty _texProp;
	Poof _poof;
	
	HandTimer _animationTimer;

	bool _isDestruct;
	bool _isDestructing;

	int _health;

	float _speed;
	bool _wasAttacked;

	DrawProperty _drawProp;

	void UpdateHealth();

public: 

	int GetHealth();
	void TakeDamage(int countDamage);
	Position GetPos();
	Size GetSize();
	bool IsDestruct();
	bool IsDestructing();
	void Destruct();
	virtual bool ConfirmDrawProp();
	virtual void Draw() {};
	Body(TexHelper * texHelper);
};