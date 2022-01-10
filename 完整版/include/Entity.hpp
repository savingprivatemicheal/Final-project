#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

// //for Mac
// #include <SDL2/SDL.h>
// #include <SDL_image.h>
// #include <SDL_mixer.h>
// #include <SDL_ttf.h>
// #include <iostream>

#include "Math.hpp"

class Entity
{
public:
	Entity();
	Entity(vec2f p_pos, SDL_Texture* p_tex, float p_w, float p_h);
	vec2f& getpos();
	SDL_Texture* gettex();
	SDL_Rect getcurrentframe();
	void Alterpos(vec2f a_pos);
	void Alterframe(vec2f a_frame);
private:
	vec2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};