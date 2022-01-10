#include "Timefreeze.hpp"

Timefreeze::Timefreeze(vec2f b_pos, SDL_Texture* b_tex, float b_w, float b_h):Entity(b_pos, b_tex, b_w, b_h)
{
	cd=2000;
	divide=1.5;
	can_shoot=true;
	has_divided=false;
	lasting=500;
	spdtemp=5;//oppo->get_speed();
	able=false;
}
void Timefreeze::update(){
	if(is_on==true){
		if(has_divided==false){
			oppo->set_speed(static_cast<int>(1));
			oppo->set_can_shoot(false);
		}
		has_divided=true;
		lastingticks+=1;
		//std::cout<<"lastingticks = "<<lastingticks<<std::endl;
		can_shoot=false;
		reset();
	}
	if(lastingticks>=lasting){
		is_on=false;
		oppo->reset_speed();
		has_divided=false;
		oppo->set_can_shoot(true);
		lastingticks=0;
		can_shoot=true;
	}
	ticks+=1;
	if(ticks>=cd){ticks=cd;  able=true;}
	else{able=false;}
}
void Timefreeze::reset(){ticks=0;}
void Timefreeze::doit(){is_on=true;}