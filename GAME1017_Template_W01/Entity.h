#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "EntityState.h"
#include "GameObject.h"

class Animator;

class Entity : public GameObject
{
public:
	Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t);
	~Entity();
	
	virtual void update() = 0;
	virtual void clean() = 0;
	
	void MovementUpdate();
	Animator* GetAnimator() { return m_animator; }
	void AddAnimator(Animator* animator);

	bool IsAlive() { return m_alive; }

	SDL_FRect* GetBody() { return &m_body; }

protected:
	Animator* m_animator;

	bool m_alive;
	
	SDL_FRect m_body;
	void SetBodyPosition();
	
	EntityState* m_state;
	
};

#include "Animator.h"

#endif