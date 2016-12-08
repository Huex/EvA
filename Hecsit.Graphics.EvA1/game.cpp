#include "game.h"
#include <iostream>
#include <functional>
#include <ctime>

Game::~Game()
{
}

GameState * Game::GetGameState()
{
	return _gameState;
}

Keyboard * Game::GetKeyboardHandler()
{
	return _keyboardHandler;
}

void Game::InitLevels()
{
	std::queue<Level> levels;
	_levels = levels;
	Level level1;
	level1.Zombies.push_back(Zombie(_texHelper, Position(-0.49, -0.36)));
	level1.Zombies.push_back(Zombie(_texHelper, Position(0.49, 0.16)));
	level1.isEnd = false;
	Level level2;
	level2.Zombies.push_back(Zombie(_texHelper, Position(-0.49, -0.36)));
	level2.Zombies.push_back(Zombie(_texHelper, Position(0.49, 0.16)));
	level2.Zombies.push_back(Zombie(_texHelper, Position(-0.49, 0.16)));
	level2.Zombies.push_back(Zombie(_texHelper, Position(0.49, -0.36)));
	level2.isEnd = false;
	Level level3;
	level3.Worms.push_back(Worm(_texHelper, Position(0.49, 0.16)));
	level3.isEnd = false;

	Level level4;
	level4.Zombies.push_back(Zombie(_texHelper, Position(0.49, 0.16)));
	level4.Worms.push_back(Worm(_texHelper, Position(-0.49, -0.36)));
	level4.isEnd = false;

	Level level5;
	level5.Zombies.push_back(Zombie(_texHelper, Position(0.49, -0.36)));
	level5.Zombies.push_back(Zombie(_texHelper, Position(-0.49, -0.36)));
	level5.Worms.push_back(Worm(_texHelper, Position(0.49, 0.16)));
	level5.isEnd = false;

	Level level6;
	level6.Worms.push_back(Worm(_texHelper, Position(0.49, -0.36)));
	level6.Worms.push_back(Worm(_texHelper, Position(-0.49, -0.36)));
	level6.isEnd = false;

	Level level7;
	level7.Zombies.push_back(Zombie(_texHelper, Position(-0.49, -0.36)));
	level7.isEnd = false;

	Level level8;
	level8.Zombies.push_back(Zombie(_texHelper, Position(-0.49, -0.36)));
	level8.Worms.push_back(Worm(_texHelper, Position(0.49, 0.16)));
	level8.Worms.push_back(Worm(_texHelper, Position(0.49, 0.16)));
	level8.isEnd = false;

	Level level9;
	level9.Zombies.push_back(Zombie(_texHelper, Position(0.49, -0.36)));
	level9.Zombies.push_back(Zombie(_texHelper, Position(-0.49, -0.36)));
	level9.Zombies.push_back(Zombie(_texHelper, Position(-0.49, 0.16)));
	level9.Worms.push_back(Worm(_texHelper, Position(0.49, 0.16)));
	level9.isEnd = false;

	Level level10;
	level10.Worms.push_back(Worm(_texHelper, Position(-0.49, 0.16)));
	level10.Worms.push_back(Worm(_texHelper, Position(0.49, 0.16)));
	level10.Worms.push_back(Worm(_texHelper, Position(-0.49, -0.36)));
	level10.Worms.push_back(Worm(_texHelper, Position(0.49, -0.36)));
	level10.isEnd = false;

	Level level11;
	level11.Worms.push_back(Worm(_texHelper, Position(-0.49, 0.16)));
	level11.Worms.push_back(Worm(_texHelper, Position(0.49, 0.16)));
	level11.Worms.push_back(Worm(_texHelper, Position(-0.49, -0.36)));
	level11.Worms.push_back(Worm(_texHelper, Position(0.49, -0.36)));
	level11.Zombies.push_back(Zombie(_texHelper, Position(-0.49, 0.16)));
	level11.Zombies.push_back(Zombie(_texHelper, Position(0.49, 0.16)));
	level11.Zombies.push_back(Zombie(_texHelper, Position(-0.49, -0.36)));
	level11.Zombies.push_back(Zombie(_texHelper, Position(0.49, -0.36)));
	level11.isEnd = false;

	_levels.push(level1);
	_levels.push(level2);
	_levels.push(level3);
	_levels.push(level4);
	_levels.push(level5);
	_levels.push(level6);
	_levels.push(level7);
	_levels.push(level8);
	_levels.push(level9);
	_levels.push(level10);
	_currentLevel.isEnd = true;
}

void Game::ProcessMenu()
{
	if (_gameState->_arrows.OY > 0)
	{
		_ui->SetCursor(UI::NewGame);
	}
	if (_gameState->_arrows.OY < 0)
	{
		_ui->SetCursor(UI::End);
	}
	_drawer->Add(_ui);
	if (_gameState->_space && _butTimer.Time > 500)
	{
		if (_ui->GetChoice() == UI::End)
		{
			exit(0);
		}
		if (_ui->GetChoice() == UI::NewGame)
		{
			_gameState->SetStatus(GameState::Game);
			InitLevels();
			_ui->InitScore();
		}
	}
}

void Game::ProcessGame()
{
	if(UpdateLevel())
	{
		UpdateBodies();
	}
	DeleteDeadMonsters();
	UpdateCharacter();
	UpdateShots();
	UpdateWormsAttack();
	UpdateZombieAttack();
	UpdateHitsBodies();
	UpdateCharacterDamage();

	SortBodies();



	DrawGame();
}

bool Game::UpdateLevel()
{
	bool res = _currentLevel.isEnd && !_levels.empty();
	if (_currentLevel.isEnd)
	{
		if (!_levels.empty())
		{
			_currentLevel = _levels.front();
			_levels.pop();
			_currentLevel.isEnd = false;
			_bodies.clear();
		}
		else
		{
			_gameState->SetStatus(GameState::Pause);
		}
	}
	return res;
}

void Game::UpdateBodies()
{
	for (int i = 0; i < _currentLevel.Zombies.size(); i++)
	{
		_bodies.push_back(&_currentLevel.Zombies[i]);
	}
	for (int i = 0; i < _currentLevel.Worms.size(); i++)
	{
		_bodies.push_back(&_currentLevel.Worms[i]);
	}
	_bodies.push_back(_character);
}

void Game::SortBodies()
{
	Body * tmp;

	for (int i = 0; i < _bodies.size() - 1; ++i) // i - номер прохода
	{
		for (int j = 0; j < _bodies.size() - 1; ++j) // внутренний цикл прохода
		{
			if (_bodies[j + 1]->GetPos().Y > _bodies[j]->GetPos().Y)
			{
				tmp = _bodies[j + 1];
				_bodies[j + 1] = _bodies[j];
				_bodies[j] = tmp;
			}
		}
	}
}

void Game::DrawGame()
{
	_drawer->Add(_room);
	_drawer->Add(_ui);

	for(int i = 0; i < _bodies.size(); i++)
	{
		_drawer->Add(_bodies[i]);
	}
	for (int i = 0; i < _shots.size(); i++)
	{
		_drawer->Add(&_shots[i]);
	}
}

Game::Game()
{
	InitModules(GameState::Menu);
}

void Game::InitModules(GameState::State state)
{
	_gameState = new GameState(state);
	_keyboardHandler = new Keyboard(_gameState);
	_drawer = new Drawer();
	_texHelper = new TexHelper();
	_ui = new UI(_texHelper,_gameState->GetStatus());
	_room = new Room(_texHelper);
	_character = new Character(_texHelper);
}

void Game::UpdateCharacter()
{
	_character->SetHead(_gameState->_arrows);
	_character->SetMove(_gameState->_wasd);
}

void Game::UpdateShots()
{
	extern float TIME_PER_FRAME;
	_shotTimer.Inc(TIME_PER_FRAME);
	if ((_gameState->_arrows.OX != 0 || _gameState->_arrows.OY != 0)&& !_character->IsDestruct())
	{
		if (_shotTimer.Time > 600)
		{
			_shots.emplace_back(Shot(
				_texHelper,
				_gameState->_arrows,
				Position(_character->GetPos().X, _character->GetPos().Y)
			));
			//if (_gameState->_wasd.OX + _gameState->_arrows.OX != 0 || _gameState->_wasd.OY + _gameState->_arrows.OY != 0)
			//{
			//	_shots.back().SetRange(_shots.back().GetRange() * 0.005 * 600) ;
			//}
			_shotTimer.Init();
		}
	}
	for (int i = 0; i < _shots.size(); i++)
	{
		if (_shots[i].ConfirmDrawProp())
		{
			_shots[i].Destruct();
		}
		if (_shots[i].IsDestruct())
		{
			_shots.erase(_shots.begin() + i );
		}
	}
}

void Game::UpdateWormsAttack()
{
	for (int i = 0; i < _bodies.size(); i++)
	{
		if (typeid(*_bodies[i]) == typeid(Worm))
		{
			Worm * worm = (Worm *)_bodies[i];
			float pos = 0;
			if (abs(worm->GetPos().X - _character->GetPos().X) < 0.03)
			{
				if ((worm->GetPos().Y - _character->GetPos().Y) > 0)
				{
					pos = -1;
				}
				if ((worm->GetPos().Y - _character->GetPos().Y) < 0)
				{
					pos = 1;
				}
				if ((worm->GetPos().Y - _character->GetPos().Y) == 0)
				{
					pos = 0;
				}
				worm->Attack(Orientation(0, pos));
			}
			if (abs(worm->GetPos().Y - _character->GetPos().Y) < 0.03)
			{
				if ((worm->GetPos().X - _character->GetPos().X) > 0)
				{
					pos = -1;
				}
				if ((worm->GetPos().X - _character->GetPos().X) < 0)
				{
					pos = 1;
				}
				if ((worm->GetPos().X - _character->GetPos().X) == 0)
				{
					pos = 0;
				}
				worm->Attack(Orientation(pos, 0));
			}
		}
	}
}

void Game::UpdateZombieAttack()
{
	for (int i = 0; i < _bodies.size(); i++)
	{
		if (typeid(*_bodies[i]) == typeid(Zombie))
		{
			Zombie * zombie = (Zombie*)_bodies[i];
			zombie->Go(_character->GetPos());			
		}
	}
}

void Game::UpdateHitsBodies()
{
	UpdateHitsTo<Worm>(0.05);
	UpdateHitsTo<Zombie>(0.07);
	if(_character->IsDestruct())
	{
		_gameState->SetStatus(GameState::Pause);
		_character = new Character(_texHelper);
	}
}

void Game::UpdateCharacterDamage()
{
	for (int i = 0; i < _bodies.size(); i++)
	{
		if (typeid(*_bodies[i]) != typeid(Character))
		{
			Body * monster = _bodies[i];
			if (sqrt(pow(_character->GetPos().X - monster->GetPos().X, 2) + pow((_character->GetPos().Y + _character->GetSize().Height / 2) - (monster->GetPos().Y + monster->GetSize().Height / 2), 2)) < 0.05)
			{
				if (!_character->IsDestructing() && !monster->IsDestructing())
				{
					_character->TakeDamage(20);
				}
			}
		}
	}
}

void Game::ProcessPause()
{
	_drawer->Add(_ui);
	if (_gameState->_space)
	{
		_gameState->SetStatus(GameState::Menu);
		_butTimer.Init();
	}
}

template <typename Monster>
void Game::UpdateHitsTo(float radius)
{
	for (int i = 0; i < _bodies.size(); i++)
	{
		for (int j = 0; j < _shots.size(); j++)
		{
			if (typeid(*_bodies[i]) == typeid(Monster))
			{
				Monster * worm = (Monster *)_bodies[i];
				if (sqrt(pow(_shots[j].GetPos().X - worm->GetPos().X, 2) + pow((_shots[j].GetPos().Y + _shots[j].GetSize().Height / 2) - (worm->GetPos().Y + worm->GetSize().Height / 2), 2)) < radius)
				{
					if (!_shots[j].IsDestructing() && !worm->IsDestructing())
					{
						worm->TakeDamage(20);
						_shots[j].Destruct();
					}
				}
			}
		}
	}
}

void Game::DeleteDeadMonsters()
{
	for (int i = 0; i< _bodies.size(); i++)
	{
		if (_bodies[i]->IsDestruct())
		{			
			if (typeid(*_bodies[i]) == typeid(Worm))
			{
				_ui->IncScore(750);
			}
			if (typeid(*_bodies[i]) == typeid(Zombie))
			{
				_ui->IncScore(225);
			}
			_bodies.erase(_bodies.begin() + i);
			
		}
	}
	if(_bodies.size() == 1)
	{
		_currentLevel.isEnd = true;
	}
}




void Game::Frame()
{
	extern float TIME_PER_FRAME;
	_butTimer.Inc(TIME_PER_FRAME);
	_ui->SetStatus(_gameState->GetStatus());
	switch (_gameState->GetStatus())
	{
	case(GameState::Menu):
		ProcessMenu();
		break;
	case(GameState::Game):
		ProcessGame();
		break;
	case(GameState::Pause):
		ProcessPause();
		break;
	}

	_drawer->Run();
}