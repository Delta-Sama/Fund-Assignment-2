#include "ScrollingManager.h"

#include <iostream>

#include "Config.h"
#include "Engine.h"
#include "TextureManager.h"

std::vector<Sprite*> SCMA::m_scrollingObjects;
std::vector<Background*> SCMA::m_background;
std::vector<Floor*> SCMA::m_floor;
std::vector<Pillar*> SCMA::m_pillars;
int SCMA::m_windowSizeX;
int SCMA::m_minBackgrounds;
int SCMA::m_minFloors;
int SCMA::m_minPillars;

const float BACKGROUNDX = 1024.0;
const float BACKGROUNDY = 768.0;
Background::Background(float x) : Sprite({0,0,1024,768 },{x,0,BACKGROUNDX,BACKGROUNDY },TEMA::GetTexture("background"))
{}

const float FLOORX = 512.0;
const float FLOORY = 256.0;
Floor::Floor(float x) : Sprite({ 1024,510,512,256 }, { x,FLOOR,FLOORX,FLOORY }, TEMA::GetTexture("background"))
{}

const float PILLARX = 190.0;
const float PILLARY = 514.0;
Pillar::Pillar(float x) : Sprite({ 1024,0,256,511 }, { x,0,PILLARX,PILLARY }, TEMA::GetTexture("background"))
{}

void ScrollingManager::Init()
{
	SDL_GetWindowSize(Engine::Instance().GetWindow(), &m_windowSizeX, nullptr);
	m_minBackgrounds = GetMinFitAmount(BACKGROUNDX);
	m_minFloors = GetMinFitAmount(FLOORX);
	m_minPillars = GetMinFitAmount(PILLARX);
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

	for (Background* bck : m_background) {
		bck->GetDstP()->x -= BACKMOVE;
	}
	for (Floor* flr : m_floor) {
		flr->GetDstP()->x -= GENMOVE;
	}
	for (Pillar* pil : m_pillars) {
		pil->GetDstP()->x -= GENMOVE;
	}
}

void ScrollingManager::Render()
{
	for (Background* bck : m_background)
	{
		bck->Render();
	}
	for (Pillar* pil : m_pillars)
	{
		pil->Render();
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
	for (Pillar* pil : m_pillars)
	{
		delete pil;
	}
}
