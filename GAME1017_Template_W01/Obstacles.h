#pragma once
#ifndef _OBSTACLES_H_
#define _OBSTACLES_H_
#include "Sprite.h"

const float BACKGROUNDX = 1024.0;
const float BACKGROUNDY = 768.0;

const float FLOORX = 512.0;
const float FLOORY = 256.0;

const float PILLARX = 190.0;
const float PILLARY = 514.0;

enum OBSTACLES { SPEAR, SPIKES, SAW };

class Background : public Sprite
{
public:
	Background(float x);
};

class Floor : public Sprite
{
public:
	Floor(float x);
};

class Pillar : public Sprite
{
public:
	Pillar(float x);
};

class Obstacle : public Sprite
{
public:
	Obstacle(float moveX, SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	float GetMoveX() { return m_moveX; }
	virtual void Update() {};
	
private:
	float m_moveX;
};

class Saw : public Obstacle
{
public:
	Saw(int x, int y);
	virtual void Update() override;
	
};

class Spikes : public Obstacle
{
public:
	Spikes(int x);
};

class Spear : public Obstacle
{
public:
	Spear(int x, int y);
};

#endif