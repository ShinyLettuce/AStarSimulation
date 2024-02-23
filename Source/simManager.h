#pragma once
#include "level.h"

class SimManager {
public:
	Level level;

	enum class SimState
	{
		EDIT,
		RUNNING
	};

	SimState currentState = SimState::EDIT;

	enum class EditState
	{
		BLOCK,
		STARCHASER,
		STAR,
		SHIP,
		TRADING
	};

	EditState editState = EditState::BLOCK;

	Vector2 mouseTileCollision();

	void update();
	void render();
	};