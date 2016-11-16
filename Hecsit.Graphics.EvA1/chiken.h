#pragma once
class Chiken : public Drawable
{
private:
	enum Orientation
	{
		Left,
		Right,
		Up,
		Down
	}orientation;
	float timerX, timerY;
	TextureHelper::TextureImage texture;
	void Update();
	Coord coord, scale;
	TextureHelper * _textureHelper;
public:
	Chiken(TextureHelper *);
	float x, y, dx, dy;
	~Chiken();
	void Draw();
};

