#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL.h"

class Sprite // Inline class.
{
public: // Inherited and public.
	Sprite(SDL_Rect s, SDL_FRect d, SDL_Texture* t)
		:m_src(s), m_dst(d), m_pText(t), m_angle(0.0) {}
	
	virtual void Render();
	
	SDL_Rect* GetSrcP() { return &m_src; }
	SDL_FRect* GetDstP() { return &m_dst; }
	double& GetAngle() { return m_angle; }
	SDL_Texture* GetTexture() { return m_pText; }
	
	SDL_FPoint GetCenter();
	
	void SetAngle(double a) { m_angle = a; }
	void SetSrcCords(int x, int y);
	void SetDstSize(int w, int h);
	void SetTexture(SDL_Texture* text) { m_pText = text; }
	
protected: // Private BUT inherited.
	double m_angle;
	SDL_Rect m_src;
	SDL_FRect m_dst;
	SDL_Texture* m_pText;
	
private: // Private NOT inherited.
};

#endif