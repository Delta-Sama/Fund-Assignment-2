#include "EntityState.h"

BehaviorState::BehaviorState() {}

BehaviorState::~BehaviorState() {}

EntityState::EntityState()
{
	m_state = new RunState();
}

EntityState::~EntityState()
{
	
}

void EntityState::Update()
{
	
}

//States:

ScrollState::ScrollState()
{
	
}

ScrollState::~ScrollState() {}

void ScrollState::Update()
{
	
}

void ScrollState::Enter()
{
}

void ScrollState::Exit()
{
}

JumpState::JumpState()
{
	
}

JumpState::~JumpState() {}

void JumpState::Update()
{
	
}

void JumpState::Enter()
{
}

void JumpState::Exit()
{
}

RunState::RunState()
{
	
}

RunState::~RunState() {}

void RunState::Update()
{
	
}

void RunState::Enter()
{
}

void RunState::Exit()
{
}
