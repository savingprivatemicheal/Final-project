#include "Behead.hpp"

Behead::Behead(vec2f b_pos, SDL_Texture* b_tex, float b_w, float b_h):Entity(b_pos, b_tex,  b_w,  b_h)
{
	n=1;
	m=0;
	hits=false;
	crash=false;
	cd = 800;
	lastingticks=0;
	lasting=500;
	able=false;
}
void Behead::update(){
	if(is_on==true){
		lastingticks+=1;
		//std::cout<<"is_on "<<std::endl;
		vec2f frame;
		frame.x=0.0;
		frame.y=0.0;
		Alterframe(frame);
		vec2f pos=me->get_pos();
		pos.x-=blockpixel;
		pos.y-=blockpixel;
		Alterpos(pos);
		check_hit();
		int x=static_cast<int>(me->get_blockpos().x);
		std::cout<<"my pos x = "<<x<<std::endl;
		int y=static_cast<int>(me->get_blockpos().y);
		std::cout<<"my pos y = "<<y<<std::endl;
		for(int k=-1; k<=1; k++){
			for(int p=-1; p<=1; p++){
				if(x+k>=0&&x+k<21&&y+p>=0&&y+p<=13&&land[x+k][y+p]!=1&&land[x+k][y+p]!=-1){
					land[x+k][y+p]=0;
					//pos.x+=blockpixel*n*1.0;
					//pos.y+=blockpixel*m*1.0;
					//Alterpos(pos);
				}
			}
		}
			
			
		
		// int x=static_cast<int>(me->get_blockpos().x);
		// std::cout<<"my pos x = "<<x<<std::endl;
		// int y=static_cast<int>(me->get_blockpos().y);
		// std::cout<<"my pos y = "<<y<<std::endl;
		// if(n==1&&m==0){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	m=-1;
		// }
		// else if(n==1&&m==-1){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	n=0;
		// }
		// else if(n==0&&m==-1){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	n=-1;
		// }
		// else if(n==-1&&m==-1){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	m=0;
		// }
		// else if(n==-1&&m==0){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	m=1;
		// }
		// else if(n==-1&&m==1){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	n=0;
		// }
		// else if(n==0&&m==1){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	n=1;
		// }
		// else if(n==1&&m==1){
		// 	if(land[x+n][y+m]!=1&&land[x+n][y+m]!=-1){
		// 		land[x+n][y+m]=0;
		// 		pos.x+=blockpixel*n*1.0;
		// 		pos.y+=blockpixel*m*1.0;
		// 		Alterpos(pos);
		// 	}
		// 	m=0;
		// 	is_on=false;
		// 	vec2f initframe;
		// 	initframe.x=0;
		// 	initframe.y=0;
		// 	Alterframe(initframe);
		// }
		// else{;}
		reset();
	}
	if(lastingticks>=lasting){
		is_on=false;
		lastingticks=0;
	}
	ticks+=1;
	if(ticks>=cd){ticks=cd;  able=true;}
	else{able=false;}
}
void Behead::doit(){is_on=true;}
void Behead::reset(){ticks=0; }
void Behead::check_hit(){
	vec2f tppos=oppo->get_pos();
	vec2f bpos=me->get_pos();
	//std::cout<<"p2 "<<tppos.x<<' '<<tppos.y<<std::endl;
	//std::cout<<"this "<<bpos.x<<' '<<bpos.y<<std::endl;
	// if((bpos.x-blockpixel*1)<=(tppos.x+blockpixel)&&(bpos.x-blockpixel*1)>=tppos.x){
	// 	if((bpos.y+blockpixel*2)<=(tppos.y+blockpixel)&&(bpos.y+blockpixel*2)>=tppos.y){
	// 		//std::cout<<"line 69 "<<std::endl;
	// 		col.x = bpos.x-blockpixel*1;
	// 		col.y = tppos.y;
	// 		col.w = tppos.x+blockpixel-(bpos.x-blockpixel*1);
	// 		col.h = bpos.y+blockpixel*2-tppos.y;
	// 		//crash = true;
	// 	}
	// 	else if((bpos.y-blockpixel*1)<=(tppos.y+blockpixel)&&(bpos.y-blockpixel*1)>=tppos.y){
	// 		//std::cout<<"line 77 "<<std::endl;
	// 		col.x = bpos.x-blockpixel*1;
	// 		col.y = bpos.y-blockpixel*1;
	// 		col.w = tppos.x+blockpixel-(bpos.x-blockpixel*1);
	// 		col.h = tppos.y+blockpixel-(bpos.y-blockpixel*1);
	// 		//crash = true;
	// 	}
	// 	else if((bpos.y+blockpixel*2)>=(tppos.y+blockpixel)&&(bpos.y-blockpixel*1)<=tppos.y){
	// 		//std::cout<<"line 77 "<<std::endl;
	// 		col.x = bpos.x-blockpixel*1;
	// 		col.y = tppos.y;
	// 		col.w = tppos.x+blockpixel-bpos.x;
	// 		col.h = blockpixel;
	// 		//crash = true;
	// 	}

	// }
	// else if((tppos.x<=(bpos.x+blockpixel*2))&&(tppos.x>=(bpos.x-blockpixel*1))){
	// 	if((tppos.y+blockpixel)<=(bpos.y+blockpixel*2)&&(tppos.y+blockpixel)>=(bpos.y-blockpixel*1)){
	// 		//std::cout<<"line 87 "<<std::endl;
	// 		col.x = tppos.x;
	// 		col.y = bpos.y-blockpixel*1;
	// 		col.w = bpos.x+blockpixel*2-tppos.x;
	// 		col.h = tppos.y+blockpixel-(bpos.y-blockpixel*1);
	// 		//crash = true;
	// 	}
	// 	else if(tppos.y<=(bpos.y+blockpixel*2)&&tppos.y+blockpixel>=(bpos.y+blockpixel*2)){
	// 		//std::cout<<"line 95 "<<std::endl;
	// 		col.x = tppos.x;
	// 		col.y = tppos.y;
	// 		col.w = bpos.x+blockpixel*2-tppos.x;
	// 		col.h = bpos.y+blockpixel*2-tppos.y;
	// 		//crash = true;
	// 	}
	// 	else if(tppos.y+blockpixel<=(bpos.y+blockpixel*2)&&tppos.y>=(bpos.y-blockpixel*1)){
	// 		//std::cout<<"line 95 "<<std::endl;
	// 		col.x = tppos.x;
	// 		col.y = tppos.y;
	// 		col.w = bpos.x+blockpixel*2-tppos.x;
	// 		col.h = blockpixel;
	// 		//crash = true;
	// 	}
	// }
	// //else if((tppos.x<=(bpos.x+blockpixel*2))&&(tppos.x>=(bpos.x-blockpixel*1))){
	// 	if((tppos.y+blockpixel)<=(bpos.y+blockpixel*2)&&(tppos.y+blockpixel)>=(bpos.y-blockpixel*1)){
	// 		//std::cout<<"line 87 "<<std::endl;
	// 		col.x = tppos.x;
	// 		col.y = bpos.y-blockpixel*1;
	// 		col.w = bpos.x+blockpixel*2-tppos.x;
	// 		col.h = tppos.y+blockpixel-(bpos.y-blockpixel*1);
	// 		//crash = true;
	// 	}
	// 	else if(tppos.y<=(bpos.y+blockpixel*2)&&tppos.y+blockpixel>=(bpos.y+blockpixel*2)){
	// 		//std::cout<<"line 95 "<<std::endl;
	// 		col.x = tppos.x;
	// 		col.y = tppos.y;
	// 		col.w = bpos.x+blockpixel*2-tppos.x;
	// 		col.h = bpos.y+blockpixel*2-tppos.y;
	// 		//crash = true;
	// 	}
	// 	else if(tppos.y+blockpixel<=(bpos.y+blockpixel*2)&&tppos.y>=(bpos.y-blockpixel*1)){
	// 		//std::cout<<"line 95 "<<std::endl;
	// 		col.x = tppos.x;
	// 		col.y = tppos.y;
	// 		col.w = bpos.x+blockpixel*2-tppos.x;
	// 		col.h = blockpixel;
	// 		//crash = true;
	// 	}
	// }
	if(tppos.x>(bpos.x-blockpixel*2)&&tppos.x<(bpos.x+blockpixel*2)&&tppos.y>(bpos.y-blockpixel*2)&&tppos.y<(bpos.y+blockpixel*2)){
		crash=true;
	}
	if(crash==true){
		//if(col.w == 0 || col.h == 0){crash=false; return;}
		//std::cout<<"crasssshhhh!!!!!"<<std::endl;
		oppo->reduce_hp(2.0);
		crash=false;
		//moving=false;
		//disappear(map);
	}
	//;
}