#include "Player.hpp"

Player::Player(vec2f p_pos, SDL_Texture* p_tex, int stand)
:tex(p_tex), pos(p_pos), moving(-1)
{
	update_blockpos();
	currentFrame.w = 32;
	currentFrame.h = 32;
	currentFrame.x = 0;
	currentFrame.y = 0;
	c_frame = 0;
	facing = -1;
	standing = stand;
	stand_itr = 0;
	can_shoot=true;
}
SDL_Texture* Player::gettex()
{
	return tex;
}
// void Player::load_map(int **p_map)
// {
// 	map = p_map;
// }
int Player::get_moving()
{
	return moving;
}
int Player::get_facing()
{
	return facing;
}
void Player::move_trigger(int dir)
{
	if(moving==-1){
		if(((facing+standing+1)%4 == dir) && facing!=-1){
			moving = dir;
			move_itr = 0;
			facing = moving;
		}
		else facing = (dir+3-standing)%4;
	}
	
}
void Player::reduce_hp(float r_hp)
{
	hp-=r_hp;
}
vec2f& Player::get_pos()
{
	return pos;
}
double Player::get_angle()
{
	return angle;
}
SDL_RendererFlip Player::get_flip()
{
	return flip;
}
SDL_Rect Player::getcurrentframe()
{
	return currentFrame;
}
void Player::Alterframe(vec2f i_frame)
{
	currentFrame.x = i_frame.x;
	currentFrame.y = i_frame.y;
}
int Player::get_speed()
{
	return speed;
}
void Player::set_speed(int spd)
{
	speed=spd;
}
bool Player::get_can_shoot()
{
	return can_shoot;
}
void Player::set_can_shoot(bool cann)
{
	can_shoot=cann;
}
int Player::absdir()
{
	if(moving!=-1) return moving;
	if(facing == -1) return (standing+2)%4;
	return (standing+facing+1)%4;
}
void Player::init(float p_spd, float p_hp, float p_atk)
{
	speed = p_spd;
	hp = p_hp;
	atk = p_atk;
	maxhp = p_hp;
	speed_o = p_spd;
}
void Player::reset_speed()
{
	speed = speed_o;
}
void Player::update(int** map)
{
	if(moving == -1)
	{
		switch(facing)
		{
			case -1:
				flip = SDL_FLIP_NONE;
				stand_itr = (stand_itr+1)%20;
				if(stand_itr == 0)
				{
					c_frame++;
					c_frame = c_frame%2;
				}
				break;
			case 0:
				c_frame = 2;
				flip = SDL_FLIP_NONE;
				break;
			case 1:
				c_frame = 3;
				flip = SDL_FLIP_NONE;
				break;
			case 2:
				c_frame = 2;
				flip = SDL_FLIP_HORIZONTAL;
				break;
			case 3:
				c_frame = 4;
				flip = SDL_FLIP_NONE;
				break;
		}
		currentFrame.x = c_frame*32;
		// std::cout<<standing;
		switch(standing)
		{
			case 0:
				angle = 90;
				break;
			case 1:
				angle = 180;
				break;
			case 2:
				angle = 270;
				break;
			case 3:
				angle = 0;
				break;
		}
	}
	if(moving>=0){
		switch(moving)
		{
			case 0:
				if(map[blockpos.x+1][blockpos.y]!=0){
					if(map[blockpos.x+1][blockpos.y]==2||map[blockpos.x+1][blockpos.y]==102){
						map[blockpos.x+1][blockpos.y] = 0;
						break;
					}
					else if(map[blockpos.x+1][blockpos.y]==3||map[blockpos.x+1][blockpos.y]==103)
						map[blockpos.x+1][blockpos.y] -= 1;
					pos.x = blockpos.x*40;
					pos.y = blockpos.y*40;
					standing = 2;
					facing = -1;
					moving = -1;
					update(map);
				}
				break;
			case 1:
				if(map[blockpos.x][blockpos.y+1]!=0){
					if(map[blockpos.x][blockpos.y+1]==2||map[blockpos.x][blockpos.y+1]==102){
						map[blockpos.x][blockpos.y+1] = 0;
						break;
					}
					else if(map[blockpos.x][blockpos.y+1]==3||map[blockpos.x][blockpos.y+1]==103)
						map[blockpos.x][blockpos.y+1] -= 1;
					pos.x = blockpos.x*40;
					pos.y = blockpos.y*40;
					standing = 3;
					facing = -1;
					moving = -1;
					update(map);
				}
				break;
			case 2:
				if(map[blockpos.x][blockpos.y]!=0){
					if(map[blockpos.x][blockpos.y]==2||map[blockpos.x][blockpos.y]==102){
						map[blockpos.x][blockpos.y] = 0;
						break;
					}
					else if(map[blockpos.x][blockpos.y]==3||map[blockpos.x][blockpos.y]==103)
						map[blockpos.x][blockpos.y] -= 1;
					pos.x = blockpos.x*40+40;
					pos.y = blockpos.y*40;
					standing = 0;
					facing = -1;
					moving = -1;
					update(map);
				}
				break;
			case 3:
				if(map[blockpos.x][blockpos.y]!=0){
					if(map[blockpos.x][blockpos.y]==2||map[blockpos.x][blockpos.y]==102){
						map[blockpos.x][blockpos.y] = 0;
						break;
					}
					else if(map[blockpos.x][blockpos.y]==3||map[blockpos.x][blockpos.y]==103)
						map[blockpos.x][blockpos.y] -= 1;
					pos.x = blockpos.x*40;
					pos.y = blockpos.y*40+40;
					standing = 1;
					facing = -1;
					moving = -1;
					update(map);
				}
				break;
		}
		switch(moving)
		{
			case 0:
				pos.x+=speed;
				angle = 0;
				flip = SDL_FLIP_NONE;
				break;
			case 1:
				pos.y+=speed;
				angle = 90;
				flip = SDL_FLIP_NONE;
				break;
			case 2:
				pos.x-=speed;
				angle = 0;
				flip = SDL_FLIP_HORIZONTAL;
				break;
			case 3:
				pos.y-=speed;
				angle = 270;
				flip = SDL_FLIP_NONE;
				break;
		}
		if(move_itr<3){
			c_frame = move_itr+5;
			currentFrame.x = c_frame*32;
			move_itr++;
		}
		else{
			if(move_itr == 3){
				if(c_frame == 8) c_frame = 9;
				else c_frame = 8;
				move_itr = 6;
			}
			else move_itr--;
			currentFrame.x = c_frame*32;
		}
		update_blockpos();	
	}
	midair(map);
}

void Player::update_blockpos()
{
	blockpos.x = pos.x/40;
	blockpos.y = pos.y/40;
}
vec2d Player::get_blockpos()
{
	return blockpos;
}
float Player::get_hp()
{
	return hp/maxhp;
}
bool Player::check_pcollision(Player& p2, int** map)
{
	SDL_Rect col;
	bool crash = false;
	if(this->pos.x<=p2.pos.x+40&&this->pos.x>=p2.pos.x){
		if(this->pos.y+40<=p2.pos.y+40&&this->pos.y+40>=p2.pos.y){
			col.x = this->pos.x;
			col.y = p2.pos.y;
			col.w = p2.pos.x+40-this->pos.x;
			col.h = this->pos.y+40-p2.pos.y;
			crash = true;
		}
		else if(this->pos.y<=p2.pos.y+40&&this->pos.y>=p2.pos.y){
			col.x = this->pos.x;
			col.y = this->pos.y;
			col.w = p2.pos.x+40-this->pos.x;
			col.h = p2.pos.y+40-this->pos.y;
			crash = true;
		}
	}
	else if(p2.pos.x<=this->pos.x+40&&p2.pos.x>=this->pos.x){
		if(p2.pos.y+40<=this->pos.y+40&&p2.pos.y+40>=this->pos.y){
			col.x = p2.pos.x;
			col.y = this->pos.y;
			col.w = this->pos.x+40-p2.pos.x;
			col.h = p2.pos.y+40-this->pos.y;
			crash = true;
		}
		else if(p2.pos.y<=this->pos.y+40&&p2.pos.y>=this->pos.y){
			col.x = p2.pos.x;
			col.y = p2.pos.y;
			col.w = this->pos.x+40-p2.pos.x;
			col.h = this->pos.y+40-p2.pos.y;
			crash = true;
		}
	}
	if(col.w == 0 || col.h == 0) crash = false;
	return crash;
}
bool Player::collision(Player& p2, int** map)
{
	bool crash = check_pcollision(p2, map);
	if(crash){
		double ch1_t, ch2_t;
		if(this->moving>=0&&p2.moving>=0){
			if(this->moving == p2.moving){
				if(this->speed>p2.speed){
					p2.hp-=this->atk*2;
					std::cout<<"BACK CRIT!"<<std::endl;
					this->moving = (this->moving+2)%4;
				}
				else if(this->speed<p2.speed){
					this->hp-=p2.atk*2;
					std::cout<<"BACK CRIT!"<<std::endl;
					p2.moving = (p2.moving+2)%4;
				}
			}
			else if(this->moving%2 == p2.moving%2){
				//std::cout<<this->moving<<" "<<p2.moving<<std::endl;
				this->moving = (this->moving+2)%4;
				p2.moving = (p2.moving+2)%4;
				std::cout<<"HEAD ON!1"<<std::endl;
				this->hp-=p2.atk;
				p2.hp-=this->atk;
			}
			else{
				switch(this->moving)
				{
					case 0:
						ch1_t = (this->pos.x+40-p2.pos.x)/this->speed;
						break;
					case 1:
						ch1_t = (this->pos.y+40-p2.pos.y)/this->speed;
						break;
					case 2:
						ch1_t = (p2.pos.x+40-this->pos.x)/this->speed;
						break;
					case 3:
						ch1_t = (p2.pos.y+40-this->pos.y)/this->speed;
				}
				switch(p2.moving)
				{
					case 0:
						ch2_t = (p2.pos.x+40-this->pos.x)/p2.speed;
						break;
					case 1:
						ch2_t = (p2.pos.y+40-this->pos.y)/p2.speed;
						break;
					case 2:
						ch2_t = (this->pos.x+40-p2.pos.x)/p2.speed;
						break;
					case 3:
						ch2_t = (this->pos.y+40-p2.pos.y)/p2.speed;
						break;
				}
				if(ch1_t < ch2_t){
					std::cout<<"P1 CRIT P2!1"<<std::endl;
					p2.hp-=this->atk*2;
					//std::cout<<this->moving<<std::endl;
					//std::cout<<this->moving<<" "<<p2.moving<<std::endl;
					switch(this->moving)
					{
						case 0:
							p2.pos.x = this->pos.x+40;
							p2.pos.y = this->pos.y;
							break;
						case 1:
							p2.pos.x = this->pos.x;
							p2.pos.y = this->pos.y+40;
							break;
						case 2:
							p2.pos.x = this->pos.x-40;
							p2.pos.y = this->pos.y;
							break;
						case 3:
							p2.pos.x = this->pos.x;
							p2.pos.y = this->pos.y-40;
							break;
					}
					p2.moving = this->moving;
					this->moving = (this->moving+2)%4;
				}
				else if(ch1_t > ch2_t){
					std::cout<<"P2 CRIT P1!1"<<std::endl;
					this->hp-=p2.atk*2;
					//std::cout<<this->moving<<" "<<p2.moving<<std::endl;
					switch(p2.moving)
					{
						case 0:
							this->pos.x = p2.pos.x+40;
							this->pos.y = p2.pos.y;
							break;
						case 1:
							this->pos.x = p2.pos.x;
							this->pos.y = p2.pos.y+40;
							break;
						case 2:
							this->pos.x = p2.pos.x-40;
							this->pos.y = p2.pos.y;
							break;
						case 3:
							this->pos.x = p2.pos.x;
							this->pos.y = p2.pos.y-40;
							break;
					}
					this->moving = p2.moving;
					p2.moving = (p2.moving+2)%4;
				}
				else if(ch1_t == ch2_t){
					std::cout<<"PERFECT CRIT!"<<std::endl;
					p2.hp-=this->atk*2;
					this->hp-=p2.atk*2;
					this->moving = (this->moving+2)%4;
					p2.moving = (p2.moving+2)%4;
				}
			}
		}
		else if(this->moving==-1){
			if(this->facing!=-1 && (this->facing+this->standing+1)%4 == (p2.moving+2)%4){
				std::cout<<"HEAD ON!"<<std::endl;
				this->hp-=p2.atk;
				p2.hp-=this->atk;
				p2.moving = (p2.moving+2)%4;
				switch(p2.moving)
				{
					case 0:
						p2.pos.x = this->pos.x+40;
						break;
					case 1:
						p2.pos.y = this->pos.y+40;
						break;
					case 2:
						p2.pos.x = this->pos.x-40;
						break;
					case 3:
						p2.pos.y = this->pos.y-40;
						break;
				}
				this->moving = (p2.moving+2)%4;
				//std::cout<<p2.moving<<std::endl;
			}
			else{
				std::cout<<"P2 CRIT P1!"<<std::endl;
				this->hp-=p2.atk*2;
				//std::cout<<p2.moving<<std::endl;
				p2.moving = (p2.moving+2)%4;
				switch(p2.moving)
				{
					case 0:
						p2.pos.x = this->pos.x+40;
						break;
					case 1:
						p2.pos.y = this->pos.y+40;
						break;
					case 2:
						p2.pos.x = this->pos.x-40;
						break;
					case 3:
						p2.pos.y = this->pos.y-40;
						break;
				}
				this->moving = (p2.moving+2)%4;
				//std::cout<<p2.moving<<std::endl;
			}
		}
		else if(p2.moving==-1){
			if(p2.facing!=-1 && (p2.facing+p2.standing+1)%4 == (this->moving+2)%4){
				std::cout<<"HEAD ON!"<<std::endl;
				this->hp-=p2.atk;
				p2.hp-=this->atk;
				this->moving = (this->moving+2)%4;
				switch(this->moving)
				{
					case 0:
						this->pos.x = p2.pos.x+40;
						break;
					case 1:
						this->pos.y = p2.pos.y+40;
						break;
					case 2:
						this->pos.x = p2.pos.x-40;
						break;
					case 3:
						this->pos.y = p2.pos.y-40;
						break;
				}
				p2.moving = (this->moving+2)%4;
				//std::cout<<this->moving<<std::endl;
			}
			else{
				std::cout<<"P1 CRIT P2!"<<std::endl;
				p2.hp-=this->atk*2;
				this->moving = (this->moving+2)%4;
				switch(this->moving)
				{
					case 0:
						this->pos.x = p2.pos.x+40;
						break;
					case 1:
						this->pos.y = p2.pos.y+40;
						break;
					case 2:
						this->pos.x = p2.pos.x-40;
						break;
					case 3:
						this->pos.y = p2.pos.y-40;
						break;
				}
				p2.moving = (this->moving+2)%4;
			}
		}
	}
	return crash;
}
// void Player::find_standpoint(int** map)
// {
// 	update_blockpos();
// 	if(map[blockpos.x-1][blockpos.y] == 1) standing = 0;
// 	else if(map[blockpos.x][blockpos.y-1] == 1) standing = 1;
// 	else if(map[blockpos.x+1][blockpos.y] == 1) standing = 2;
// 	else if(map[blockpos.x][blockpos.y+1] == 1) standing = 3;
// 	std::cout<<standing<<std::endl;
// }
bool Player::block_up(int** map, Player& p2, bool blue)
{
	switch(absdir())
	{
		case 0:
			if(map[blockpos.x-1][blockpos.y] == 0){
				pos.x -=40;
				if(check_pcollision(p2, map) == false){
					map[blockpos.x][blockpos.y] = 3;
					if(blue) map[blockpos.x][blockpos.y] += 100;
					update_blockpos();
					std::cout<<"placed success"<<std::endl;
					return true;
				}
				else if(map[blockpos.x-2][blockpos.y] == 0){
					std::cout<<"collll"<<std::endl;
					if(p2.absdir() == 0){
						std::cout<<"Head on!B"<<std::endl;
						this->hp-=p2.atk;
						p2.hp-=this->atk;
						map[blockpos.x][blockpos.y] = 3;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x-2)*40;
						p2.pos.y = blockpos.y*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 2;
						return true;
					}
					else{
						std::cout<<"CRIT!B"<<std::endl;
						p2.hp-=this->atk*2;
						map[blockpos.x][blockpos.y] = 3;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x-2)*40;
						p2.pos.y = blockpos.y*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 2;
						return true;
					}
				}
				else{
					std::cout<<"blockup failed"<<std::endl;
					pos.x+=40;
					return false;
				}
			}
			break;
		case 1:
			if(map[blockpos.x][blockpos.y-1] == 0){
				pos.y-=40;
				if(check_pcollision(p2, map) == false){
					map[blockpos.x][blockpos.y] = 3;
					if(blue) map[blockpos.x][blockpos.y] += 100;
					update_blockpos();
					std::cout<<"placed success"<<std::endl;
					return true;
				}
				else if(map[blockpos.x][blockpos.y-2] == 0){
					if(p2.absdir() == 1){
						std::cout<<"Head on!B"<<std::endl;
						this->hp-=p2.atk;
						p2.hp-=this->atk;
						map[blockpos.x][blockpos.y] = 3;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x)*40;
						p2.pos.y = (blockpos.y-2)*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 3;
						return true;
					}
					else{
						std::cout<<"CRIT!B"<<std::endl;
						p2.hp-=this->atk*2;
						map[blockpos.x][blockpos.y] = 3;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x)*40;
						p2.pos.y = (blockpos.y-2)*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 3;
						return true;
					}
				}
				else{
					std::cout<<"blockup failed"<<std::endl;
					pos.y+=40;
					return false;
				}
			}
			break;
		case 2:
			if(map[blockpos.x+1][blockpos.y] == 0){
				pos.x +=40;
				if(check_pcollision(p2, map) == false){
					map[blockpos.x][blockpos.y] = 3;
					if(blue) map[blockpos.x][blockpos.y] += 100;
					update_blockpos();
					std::cout<<"placed success"<<std::endl;
					return true;
				}
				else if(map[blockpos.x+2][blockpos.y] == 0){
					std::cout<<"collll"<<std::endl;
					if(p2.absdir() == 2){
						std::cout<<"Head on!B"<<std::endl;
						this->hp-=p2.atk;
						p2.hp-=this->atk;
						map[blockpos.x][blockpos.y] = 3;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x+2)*40;
						p2.pos.y = blockpos.y*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 0;
						return true;
					}
					else{
						std::cout<<"CRIT!B"<<std::endl;
						p2.hp-=this->atk*2;
						map[blockpos.x][blockpos.y] = 3;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x+2)*40;
						p2.pos.y = blockpos.y*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 0;
						return true;
					}
				}
				else{
					std::cout<<"blockup failed"<<std::endl;
					pos.x-=40;
					return false;
				}
			}
			break;
		case 3:
			if(map[blockpos.x][blockpos.y+1] == 0){
				pos.y+=40;
				if(check_pcollision(p2, map) == false){
					map[blockpos.x][blockpos.y] = 3;
					if(blue) map[blockpos.x][blockpos.y] += 100;
					update_blockpos();
					std::cout<<"placed success"<<std::endl;
					return true;
				}
				else if(map[blockpos.x][blockpos.y+2] == 0){
					if(p2.absdir() == 3){
						std::cout<<"Head on!B"<<std::endl;
						this->hp-=p2.atk;
						p2.hp-=this->atk;
						map[blockpos.x][blockpos.y] = 3;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x)*40;
						p2.pos.y = (blockpos.y+2)*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 1;
						return true;
					}
					else{
						std::cout<<"CRIT!B"<<std::endl;
						map[blockpos.x][blockpos.y] = 3;
						p2.hp-=this->atk*2;
						if(blue) map[blockpos.x][blockpos.y] += 100;
						p2.pos.x = (blockpos.x)*40;
						p2.pos.y = (blockpos.y+2)*40;
						update_blockpos();
						p2.update_blockpos();
						p2.moving = 1;
						return true;
					}
				}
				else{
					std::cout<<"blockup failed"<<std::endl;
					pos.y-=40;
					return false;
				}
			}
			break;
	}
}

void Player::reset_facing()
{
	facing = -1;
}

void Player::midair(int** map)
{
	if(moving == -1){
		update_blockpos();
		bool air = true;
		if(map[blockpos.x+1][blockpos.y] != 0) air = false;
		if(map[blockpos.x-1][blockpos.y] != 0) air = false;
		if(map[blockpos.x][blockpos.y+1] != 0) air = false;
		if(map[blockpos.x][blockpos.y-1] != 0) air = false;
		if(air == true){
			c_frame = 10;
			currentFrame.x = c_frame*32;
			angle = 0;
			flip = SDL_FLIP_NONE;
		}

	}
}