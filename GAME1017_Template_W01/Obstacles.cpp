#include "Obstacles.h"
#include "Config.h"
#include "Engine.h"
#include "TextureManager.h"

Background::Background(float x) : Sprite({ 0,0,1024,768 }, { x,0,BACKGROUNDX,BACKGROUNDY }, TEMA::GetTexture("background"))
{}

Floor::Floor(float x) : Sprite({ 1024,510,512,256 }, { x,FLOOR,FLOORX,FLOORY }, TEMA::GetTexture("background"))
{}

Pillar::Pillar(float x) : Sprite({ 1024,0,256,511 }, { x,0,PILLARX,PILLARY }, TEMA::GetTexture("background"))
{}

Obstacle::Obstacle(float moveX, SDL_Rect s, SDL_FRect d, SDL_Texture* t) : Sprite(s,d,t), m_moveX(moveX)
{}

Saw::Saw(int x, int y) : Obstacle(4.0f,{128,128,(int)SAWX,128 },{(float)x,FLOOR - 100.0f - (float)y,100,100 },TEMA::GetTexture("obstacles"))
{}

void Saw::Update()
{
	this->m_angle += 5;
}

Spikes::Spikes(int x) : Obstacle(0.0f,{ 128,64,(int)SPIKESX,64 }, { (float)x,FLOOR - 60.0f,128,64 }, TEMA::GetTexture("obstacles"))
{}

Spear::Spear(int x, int y) : Obstacle(0.0f,{ 0,0,(int)SPEARX,448 }, { (float)x,(float)y,120,420 }, TEMA::GetTexture("obstacles"))
{}
