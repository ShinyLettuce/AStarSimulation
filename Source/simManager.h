#pragma once
#include "level.h"
#include "entity.h"
#include "cmath"

class SimManager {
public:
	Level level;
	StarChaser bountyHunterRoy;
	FallenStar fallenStar;
	TradingPost tradingPost;
	SpaceShip spaceShip;

	bool pathCalculated = false;
	bool victory = true;
	std::vector<Node> aStarPath = {};

	enum class SimState
	{
		EDIT,
		RUNNING,
		FINISHED
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

	float random_float01();
	float random_float_in_range(float min, float max);

	void initNewPath(Vector2 goal);
	void starChaserMove(Vector2 goal, StarChaser::ChaserState newState);

	void update();
	void render();
	};