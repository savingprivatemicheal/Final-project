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
#include "Entity.hpp"

class Skills{
protected:
	Player* me;
	Player* oppo;
	double cd;
	double lasting;
	double damage;
	double ticks;
	double lastingticks;
	int** land;
	int blockpixel;
	bool is_on;
	bool able;
public:
	Skills(){ticks=0; lastingticks=0; is_on=false; blockpixel=40; able=false;}
	void setPlayer(Player& me, Player& oppo){this->me = &me; this->oppo = &oppo;}
	void setLand(int** map){land = map;}
	void setCD(double x){cd = x;}
	void setLasting(double x){lasting = x;}
	void setDamage(double x){damage = x;}
	double getCD(){return cd;}
	double getnowticks(){return ticks;}
	double getLasting(){return lasting;}
	double getDamage(){return damage;}
	bool getIS_ON(){return is_on;}
	bool getAble(){return able;}
	Player* getoppo(){return oppo;}
	Player* getme(){return me;}
	virtual void update(){;};
	virtual void doit(){is_on=true;}
	virtual void reset(){ticks=0;}

};