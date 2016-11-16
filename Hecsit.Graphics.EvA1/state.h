#pragma once
class GameState
{
public:
	GameState();
	~GameState();

	enum State
	{
		Game,
		Menu,
		Pause
	};

	struct ActivatedEvents
	{
		bool goUp;
		bool goDown;
		bool goLeft;
		bool goRight;
	};

	State GetStatus();
	ActivatedEvents * GetEvents();
	void SetStatus(State);
	void InitEvents();
private:
	State _status;
	ActivatedEvents _events;
};


