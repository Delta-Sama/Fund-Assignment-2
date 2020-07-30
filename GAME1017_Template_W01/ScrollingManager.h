#pragma once
#ifndef _SCROLLINGMANAGER_H_
#define _SCROLLINGMANAGER_H_
#include <vector>

#include "Sprite.h"
#include "Vector2.h"

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

class ScrollingManager
{
public:
	static void Init();
	static void Update();
	static void Render();
	static void Clean();

	static int GetMinFitAmount(int size);
	static void DeleteFromArrays(std::vector<Sprite*>::iterator sprt);

private:
	static std::vector<Sprite*> m_scrollingObjects;
	
	static std::vector<Background*> m_background;
	static std::vector<Floor*> m_floor;
	static std::vector<Pillar*> m_pillars;
	
	static int m_windowSizeX;
	static int m_minBackgrounds;
	static int m_minFloors;
	static int m_minPillars;
};

typedef ScrollingManager SCMA;

#endif