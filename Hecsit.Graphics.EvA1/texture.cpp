#include <IL/il.h>
#include <IL/ilu.h>
#include <OpenGL/glew.h>
#include "structures.h"
#include "texture.h"

TexHelper::TexHelper()
{
	ilInit();
	iluInit();
	_countTextures = 0;
	Load("textures/character1.png", &character1);
	Load("textures/depths.png", &depths);
	Load("textures/shading.png", &shading);
	Load("textures/stone_shot.png", &stone_shot);
	Load("textures/effect_poof.png", &effect_poof);
	Load("textures/in_game_menu.png", &in_game_menu);
	Load("textures/monster_worm.png", &monster_worm);
	Load("textures/effect_dead_poof.png", &effect_dead_poof);
	Load("textures/effect_blood_poof.png", &effect_blood_poof);
	Load("textures/effect_blood_poof2.png", &effect_blood_poof2);
	Load("textures/effect_blood_poof3.png", &effect_blood_poof3);
	Load("textures/monster_zombie.png", &monster_zombie);
	Load("textures/effect_start_poof.png", &effect_start_poof);
	Load("textures/main_menu.png", &main_menu);
	Load("textures/cursor.png", &cursor);
	Load("textures/splashes.png", &splashes);
	Load("textures/shadow.png",&shadow);
	Load("textures/numerial.png", &numerial);
	Load("textures/win.png", &win);
}

TexHelper::~TexHelper()
{
}

void TexHelper::Activate(TexImage * texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->Width, texture->Height, 0, texture->Format, texture->Type, texture->ImageData);
}

void TexHelper::Load(char * fileName, TexImage *texture)
{
	_countTextures++;
	ilBindImage(_countTextures);
	ilLoad(IL_PNG, (ILstring)fileName);
	int error = ilGetError();
	texture->Width = ilGetInteger(IL_IMAGE_WIDTH);
	texture->Height = ilGetInteger(IL_IMAGE_HEIGHT);
	texture->BPP = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	texture->Format = ilGetInteger(IL_IMAGE_FORMAT);
	texture->ImageData = ilGetData();
	ilEnable(IL_CONV_PAL);
	texture->Type = ilGetInteger(IL_IMAGE_TYPE);
	glGenTextures(1, &texture->ID);
}

void TexHelper::Free(TexImage *texture)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture->ID);
	ilDeleteImages(1, &texture->ID);                                 
}

void TexHelper::Draw(TexProperty texCoord, DrawProperty drawCoord, TexImage * texture)
{
	Activate(texture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(texCoord.Start.S, texCoord.Start.T);
	glVertex2f(drawCoord.Start.X - drawCoord.Size.Width / 2, drawCoord.Start.Y);
	glTexCoord2f(texCoord.Start.S + texCoord.Size.Width, texCoord.Start.T);
	glVertex2f(drawCoord.Start.X + drawCoord.Size.Width / 2, drawCoord.Start.Y);
	glTexCoord2f(texCoord.Start.S + texCoord.Size.Width, texCoord.Start.T - texCoord.Size.Height);
	glVertex2f(drawCoord.Start.X + drawCoord.Size.Width / 2, (drawCoord.Start.Y + drawCoord.Size.Height));
	glTexCoord2f(texCoord.Start.S, texCoord.Start.T - texCoord.Size.Height);
	glVertex2f(drawCoord.Start.X - drawCoord.Size.Width / 2, (drawCoord.Start.Y + drawCoord.Size.Height));
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void TexHelper::DrawReflectX(TexProperty texCoord, DrawProperty drawCoord, TexImage * texture)
{
	Activate(texture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(texCoord.Start.S + texCoord.Size.Width, texCoord.Start.T);
	glVertex2f(drawCoord.Start.X - drawCoord.Size.Width / 2, drawCoord.Start.Y);
	glTexCoord2f(texCoord.Start.S, texCoord.Start.T);
	glVertex2f(drawCoord.Start.X + drawCoord.Size.Width / 2, drawCoord.Start.Y);
	glTexCoord2f(texCoord.Start.S, texCoord.Start.T - texCoord.Size.Height);
	glVertex2f(drawCoord.Start.X + drawCoord.Size.Width / 2, (drawCoord.Start.Y + drawCoord.Size.Height));
	glTexCoord2f(texCoord.Start.S + texCoord.Size.Width, texCoord.Start.T - texCoord.Size.Height);
	glVertex2f(drawCoord.Start.X - drawCoord.Size.Width / 2, (drawCoord.Start.Y + drawCoord.Size.Height));
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
