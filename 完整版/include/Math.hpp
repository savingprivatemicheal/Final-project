#pragma once

struct vec2f
{
	vec2f()
	:x(0.0f), y(0.0f){}
	vec2f(float p_x, float p_y)
	:x(p_x), y(p_y){}
	float x, y;
	vec2f operator+(vec2f v2){
		vec2f temp(0, 0);
		temp.x = x+v2.x;
		temp.y = y+v2.y;
		return temp;
	}
};

struct vec2d
{
	vec2d()
	:x(0), y(0){}
	vec2d(int p_x, int p_y)
	:x(p_x), y(p_y){}
	int x, y;
};