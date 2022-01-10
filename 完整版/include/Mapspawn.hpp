//
// Created by 錡亭勳 on 2021/12/15.
//

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
#include <bits/stdc++.h>

// // //for Mac
// #include <SDL2/SDL.h>
// #include <SDL_image.h>
// #include <SDL_mixer.h>
// #include <SDL_ttf.h>
// #include <iostream>

#include "Math.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"
//#include "RenderWindow.hpp"

// class mapBlock{
// private:
//     Entity e;
//     vec2f from;
//     vec2f to;
// public:
//     mapBlock(Entity , vec2f , vec2f );
//     vec2f pos;
//     void spawnThisBlock();
//     void moveThisBlock(vec2f, vec2f);

// };
class Map{
private:
    RenderWindow *window;
    int numOfSpace;
    void initLand();
    void spawnMidRec();
    void spawnSideRecs();
    void checkspace();
    void finalGrow();
    int right;
    int left;
    int tx;
    int ty;
    int mid;
    //midrec
    int mid_x;
    int mid_y;
    int x1;
    int x2;
    int y1;
    int y2;
    //rightrec
    int rmid_x;
    int rmid_y;
    int rx1;
    int rx2;
    int ry1;
    int ry2;
    //leftrec
    int lmid_x;
    int lmid_y;
    int lx1;
    int lx2;
    int ly1;
    int ly2;

public:
    vec2f total;
    vec2f startPos;
    //Map(RenderWindow&);
    //std::vector<Entity> arrmap;
    void init();
    int** land;
    vec2f setinit1();
    vec2f setinit2();

};
