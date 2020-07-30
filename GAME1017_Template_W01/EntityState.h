#pragma once
#ifndef _ENTITYSTATE_H_
#define _ENTITYSTATE_H_

class BehaviorState
{
public:
	BehaviorState();
	~BehaviorState();

	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	
protected:
	
};

class EntityState
{
public:
	EntityState();
	~EntityState();

	void Update();

	void ChangeState();
	
private:
	BehaviorState* m_state;
	
};

//States:

class ScrollState : public BehaviorState
{
public:
	ScrollState();
	~ScrollState();

	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;
	
private:

	
};

class JumpState : public BehaviorState
{
public:
	JumpState();
	~JumpState();

	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:

	
};

class RunState : public BehaviorState
{
public:
	RunState();
	~RunState();

	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:


};

#endif