#pragma once
#ifndef _LEVEL_H_
#define _LEVEL_H_

class GameState;

class Level
{
public:
	Level(GameState* scene) : m_scene(scene) {};
	~Level() {};

	virtual void Load() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

protected:
	GameState* m_scene;
	
};

#include "States.h"

#endif