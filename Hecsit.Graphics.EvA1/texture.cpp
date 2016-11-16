#include "texture.h"
#include "stdafx.h"

TextureHelper::TextureHelper()
{
	ilInit();
	iluInit();
	_countTextures = 0;
}


TextureHelper::~TextureHelper()
{
}


void TextureHelper::Activate(TextureImage * texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->Width, texture->Height, 0, texture->Format, texture->Type, texture->ImageData);
}

// Функция, непосредственно загружающая текстуру в переданную структуру.
// В функцию передается тип файла, имя файла и указатель на текстуру.
void TextureHelper::Load(char * fileName, TextureImage *texture)
{
	_countTextures++;
	ilBindImage(_countTextures);
	ilLoad(IL_PNG, (ILstring)fileName);
	int error = ilGetError();
	if (error)
	{
		glBegin(GL_QUADS);
		glColor3ub(255, 0, 0);
		glVertex3f(-1, -1, -9);
		glVertex3f(1, -1, -9);
		glVertex3f(1, 1, -9);
		glVertex3f(-1, 1, -9);
		glEnd();
	}
	texture->Width = ilGetInteger(IL_IMAGE_WIDTH);
	texture->Height = ilGetInteger(IL_IMAGE_HEIGHT);
	texture->BPP = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	texture->Format = ilGetInteger(IL_IMAGE_FORMAT);
	texture->ImageData = ilGetData();

	ilEnable(IL_CONV_PAL);

	texture->Type = ilGetInteger(IL_IMAGE_TYPE);
	glGenTextures(1, &texture->ID);
}

void TextureHelper::Free(TextureImage *texture)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture->ID);
	ilDeleteImages(1, &texture->ID);                                 
}