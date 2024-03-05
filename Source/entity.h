#pragma once
#include "raylib.h"

class Entity
{
public:
	Vector2 pos = { 0,0 };
	Color color = WHITE;

	virtual void render(Vector2 gridPos, float tileSide) = 0;

	virtual ~Entity() {};
};

class StarChaser : public Entity
{
public:

	enum class ChaserState
	{
		STAR,
		TRADING,
		SHIP,
		FINISHED
	};

	ChaserState currentState = ChaserState::STAR;
	int timer = 1;
	int pathTraversalIndex = 1;
	int currentStamina = 60;
	int maxStamina = 60;
	bool holdingStar = false;
	bool starSold = false;

	StarChaser()
	{
		pos = {0,0};
		color = LIGHTGRAY;
	}

	void render(Vector2 gridPos, float tileSide) override;

	~StarChaser() {};
};

class FallenStar : public Entity
{
public:
	FallenStar()
	{
		pos = {1,0};
		color = YELLOW;
	}

	void render(Vector2 gridPos, float tileSide) override;

	~FallenStar() {};
};

class SpaceShip : public Entity
{
public:
	SpaceShip()
	{
		pos = {2,0};
		color = GREEN;
	}

	void render(Vector2 gridPos, float tileSide) override;

	~SpaceShip() {};
};

class TradingPost : public Entity
{
public:
	TradingPost()
	{
		pos = {3,0};
		color = RED;
	}

	void render(Vector2 gridPos, float tileSide) override;

	~TradingPost() {};
};