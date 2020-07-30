#pragma once
#ifndef _GAMEHUD_H_
#define _GAMEHUD_H_

#include "Player.h"

class GameHUD
{
public:
	GameHUD(Player* player);
	~GameHUD();

	void Update();
	void Clean();
	void Render();

private:

	
};

#endif