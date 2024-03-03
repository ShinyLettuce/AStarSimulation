#pragma once
#include "raylib.h"

class Entity
{
public:
	Vector2 pos = { 0,0 };
	Color color = WHITE;

	virtual void update() = 0;
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
	};

	ChaserState currentState = ChaserState::STAR;
	int timer = 1;
	int pathTraversalIndex = 1;
	int currentStamina = 60;
	int maxStamina = 60;

	StarChaser()
	{
		pos = {0,0};
		color = LIGHTGRAY;
	}

	void update() override;
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

	void update() override;
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

	void update() override;
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

	void update() override;
	void render(Vector2 gridPos, float tileSide) override;

	~TradingPost() {};
};