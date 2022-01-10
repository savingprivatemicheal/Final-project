#include "ChooseState.hpp"

Choose_State::Choose_State(vec2f pos, SDL_Texture* c_tex, float c_w, float c_h,vec2f pos2, SDL_Texture* c_tex2, float c_w2, float c_h2)
:background(pos, c_tex, c_w, c_h), totalbutton(pos2, c_tex2, c_w2, c_h2)
{
	currentframe.x=0.0;
	currentframe.y=0.0;
	frame_count=1.0;
	newgamepos.x=322.0;
	newgamepos.y=272.0;
	tutorialpos.x=2.0;
	tutorialpos.y=542.0;
	settingpos.x=646.0;
	settingpos.y=2.0;
	escpos.x=324.0;
	escpos.y=320.0;
	continuepos.x=324.0;
	continuepos.y=200.0;
	framecounter=0;
	reversecount=true;
}


void Choose_State::bgupdate(){
	framecounter+=1;
	if(framecounter%5==0){
		if(currentframe.x<252&&currentframe.y<211){
			currentframe.x+=frame_count;
			currentframe.y+=frame_count;
		}else if(currentframe.x>=252&&currentframe.y<211){
			currentframe.x=0;
			currentframe.y+=frame_count;
		}else if(currentframe.y>=211&&currentframe.x<252){
			currentframe.x+=frame_count;
			currentframe.y=0;
		}else if(currentframe.x>=252&&currentframe.y>=211){
			currentframe.x=0;
			currentframe.y=0;
		}


	}
	
	background.Alterframe(currentframe);
}

void Choose_State::buttonupdate(vec2f buttonframe){
	totalbutton.Alterframe(buttonframe);
}

int Choose_State::Get_state(){
	return state;
}
Entity* Choose_State::pbackground(){
	return &background;
}
Entity* Choose_State::ptotalbutton(){
	return &totalbutton;
}

vec2f Choose_State::Get_newgamepos(){
	return newgamepos;
}

vec2f Choose_State::Get_settingpos(){
	return settingpos;
}

vec2f Choose_State::Get_escpos(){
	return escpos;
}

vec2f Choose_State::Get_continuepos(){
	return continuepos;
}
vec2f Choose_State::Get_tutorialpos(){
	return tutorialpos;
}
