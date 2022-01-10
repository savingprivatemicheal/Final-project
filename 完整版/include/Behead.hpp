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
#include "Player.hpp"
#include "Skills.hpp"
#include "Entity.hpp"

class Behead:public Skills, public Entity
{
public:
	Behead();
	Behead(vec2f b_pos, SDL_Texture* b_tex, float b_w, float b_h);
	void update();
	void doit();
	void reset();
private:
	int n;
	int m;
	bool hits;
	void check_hit();
	bool crash;
};