#pragma once
#include "structures.h"

class TexHelper
{
private:
	int _countTextures;
	void Activate(TexImage *texture);
	void Load(char *filename, TexImage *texture);
public:
	TexImage character1;
	TexImage depths;
	TexImage effect_blood_poof;
	TexImage effect_blood_poof2;
	TexImage effect_blood_poof3;
	TexImage effect_dead_poof;
	TexImage effect_poof;
	TexImage effect_start_poof;
	TexImage in_game_menu;
	TexImage monster_worm;
	TexImage monster_zombie;
	TexImage shading;
	TexImage stone_shot;
	TexImage splashes;
	TexImage cursor;
	TexImage main_menu;
	TexImage shadow;
	TexImage numerial;
	TexImage win;

	TexHelper();
	~TexHelper();
	void Free(TexImage *texture);
	void Draw(TexProperty texCoord, DrawProperty drawCoord, TexImage * texture);
	void DrawReflectX(TexProperty texCoord, DrawProperty drawCoord, TexImage * texture);
};