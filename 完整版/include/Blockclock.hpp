#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

// //for Mac
// #include <SDL2/SDL.h>
// #include <SDL_mixer.h>
// #include <SDL_ttf.h>
// #include <iostream>

using namespace std;

#include "Entity.hpp"
#include "Math.hpp"
#include "Player.hpp"
#include "Shootblock.hpp"

class Blockclock:public Entity
{
public:
	//Blockclock();
	Blockclock(vec2f pos, SDL_Texture* c_tex, float c_w, float c_h, int most);
	int get_now();
	void update();
	void minus();
private:
	int now;
	int most;
	int tick;
	vec2f currentframe;
	int frame_count;
};