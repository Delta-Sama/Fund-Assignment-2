#pragma once
#ifndef _SCROLLINGMANAGER_H_
#define _SCROLLINGMANAGER_H_
#include <vector>

#include "Sprite.h"
#include "Obstacles.h"
#include "Player.h"

class ScrollingManager
{
public:
	static void Init(Player* player);
	static void Update();
	static void Render();
	static void Clean();

	static int GetMinFitAmount(int size);
	static void DeleteFromArrays(std::vector<Sprite*>::iterator sprt);
	static void AddObstacle(OBSTACLES type, int x = 0, int y = 0);
	static void CreateRandomObstacle();
	static void RegenerateBackground();
	static void Stop();

	static std::vector<Obstacle*>* GetObstacles() { return &m_obstacles; }

private:
	static Player* m_player;
	
	static std::vector<Sprite*> m_scrollingObjects;
	
	static std::vector<Background*> m_background;
	static std::vector<Floor*> m_floor;
	static std::vector<Pillar*> m_pillars;

	static std::vector<Obstacle*> m_obstacles;

	static int m_lastObstacleTime;
	
	static int m_minBackgrounds;
	static int m_minFloors;
	static int m_minPillars;

	static bool m_moving;
};

typedef ScrollingManager SCMA;

#endif