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

class RollState : public BehaviorState
{
public:
	RollState(Player* player);
	~RollState();

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
	int m_jumpProgress;
	int m_factor;
	int m_maxJumpProgress;
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

class DieState : public BehaviorState
{
public:
	DieState(Player* player);
	~DieState();

	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	int m_diedAnim;

};

#include "Player.h"

#endif