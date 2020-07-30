#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite.h"
#include <SDL.h>

class Button : public Sprite
{
public:
	int Update();
	void Render();
	
protected:
	Button(SDL_Rect src, SDL_FRect dst, SDL_Texture* t);
	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state;
	bool MouseCollision();
	virtual void Execute() = 0;
	
};

//Buttons:

class PlayButton : public Button
{
public:
	PlayButton(SDL_Rect src, SDL_FRect dst);
	
private:
	virtual void Execute() override;
	
};

class RestartButton : public Button
{
public:
	RestartButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t);
	
private:
	virtual void Execute() override;
	
};

class ExitButton : public Button
{
public:
	ExitButton(SDL_Rect src, SDL_FRect dst, SDL_Texture* t);
	
private:
	virtual void Execute() override;
	
};

#endif