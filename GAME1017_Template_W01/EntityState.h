#pragma once
#ifndef _ENTITYSTATE_H_
#define _ENTITYSTATE_H_

class Player;

class BehaviorState
{
public:
	BehaviorState(Player* player);
	~BehaviorState();

	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	
protected:
	Player* m_player;
	
};

class EntityState
{
public:
	EntityState(Player* player);
	~EntityState();

	void Update();

	void ChangeState(BehaviorState* newState);
	
private:
	BehaviorState* m_state;
	Player* m_player;
	
};

//States:

class ScrollState : public BehaviorState
{
public:
	ScrollState(Player* player);
	~ScrollState();

	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;
	
private:

	
};

class JumpState : public BehaviorState
{
public:
	JumpState(Player* player);
	~JumpState();

	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:

	
};

class RunState : public BehaviorState
{
public:
	RunState(Player* player);
	~RunState();

	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:


};

#include "Player.h"

#endif