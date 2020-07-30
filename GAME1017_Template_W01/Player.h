#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player final : public Entity
{
public: // Methods
	Player();
	~Player();

	virtual void update() override;
	virtual void clean() override;

	void KeyboardInput();
	void GamepadInput();

	int movement[2] = { 0,0 };
private:
	
};

#endif