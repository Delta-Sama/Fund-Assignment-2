#include "ScrollingManager.h"

#include <iostream>

#include "Config.h"
#include "Engine.h"
#include "TextureManager.h"

std::vector<Background*> SCMA::m_background;
std::vector<Floor*> SCMA::m_floor;
int SCMA::m_windowSizeX;
int SCMA::m_minBackgrounds;
int SCMA::m_minFloors;

const float BACKGROUNDX = 1024.0;
const float BACKGROUNDY = 768.0;
Background::Background(float x, float y) : Sprite({0,0,1024,768 },{x,y,BACKGROUNDX,BACKGROUNDY },TEMA::GetTexture("background"))
{}

const float FLOORX = 512.0;
const float FLOORY = 256.0;
Floor::Floor(float x) : Sprite({ 1024,510,512,256 }, { x,FLOOR,512,256 }, TEMA::GetTexture("background"))
{}

void ScrollingManager::Init()
{
	SDL_GetWindowSize(Engine::Instance().GetWindow(), &m_windowSizeX, nullptr);
	m_minBackgrounds = GetMinFitAmount(BACKGROUNDX);
	m_minFloors = GetMinFitAmount(FLOORX);
}

int ScrollingManager::GetMinFitAmount(int fitSize)
{
	int size = 0;
	int amount = 0;
	while (size < m_windowSizeX)
	{
		amount++;
		size += fitSize;
	}
	return amount + 1;
}

void ScrollingManager::Update()
{
	for (std::vector<Background*>::iterator bck = m_background.begin(); bck != m_background.end();) {
		if ((*bck)->GetDstP()->x + (*bck)->GetDstP()->w < 0) {
			delete *bck;
			bck = m_background.erase(bck);
		}
		else {
			bck++;
		}
	}
	for (std::vector<Floor*>::iterator flr = m_floor.begin(); flr != m_floor.end();) {
		if ((*flr)->GetDstP()->x + (*flr)->GetDstP()->w < 0) {
			delete* flr;
			flr = m_floor.erase(flr);
		}
		else {
			flr++;
		}
	}

	while (m_background.size() < m_minBackgrounds) {
		int maxX = 0;
		for (Background* bck : m_background) {
			int _x = bck->GetDstP()->x + bck->GetDstP()->w;
			if (_x > maxX) {
				maxX = _x;
			}
		}
		m_background.push_back(new Background(maxX,0));
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
	}

	for (Background* bck : m_background) {
		bck->GetDstP()->x -= BACKMOVE;
	}
	for (Floor* flr : m_floor) {
		flr->GetDstP()->x -= GENMOVE;
	}
}

void ScrollingManager::Render()
{
	for (Background* bck : m_background)
	{
		bck->Render();
	}
	for (Floor* flr : m_floor)
	{
		flr->Render();
	}
}

void ScrollingManager::Clean()
{
	for (Background* bck : m_background)
	{
		delete bck;
	}
	for (Floor* flr : m_floor)
	{
		delete flr;
	}
}
