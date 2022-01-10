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

#include "Entity.hpp"
#include "Math.hpp"


class Choose_State
{
public:
	int state=0;
	Choose_State(vec2f pos, SDL_Texture* c_tex, float c_w, float c_h, vec2f pos2, SDL_Texture* c_tex2, float c_w2, float c_h2);
	Entity* pbackground();
	Entity* ptotalbutton();
	int Get_state();
	void bgupdate();//backgroundupdate
	void buttonupdate(vec2f);//buttonupdate
	int Change_State(int i);
	vec2f Get_newgamepos();
	vec2f Get_tutorialpos();
	vec2f Get_settingpos();
	vec2f Get_escpos();
	vec2f Get_continuepos();
private:
	vec2f currentframe;
	int frame_count;
	bool ifc=true;//inverse frame count
	Entity background;
	Entity totalbutton;
	vec2f newgamepos;
	vec2f tutorialpos;
	vec2f settingpos;
	vec2f escpos;
	vec2f continuepos;
	int framecounter;
	bool reversecount;
};