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

#include "Entity.hpp"
#include "Player.hpp"

class RenderWindow{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanup();
	void clear();
	void render(Entity& p_entity, float ratio, vec2f trans = vec2f(0.0f, 0.0f));
	void renderex(Entity& p_entity, float ratio, vec2f trans = vec2f(0.0f, 0.0f), SDL_RendererFlip flip = SDL_FLIP_NONE, double theta = 0.0);
	void renderplayer(Player& p_player, float ratio, vec2f trans = vec2f(0.0f, 0.0f));
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};