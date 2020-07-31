#include "ScrollingManager.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "Config.h"
#include "Engine.h"

#include <iostream>

Player* SCMA::m_player = nullptr;
std::vector<Sprite*> SCMA::m_scrollingObjects;
std::vector<Background*> SCMA::m_background;
std::vector<Floor*> SCMA::m_floor;
std::vector<Pillar*> SCMA::m_pillars;
std::vector<Obstacle*> SCMA::m_obstacles;
int SCMA::m_minBackgrounds;
int SCMA::m_minFloors;
int SCMA::m_minPillars;
int SCMA::m_lastObstacleTime = FPS * 5;

void ScrollingManager::Init(Player* player)
{
	m_player = player;
	m_minBackgrounds = GetMinFitAmount(BACKGROUNDX);
	m_minFloors = GetMinFitAmount(FLOORX);
	m_minPillars = GetMinFitAmount(PILLARX);
}

int ScrollingManager::GetMinFitAmount(int fitSize)
{
	int size = 0;
	int amount = 0;
	while (size < WIDTH)
	{
		amount++;
		size += fitSize;
	}
	return amount + 1;
}

void ScrollingManager::DeleteFromArrays(std::vector<Sprite*>::iterator sprt)
{
	for (auto flr = m_floor.begin(); flr != m_floor.end();) {
		if (*flr == *sprt) {
			flr = m_floor.erase(flr);
		}
		else {
			flr++;
		}
	}
	for (auto pil = m_pillars.begin(); pil != m_pillars.end();) {
		if (*pil == *sprt) {
			pil = m_pillars.erase(pil);
		}
		else {
			pil++;
		}
	}
	for (auto bck = m_background.begin(); bck != m_background.end();) {
		if (*bck == *sprt) {
			bck = m_background.erase(bck);
		}
		else {
			bck++;
		}
	}
	for (auto obst = m_obstacles.begin(); obst != m_obstacles.end();) {
		if (*obst == *sprt) {
			obst = m_obstacles.erase(obst);
		}
		else {
			obst++;
		}
	}
}

void ScrollingManager::AddObstacle(OBSTACLES type,int x, int y)
{
	switch (type)
	{
	case SPEAR:
		m_obstacles.push_back(new Spear(WIDTH + x, y));
		m_scrollingObjects.push_back(m_obstacles.back());
		break;
	case SPIKES:
		m_obstacles.push_back(new Spikes(WIDTH + x));
		m_scrollingObjects.push_back(m_obstacles.back());
		break;
	case SAW:
		m_obstacles.push_back(new Saw(WIDTH + x, y));
		break;
	default:
		break;
	}
}

void ScrollingManager::CreateRandomObstacle()
{
	if (--m_lastObstacleTime <= 0)
	{
		float length = 1.5;
		int rnd = 1 + rand() % 7;
		switch (rnd)
		{
		case 1: // SPIKES
			{
				AddObstacle(SPIKES);
			}
			break;
		case 2: // SPEAR
			{
				AddObstacle(SPEAR);
			}
			break;
		case 3: // SAW
			{
				AddObstacle(SAW,0, 96 * (rand() % 2));
			}
			break;
		case 4: // DOUBLE SAW
			{
				AddObstacle(SAW, 0, 0);
				AddObstacle(SAW, 0, 300);
			}
			break;
		case 5: // ROLL-JUMP-ROLL
			{
				AddObstacle(SPEAR);
				AddObstacle(SPIKES, SPEARX + 230);
				AddObstacle(SPEAR, SPEARX + SPIKESX + 230 * 2);
				length = 4;
			}
			break;
		case 6: // LONG SPIKES
			{
				AddObstacle(SPIKES, 0);
				AddObstacle(SPIKES, SPIKESX);
				length = 3;
			}
			break;
		case 7: // JUMP PARTY
			{
				AddObstacle(SPIKES, 0);
				AddObstacle(SPIKES, SPIKESX * 3);
				AddObstacle(SPIKES, SPIKESX * 6);
				AddObstacle(SPIKES, SPIKESX * 9);
				length = 4.5;
			}
		break;
		default:
			break;
		}

		m_lastObstacleTime = FPS * length + rand() % 4 * (FPS / 2);
	}
}

void ScrollingManager::Update()
{
	for (auto sprt = m_scrollingObjects.begin(); sprt != m_scrollingObjects.end();) {
		if ((*sprt)->GetDstP()->x + (*sprt)->GetDstP()->w < 0) {
			DeleteFromArrays(sprt);
			delete* sprt;
			sprt = m_scrollingObjects.erase(sprt);
		}
		else {
			sprt++;
		}
	}
	
	RegenerateBackground();
	CreateRandomObstacle();

	for (Background* bck : m_background) {
		bck->GetDstP()->x -= BACKMOVE;
	}
	
	for (Pillar* pil : m_pillars) {
		pil->GetDstP()->x -= MIDMOVE;
	}

	for (Floor* flr : m_floor) {
		flr->GetDstP()->x -= FORWMOVE;
	}

	for (Obstacle* obst : m_obstacles)
	{
		obst->GetDstP()->x -= FORWMOVE + obst->GetMoveX();
		obst->Update();
		if (COMA::AABBCheck(*obst->GetDstP(), *m_player->GetBody()))
		{
			m_player->SetAlive(false);
		}
	}
}

void ScrollingManager::Render()
{
	for (Sprite* obj : m_scrollingObjects)
	{
		obj->Render();
	}
	for (Obstacle* obst : m_obstacles)
	{
		obst->Render();
	}
}

void ScrollingManager::Clean()
{
	m_player = nullptr;
	for (Sprite* obj : m_scrollingObjects)
	{
		delete obj;
	}
	m_scrollingObjects.clear();
	m_scrollingObjects.shrink_to_fit();
	m_pillars.clear();
	m_pillars.shrink_to_fit();
	m_floor.clear();
	m_floor.shrink_to_fit();
	m_obstacles.clear();
	m_obstacles.shrink_to_fit();
}

void ScrollingManager::RegenerateBackground()
{
	while (m_background.size() < m_minBackgrounds) {
		int maxX = 0;
		for (Background* bck : m_background) {
			int _x = bck->GetDstP()->x + bck->GetDstP()->w;
			if (_x > maxX) {
				maxX = _x;
			}
		}
		m_background.push_back(new Background(maxX));
		m_scrollingObjects.push_back(m_background.back());
	}
	while (m_floor.size() < m_minFloors) {
		int maxX = 0;
		for (Floor* flr : m_floor) {
			int _x = flr->GetDstP()->x + flr->GetDstP()->w;
			if (_x > maxX) {
				maxX = _x;
			}
		}
		m_floor.push_back(new Floor(maxX));
		m_scrollingObjects.push_back(m_floor.back());
	}
	while (m_pillars.size() < m_minPillars) {
		int maxX = 0;
		for (Pillar* pil : m_pillars) {
			int _x = pil->GetDstP()->x + pil->GetDstP()->w;
			if (_x > maxX) {
				maxX = _x;
			}
		}
		m_pillars.push_back(new Pillar(maxX));
		m_scrollingObjects.push_back(m_pillars.back());
	}
}