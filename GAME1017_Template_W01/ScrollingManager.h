#pragma once
#ifndef _SCROLLINGMANAGER_H_
#define _SCROLLINGMANAGER_H_
#include <vector>

#include "Sprite.h"
#include "Vector2.h"

class Background : public Sprite
{
public:
	Background(float x, float y);
};

class Floor : public Sprite
{
public:
	Floor(float x);
};

class ScrollingManager
{
public:
	static void Init();
	static void Update();
	static void Render();
	static void Clean();

	static int GetMinFitAmount(int size);
	
private:
	static std::vector<Background*> m_background;
	static std::vector<Floor*> m_floor;
	static int m_windowSizeX;
	static int m_minBackgrounds;
	static int m_minFloors;
};

typedef ScrollingManager SCMA;

#endif