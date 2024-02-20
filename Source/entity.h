#pragma once
#include "raylib.h"

class Entity
{
public:
	Vector2 pos = { 0,0 };

	virtual void update() = 0;
	virtual void render() = 0;

	virtual ~Entity() {};
};

class StarChaser : public Entity
{
public:
	StarChaser(Vector2 position)
	{
		pos = position;
	}

	void update() override;
	void render() override;

	~StarChaser() {};
};

class FallenStar : public Entity
{
public:
	FallenStar(Vector2 position)
	{
		pos = position;
	}

	void update() override;
	void render() override;

	~FallenStar() {};
};

class SpaceShip : public Entity
{
public:
	SpaceShip(Vector2 position)
	{
		pos = position;
	}

	void update() override;
	void render() override;

	~SpaceShip() {};
};

class TradingPost : public Entity
{
public:
	TradingPost(Vector2 position)
	{
		pos = position;
	}

	void update() override;
	void render() override;

	~TradingPost() {};
};