#pragma once
#include "raylib.h"

class Entity
{
public:
	Vector2 pos = { 0,0 };

	virtual void update() = 0;
	virtual void render(Vector2 gridPos, float tileSide) = 0;

	virtual ~Entity() {};
};

class StarChaser : public Entity
{
public:
	StarChaser()
	{
		pos = {0,0};
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
	}

	void update() override;
	void render(Vector2 gridPos, float tileSide) override;

	~TradingPost() {};
};