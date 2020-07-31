#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "GameObject.h"

class Animator;
class EntityState;

class Entity : public GameObject
{
public:
	Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	~Entity();
	
	virtual void update() = 0;
	virtual void clean() = 0;

	void StopX();
	void SetAccelX(float a);
	float GetVelX();
	
	void MovementUpdate();
	
	Animator* GetAnimator() { return m_animator; }
	void AddAnimator(Animator* animator);

	bool IsAlive() { return m_alive; }
	void SetAlive(bool alive) { m_alive = alive; }
	
	SDL_FRect* GetBody() { return &m_body; }

	EntityState* GetStateMachine() { return m_state; }

private:
	Vec2 m_velocity;
	Vec2 m_accel;
	float m_maxVelocity;

	float m_drag, m_speed;
	
protected:
	Animator* m_animator;

	bool m_alive;
	
	SDL_FRect m_body;
	void SetDstPosition();
	
	EntityState* m_state;
	
};

#include "Animator.h"
#include "EntityState.h"

#endif