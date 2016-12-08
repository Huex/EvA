#pragma once
#include "keyboard.h"
#include "state.h"
#include "texture.h"
#include "drawer.h"
#include "room.h"
#include "character.h"
#include "shot.h"
#include "worm.h"
#include "ui.h"
#include "zombie.h"

class Game
{
public:
	Game();
	~Game();
	void Frame();
	GameState * GetGameState();
	Keyboard * GetKeyboardHandler();
private:
	struct Level
	{
		std::vector<Zombie> Zombies;
		std::vector<Worm> Worms;
		bool isEnd;
	};
	std::queue<Level> _levels;
	std::vector<Body *> _bodies;
	std::vector<Shot> _shots;

	Level _currentLevel;
	HandTimer _shotTimer;
	HandTimer _butTimer;

	Keyboard * _keyboardHandler;
	GameState * _gameState;
	Drawer * _drawer;
	TexHelper * _texHelper;
	UI * _ui;
	Room * _room;
	Character * _character;



	void UpdateCharacter();
	void InitLevels();
	void ProcessMenu();
	void ProcessGame();
	bool UpdateLevel();
	void UpdateBodies();
	void SortBodies();
	void DrawGame();
	void UpdateShots();
	void UpdateWormsAttack();
	void UpdateZombieAttack();
	void UpdateHitsBodies();
	void UpdateCharacterDamage();
	void ProcessPause();

	template <typename Monster>
	void UpdateHitsTo(float radius);

	void DeleteDeadMonsters();
	void InitModules(GameState::State state);
	//void UpdateShot();
	//void UpdateWorm();
	//void UpdateHitWorm();
};

