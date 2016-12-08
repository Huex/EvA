#include "room.h"
#include <OpenGL/glew.h>

Room::Room(TexHelper* texDrawer)
{
	_texHelper = texDrawer;
	
	_drawProp.Init(0, -0.5, 0.07 * 12.5, 0.13 * 10.5);
	_texProp.Init(0, 1, 1, 1);
	//_drawProp.Size.Width*_texture.Height / _texture.Width
}

void Room::Draw()
{
	_texHelper->Draw(_texProp, _drawProp, &_texHelper->depths);
	_texHelper->Draw(_texProp, _drawProp, &_texHelper->shading);
}

Room::~Room()
{
}
