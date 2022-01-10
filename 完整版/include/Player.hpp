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
//#include "Blockclock.hpp"

class Player
{
public:
	//init
	Player(vec2f p_pos, SDL_Texture* p_tex, int stand);
	//get
	SDL_Texture* gettex();
	SDL_Rect getcurrentframe();
	vec2f &get_pos();
	double get_angle();
	SDL_RendererFlip get_flip();
	int absdir();
	float get_hp();
	int get_moving();
	int get_facing();
	int get_speed();
	vec2d get_blockpos();
	bool get_can_shoot();
	//alter
	void Alterpos(vec2f a_pos);
	void Alterframe(vec2f i_frame);
	void move_trigger(int dir);
	void update(int** map);
	void reset_facing();
	void set_speed(int spd);
	void set_can_shoot(bool cann);
	//void load_map(int** p_map);
	void init(float p_spd, float p_hp, float p_atk);
	void update_blockpos();
	bool check_pcollision(Player& p2, int** map);
	bool collision(Player& p2, int** map);
	//void find_standpoint(int** map);
	void reduce_hp(float p_rhp);
	bool block_up(int** map, Player& p2, bool blue);
	void midair(int** map);
	void reset_speed();
private:
	SDL_Texture* tex;
	vec2f pos;
	int moving, facing, standing;
	int c_frame;
	SDL_Rect currentFrame;
	vec2f v;
	float maxhp, hp, atk, speed, speed_o;
	//int **map;
	SDL_RendererFlip flip;
	double angle;
	vec2d blockpos;
	int stand_itr;
	int move_itr;
	int ppb;
	bool can_shoot;
};