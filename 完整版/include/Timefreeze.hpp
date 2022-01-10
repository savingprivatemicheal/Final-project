#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

// // //for Mac
// #include <SDL2/SDL.h>
// #include <SDL_image.h>
// #include <SDL_mixer.h>
// #include <SDL_ttf.h>
// #include <iostream>

#include "Math.hpp"
#include "Player.hpp"
#include "Skills.hpp"
#include "Entity.hpp"

class Timefreeze:public Skills, public Entity
{
public:
	Timefreeze();
	Timefreeze(vec2f b_pos, SDL_Texture* b_tex, float b_w, float b_h);
	void update();
	void doit();
	void reset();
private:
	double divide;
	bool can_shoot;
	bool has_divided;
	int spdtemp;
};