#include "Blockclock.hpp"

Blockclock::Blockclock(vec2f pos, SDL_Texture* c_tex, float c_w, float c_h, int most):Entity( pos, c_tex, c_w, c_h)
{
	this->most=most;
	now=5;
	tick=0;
	currentframe.x=0.0;
	currentframe.y=0.0;
	frame_count=0;
}
int Blockclock::get_now(){
	return now;
}
void Blockclock::update(){
	tick+=1;
	tick=tick%30;//generate speed
	if(tick==0&&now<most){
		frame_count+=1;
		if(frame_count==13){
			now+=1;
			frame_count=frame_count%13;
		}
		currentframe.x=16.0*frame_count;
		Alterframe(currentframe);
	}
}
void Blockclock::minus(){
	now-=1;
}