#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

//for Mac
// #include <SDL2/SDL.h>
// #include <SDL_image.h>
// #include <SDL_mixer.h>
// #include <SDL_ttf.h>
// #include <iostream>

#include "Math.hpp"
#include "Entity.hpp"
#include "Player.hpp"
class Shootblock : public Entity{
public:
    Shootblock();
    Shootblock(vec2f b_pos, SDL_Texture* b_tex, float b_w, float b_h);
    void shoot(int direction, int**map);
    void check_collision(Player& p2, int** map);
    //bool appear;
    void spawn(vec2f b_pos);
    bool able(int dir, vec2f b_pos, int** map);
    //void crack(int** map);
    void disappear(int **map);
    void move_trigger();
    void update(Player& p2,int **map, int iam);
private:
    int state;
    int speed;
    vec2f pos;
    vec2f cframe;
    bool crash;
    float blockpixel;
    bool moving;
    bool moved;
    int direction;

};