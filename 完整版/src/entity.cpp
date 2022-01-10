#include "Entity.hpp"


Entity::Entity(vec2f p_pos, SDL_Texture* p_tex, float p_w, float p_h)
:pos(p_pos), tex(p_tex)
{
	currentFrame.w = p_w; 
	currentFrame.h = p_h;
	currentFrame.x = 0;
	currentFrame.y = 0;
}


SDL_Texture* Entity::gettex()
{
	return tex;
}

SDL_Rect Entity::getcurrentframe()
{
	return currentFrame;
}

void Entity::Alterpos(vec2f a_pos)
{
	pos = a_pos;
	
}

void Entity::Alterframe(vec2f a_frame)
{
	currentFrame.x = a_frame.x;
	currentFrame.y = a_frame.y;
}

vec2f& Entity::getpos()
{
	return pos;
}