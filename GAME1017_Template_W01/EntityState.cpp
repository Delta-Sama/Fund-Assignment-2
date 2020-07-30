#include "EntityState.h"

BehaviorState::BehaviorState(Player* player) : m_player(player)
{
	
}

BehaviorState::~BehaviorState() {}

EntityState::EntityState(Player* player) : m_player(player)
{
	ChangeState(new RunState(m_player));
}

EntityState::~EntityState()
{
	
}

void EntityState::Update()
{
	
}

void EntityState::ChangeState(BehaviorState* newState)
{
	if (m_state)
	{
		m_state->Exit();
		delete m_state;
	}
	m_state = newState;
	m_state->Enter();
}

//States:

//SCROLL:

ScrollState::ScrollState(Player* player) : BehaviorState(player)
{
	
}

ScrollState::~ScrollState() {}

void ScrollState::Enter()
{
	
}

void ScrollState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("scroll");
}

void ScrollState::Exit()
{
}

//JUMP:

JumpState::JumpState(Player* player) : BehaviorState(player)
{
	
}

JumpState::~JumpState() {}

void JumpState::Enter()
{
	
}

void JumpState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("jump");
}

void JumpState::Exit()
{
	
}

// RUN:

RunState::RunState(Player* player) : BehaviorState(player)
{
	
}

RunState::~RunState() {}

void RunState::Enter()
{
	
}

void RunState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("run");
}

void RunState::Exit()
{
	
}
