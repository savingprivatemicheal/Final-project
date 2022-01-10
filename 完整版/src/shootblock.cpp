#include "Shootblock.hpp"
//Shootblock::Shootblock():Entity(){}
Shootblock::Shootblock(vec2f b_pos, SDL_Texture* b_tex, float b_w, float b_h):Entity(b_pos, b_tex, b_w, b_h)
{
	blockpixel=40;
	state=0;
	speed=30;
	pos=b_pos;
	crash=false;
	//appear=true;
	moving=false;
	moved=false;
	direction=-1;
	cframe.x=0;
	cframe.y=0;
}
bool Shootblock::able(int dir, vec2f b_pos, int**map){
		vec2f tpos=b_pos;
		if(dir==3){
			
			if(map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)-1]>0){
				return false;
			}
			else{return true;}

		}
		if(dir==0){
			if(map[static_cast<int>(tpos.x/blockpixel)+1][static_cast<int>(tpos.y/blockpixel)]>0){
				return false;
			}
			else{return true;}
		}
		if(dir==1){
			if(map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)+1]>0){
				return false;
			}
			else{return true;}
		}
		if(dir==2){
			if(map[static_cast<int>(tpos.x/blockpixel)-1][static_cast<int>(tpos.y/blockpixel)]>0){
				return false;
			}
			else{return true;}
		}
}
void Shootblock::spawn(vec2f b_pos){
	Alterpos(b_pos);
	//std::cout<<"pos "<<b_pos.x<<' '<<b_pos.y<<std::endl;
	vec2f tF;
	tF.x=16;
	tF.y=0;
	Alterframe(tF);
}
void Shootblock::shoot(int direction, int**map){
	//up=3, right=0, down=1, left=2 (definite)
	this->direction=direction;
	moving=true;
}
void Shootblock::check_collision(Player& p2, int** map){
	SDL_Rect col;
	vec2f tppos=p2.get_pos();
	vec2f bpos=this->getpos();
	//std::cout<<"p2 "<<tppos.x<<' '<<tppos.y<<std::endl;
	//std::cout<<"this "<<bpos.x<<' '<<bpos.y<<std::endl;
	if(bpos.x<=tppos.x+blockpixel&&bpos.x>=tppos.x){
		if(bpos.y+blockpixel<=tppos.y+blockpixel&&bpos.y+blockpixel>=tppos.y){
			//std::cout<<"line 69 "<<std::endl;
			col.x = bpos.x;
			col.y = tppos.y;
			col.w = tppos.x+blockpixel-bpos.x;
			col.h = bpos.y+blockpixel-tppos.y;
			crash = true;
		}
		else if(bpos.y<=tppos.y+blockpixel&&bpos.y>=tppos.y){
			//std::cout<<"line 77 "<<std::endl;
			col.x = bpos.x;
			col.y = bpos.y;
			col.w = tppos.x+blockpixel-bpos.x;
			col.h = tppos.y+blockpixel-bpos.y;
			crash = true;
		}
	}
	else if((tppos.x<=(bpos.x+blockpixel))&&(tppos.x>=bpos.x)){
		if(tppos.y+blockpixel<=bpos.y+blockpixel&&tppos.y+blockpixel>=bpos.y){
			//std::cout<<"line 87 "<<std::endl;
			col.x = tppos.x;
			col.y = bpos.y;
			col.w = bpos.x+blockpixel-tppos.x;
			col.h = tppos.y+blockpixel-bpos.y;
			crash = true;
		}
		else if(tppos.y<=bpos.y+blockpixel&&tppos.y>=bpos.y){
			//std::cout<<"line 95 "<<std::endl;
			col.x = tppos.x;
			col.y = tppos.y;
			col.w = bpos.x+blockpixel-tppos.x;
			col.h = bpos.y+blockpixel-tppos.y;
			crash = true;
		}
	}
	if(crash==true){
		if(col.w == 0 || col.h == 0){crash=false; return;}
		//std::cout<<"crasssshhhh!!!!!"<<std::endl;
		p2.reduce_hp(100.0);
		moving=false;
		disappear(map);
	}
}
// void Shootblock::crack(int** map){
// 	cframe.x+=16;
// 	cframe.x=static_cast<float>(static_cast<int>(cframe.x)%16);
// 	if(cframe.x==0){
// 		disappear(map);
// 	}
// 	else{
// 		Alterframe(cframe);
// 		vec2f tpos=getpos();
// 		map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)]=2;
// 	}

// }
void Shootblock::disappear(int **map){
	//map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)]=0;
	vec2f t;
	t.x=0.0;
	t.y=0.0;
	pos=t;
	Alterframe(t);
	Alterpos(t);
	moved=false;
	moving=false;
	direction =-1;
	crash=false;
}
void Shootblock::update(Player& p2, int **map, int iam){
	if(moving==true){
		int give;
		if(iam==1){give=3;}
		if(iam==2){give=103;}
		if(direction==3){
			vec2f tpos=getpos();
			if(map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)-1]==0){
				
				tpos.y-=speed;
				Alterpos(tpos);
				check_collision(p2, map);
			}
			else if(map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)-1]>0){
				tpos.y=(static_cast<int>(tpos.y/blockpixel))*blockpixel;
				Alterpos(tpos);

				map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)]=give;
				moved=true;
				moving =false;
				disappear(map);
			}
			else{;}
		}
		if(direction==0){
			vec2f tpos=getpos();
			if(map[static_cast<int>(tpos.x/blockpixel)+1][static_cast<int>(tpos.y/blockpixel)]==0){
				tpos.x+=speed;
				Alterpos(tpos);
				check_collision(p2, map);
			}
			else if(map[static_cast<int>(tpos.x/blockpixel)+1][static_cast<int>(tpos.y/blockpixel)]>0){
				tpos.x=(static_cast<int>(tpos.x/blockpixel))*blockpixel;
				Alterpos(tpos);
				map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)]=give;
				moved=true;
				moving =false;
				disappear(map);
			}
			else{;}
		}
		if(direction==1){
			vec2f tpos=getpos();
			if(map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)+1]==0){
				tpos.y+=speed;
				Alterpos(tpos);
				check_collision(p2, map);
			}
			else if(map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)+1]>0){
				tpos.y=(static_cast<int>(tpos.y/blockpixel))*blockpixel;
				Alterpos(tpos);
				map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)]=give;
				moved=true;
				moving =false;
				disappear(map);
			}
			else{;}
		}
		if(direction==2){
			vec2f tpos=getpos();
			if(map[static_cast<int>(tpos.x/blockpixel)-1][static_cast<int>(tpos.y/blockpixel)]==0){
				tpos.x-=speed;
				Alterpos(tpos);
				check_collision(p2, map);
			}
			else if(map[static_cast<int>(tpos.x/blockpixel)-1][static_cast<int>(tpos.y/blockpixel)]>0){
				tpos.x=(static_cast<int>(tpos.x/blockpixel))*blockpixel;
				Alterpos(tpos);
				map[static_cast<int>(tpos.x/blockpixel)][static_cast<int>(tpos.y/blockpixel)]=give;
				moved=true;
				moving =false;
				disappear(map);
			}
			else{;}
		}
	}
}