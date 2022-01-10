#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h> 

// //for Mac  
// #include <SDL2/SDL.h>
// #include <SDL_mixer.h>
// #include <SDL_ttf.h> 
// #include <iostream>

using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Mapspawn.hpp"
#include "Shootblock.hpp"
#include "Blockclock.hpp"
#include "Skills.hpp"
#include "Behead.hpp"
#include "Timefreeze.hpp"
#include "ChooseState.hpp"

int main(int argc, char* args[]){

	if(SDL_Init(SDL_INIT_VIDEO)>0){
		cout<<"SDL_Init HAS FAILED. SDL_ERROR: "<<SDL_GetError()<<endl;
	}

	if(!(IMG_Init(IMG_INIT_PNG)))
		cout<<"IMG_Init HAS FAILED. Error: "<<SDL_GetError()<<endl;

	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
		cout<<"Mix_OpenAudio HAS FAILED. Error: "<<SDL_GetError()<<endl;


	RenderWindow window("GAME v1.0", 40*21, 40*16);

	Mix_Music *mMusic = NULL;//menu music
	mMusic = Mix_LoadMUS( "res/sound/space-dojo.wav" );

	Mix_Music *gMusic = NULL;//gamemusic
	gMusic = Mix_LoadMUS( "res/sound/sci-city.wav" );

	Mix_Chunk *cMusic = NULL;//crack music
	cMusic = Mix_LoadWAV("res/sound/crack.wav");

	Mix_Chunk *deadMusic = NULL;//dead music
	deadMusic = Mix_LoadWAV("res/sound/dead-sound.wav");

	Mix_Chunk *skillMusic = NULL;//skill music
	skillMusic = Mix_LoadWAV("res/sound/skillopen.wav");
	//lipopo starts

	SDL_Texture* menubackground = window.loadTexture("res/gfx/meteorback.png");
	
	SDL_Texture* totalbutton = window.loadTexture("res/gfx/buttomsprite.png");
	SDL_Texture* petc = window.loadTexture("res/gfx/press.png");//press space to continue
	SDL_Texture* mtutorial = window.loadTexture("res/gfx/mtutorial.png");
	Entity emtutorial(vec2f(0.0, 0.0), mtutorial, 336.0, 272.0);
	SDL_Texture* purpwin = window.loadTexture("res/gfx/purpwin.png");
	Entity epurpwin(vec2f(80.0, 200.0), purpwin, 1501.0, 196.0);
	SDL_Texture* bluewin = window.loadTexture("res/gfx/bluewin.png");
	Entity ebluewin(vec2f(80.0, 200.0), bluewin, 1501.0, 196.0);
	SDL_Texture* drawin = window.loadTexture("res/gfx/draw.png");
	Entity edrawin(vec2f(180.0, 200.0), drawin, 1501.0, 196.0);
	Entity epetc(vec2f(228.0,400.0), petc, 128.0, 32.0);
	Choose_State beginning(vec2f(0.0,0.0), menubackground, 84.0f, 64.0f,vec2f(0.0,0.0), totalbutton, 64.0f, 32.0f);
	SDL_Texture* grasstexture = window.loadTexture("res/gfx/meteorback.png");
	vec2f currentpos = vec2f(0.0f, 0.0f);
	Entity platform0(currentpos, grasstexture, 336.0f, 272.0f);
	SDL_Texture* timefg = window.loadTexture("res/gfx/timef.png");
	Entity etimefg(vec2f(0.0f, 0.0f), timefg, 16.0f, 16.0f);

	//plays
	SDL_Texture* purptexture = window.loadTexture("res/gfx/animation.png");
	SDL_Texture* bluetexture = window.loadTexture("res/gfx/character2.png");
	SDL_Texture* topic = window.loadTexture("res/gfx/topic.png");
	vec2f topicpos = vec2f(150.0,50.0);
	Entity etopic(topicpos, topic, 256.0f, 128.0f);
	etopic.Alterframe(vec2f(0.0f,109.0f));

	bool bigloop = true;
	bool pstc = true;//press space to continue
	bool mb = false;//menubool
	bool gb = false;//gamebool
	bool rb = false;//resultbool
	bool tb = false;//tutorialbool
	beginning.state=0;
	int restartstate=0;
	Mix_PlayMusic( mMusic, -1 );
	

	while(bigloop){
		if(pstc){
			Mix_PauseMusic();
			Mix_ResumeMusic();
			SDL_Event event0;//press enter to continue
			bool begincontinue=true;
			window.clear();
			while(begincontinue){
				window.render(*beginning.pbackground(), 10);
				window.render(etimefg, 300);
				window.render(epetc, 3);
				window.render(etopic, 2.5);
				window.display();
				beginning.bgupdate();

				while(SDL_PollEvent(&event0)){
					if(event0.type == SDL_QUIT){
						begincontinue = false;
						bigloop=false;
					}
					if(event0.type == SDL_KEYDOWN)
					{
						switch(event0.key.keysym.sym)
						{
							case SDLK_SPACE:
								begincontinue=false;
								pstc=false;
								mb=true;
								break;
						}

					}
				}
			}
		}
		if(mb){
			SDL_Event event1;
			bool menucontinue=true;
			while((menucontinue)&&(bigloop==true)){
				while(SDL_PollEvent(&event1))
				{
					if(event1.type == SDL_QUIT){
						menucontinue = false;
						bigloop=false;
					}
					if(event1.type == SDL_KEYDOWN)
					{
						switch(event1.key.keysym.sym)
						{						
							case SDLK_RIGHT:
								if(beginning.state==0||beginning.state==-1){
									beginning.state+=1;
								}
								break;
							case SDLK_LEFT:
								if(beginning.state==0||beginning.state==1){
									beginning.state-=1;
								}
								break;
							case SDLK_UP:							
								if(beginning.state==0||beginning.state==-1){
									beginning.state+=1;
								}
								break;
							case SDLK_DOWN:
								if(beginning.state==0||beginning.state==1){
									beginning.state-=1;
								}
								break;
							case SDLK_d:
								if(beginning.state==0||beginning.state==-1){
									beginning.state+=1;
								}
								break;						
							case SDLK_a:
								if(beginning.state==0||beginning.state==1){
									beginning.state-=1;
								}
								break;
							case SDLK_w:							
								if(beginning.state==0||beginning.state==-1){
									beginning.state+=1;
								}
								break;
							case SDLK_s:
								if(beginning.state==0||beginning.state==1){
									beginning.state-=1;
								}
								break;
							case SDLK_SPACE:
								menucontinue=false;
								break;
						}
					}
					
				}
				if((beginning.state==0)&&(bigloop==true)){
						//render picture
					window.clear();
					window.render(*beginning.pbackground(), 10);
					beginning.bgupdate();
					beginning.buttonupdate(vec2f( 64.0, 0.0));//newgameon frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_newgamepos());
					window.render(*beginning.ptotalbutton(), 3);
					beginning.buttonupdate(vec2f( 128.0, 0.0));//tutorial frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_tutorialpos());
					window.render(*beginning.ptotalbutton(), 3);
					beginning.buttonupdate(vec2f( 256.0, 0.0));//setting frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_settingpos());
					window.render(*beginning.ptotalbutton(), 3);
					window.display();
				}else if((beginning.state==1)&&(bigloop==true)){
					window.clear();
					window.render(*beginning.pbackground(), 10);
					beginning.bgupdate();
					beginning.buttonupdate(vec2f( 0.0, 0.0));//newgame frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_newgamepos());
					window.render(*beginning.ptotalbutton(), 3);
					beginning.buttonupdate(vec2f( 128.0, 0.0));//tutorial frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_tutorialpos());
					window.render(*beginning.ptotalbutton(), 3);
					beginning.buttonupdate(vec2f( 320.0, 0.0));//settingon frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_settingpos());
					window.render(*beginning.ptotalbutton(), 3);
					window.display();
				}else if((beginning.state==-1)&&(bigloop==true)){
					window.clear();
					window.render(*beginning.pbackground(), 10);
					beginning.bgupdate();
					beginning.buttonupdate(vec2f( 0.0, 0.0));//newgame frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_newgamepos());
					window.render(*beginning.ptotalbutton(), 3);
					beginning.buttonupdate(vec2f( 192.0, 0.0));//tutorialon frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_tutorialpos());
					window.render(*beginning.ptotalbutton(), 3);
					beginning.buttonupdate(vec2f( 256.0, 0.0));//setting frame
					beginning.ptotalbutton()->Alterpos(beginning.Get_settingpos());
					window.render(*beginning.ptotalbutton(), 3);
					window.display();
				}
			}
						

					
			if((beginning.state==0)&&(bigloop==true)){
				window.clear();
				mb=false;
				gb=true;
			}
			if((beginning.state==1)&&(bigloop==true)){
				//setting
				SDL_Event event3;
				int settingstate=0;
				bool settingcontinue=true;
				window.clear();
				window.render(*beginning.pbackground(), 10);
				beginning.buttonupdate(vec2f( 576.0, 0.0));//continueonframe
				beginning.ptotalbutton()->Alterpos(beginning.Get_continuepos());
				window.render(*beginning.ptotalbutton(), 3);
				beginning.buttonupdate(vec2f( 384.0, 0.0));//escframe
				beginning.ptotalbutton()->Alterpos(beginning.Get_escpos());
				window.render(*beginning.ptotalbutton(), 3);
				window.display();
				while((settingcontinue)&&(bigloop==true)){
					while(SDL_PollEvent(&event3)){
						if(event3.type == SDL_QUIT){
							settingcontinue = false;
							bigloop=false;
						}
						if(event3.type == SDL_KEYDOWN)
						{
							switch(event3.key.keysym.sym)
							{
								case SDLK_SPACE:
									settingcontinue=false;
									break;
								case SDLK_w:
									settingstate=0;
									break;
								case SDLK_s:
									settingstate=1;
									break;
								case SDLK_UP:
									settingstate=0;
									break;
								case SDLK_DOWN:
									settingstate=1;
									break;
							}
						}
					}
					if((settingstate==0)&&(bigloop==true)){
						window.clear();
						window.render(*beginning.pbackground(), 10);
						beginning.bgupdate();
						beginning.buttonupdate(vec2f( 576.0, 0.0));//continueonframe
						beginning.ptotalbutton()->Alterpos(beginning.Get_continuepos());
						window.render(*beginning.ptotalbutton(), 3);
						beginning.buttonupdate(vec2f( 384.0, 0.0));//escframe
						beginning.ptotalbutton()->Alterpos(beginning.Get_escpos());
						window.render(*beginning.ptotalbutton(), 3);
						window.display();
					}
					if((settingstate==1)&&(bigloop==true)){
						window.clear();
						window.render(*beginning.pbackground(), 10);
						beginning.bgupdate();
						beginning.buttonupdate(vec2f( 512.0, 0.0));//continueframe
						beginning.ptotalbutton()->Alterpos(beginning.Get_continuepos());
						window.render(*beginning.ptotalbutton(), 3);
						beginning.buttonupdate(vec2f( 448.0, 0.0));//esconframe
						beginning.ptotalbutton()->Alterpos(beginning.Get_escpos());
						window.render(*beginning.ptotalbutton(), 3);
						window.display();
					}
				}	

				if((settingstate==0)&&(bigloop==true)){
					window.clear();
					mb=true;
					gb=false;

				}
				if((settingstate==1)&&(bigloop==true)){
					window.clear();
					mb=false;
					gb=false;
					pstc=true;
				}
			}
			if((beginning.state==-1)&&(bigloop==true)){
				mb=false;
				tb=true;
			}
		}
		if(tb&&(bigloop==true)){
			SDL_Event event4;
			bool tutorialcontinue=true;
			while(tutorialcontinue){
				window.clear();
				window.render(emtutorial, 2.5);
				window.display();
				while(SDL_PollEvent(&event4)){
					if(event4.type == SDL_QUIT){
						tutorialcontinue = false;
						bigloop=false;
					}
					if(event4.type == SDL_KEYDOWN)
					{
						switch(event4.key.keysym.sym)
						{
							case SDLK_SPACE:
								tutorialcontinue=false;
								break;
						}
					}
				}
			}
			beginning.state=0;
			tb=false;
			mb=true;
		}
		if(gb){
			Mix_HaltMusic();
			Mix_PlayMusic( gMusic, -1 );
			Map ground;
			ground.init();
			vec2f ch_pos = ground.setinit1();
			Player purp_ch(ch_pos, purptexture, 1);
			ch_pos = ground.setinit2();
			Player blue_ch(ch_pos, bluetexture, 3);
			// ball.load_map(ground.land);
			purp_ch.init(5, 2000, 120);
			// ball1.load_map(ground.land);
			blue_ch.init(7, 1400, 150);
			
			//most blocks
			int most=5;
			//shootblocks
			SDL_Texture* shoottexturep = window.loadTexture("res/gfx/shootblocksprite0_purple.png");
			vec2f bp;
			bp.x=0.0;
			bp.y=0.0;
			Shootblock block(bp, shoottexturep, 16, 16);
			Shootblock sblock[5]={
				Shootblock(bp, shoottexturep, 16, 16),
				Shootblock(bp, shoottexturep, 16, 16),
				Shootblock(bp, shoottexturep, 16, 16),
				Shootblock(bp, shoottexturep, 16, 16),
				Shootblock(bp, shoottexturep, 16, 16),

			};

			SDL_Texture* shoottextureb = window.loadTexture("res/gfx/shootblocksprite0_blue.png");
			vec2f bbp;
			bbp.x=0.0;
			bbp.y=0.0;
			Shootblock bblock(bbp, shoottextureb, 16, 16);
			Shootblock sbblock[5]={
				Shootblock(bbp, shoottextureb, 16, 16),
				Shootblock(bbp, shoottextureb, 16, 16),
				Shootblock(bbp, shoottextureb, 16, 16),
				Shootblock(bbp, shoottextureb, 16, 16),
				Shootblock(bbp, shoottextureb, 16, 16),

			};

			//blockcounter
			SDL_Texture* counterp = window.loadTexture("res/gfx/blockcountsprite.png");
			vec2f cp;
			cp.x=40.0;
			cp.y=40.0;
			Blockclock pclock(cp, counterp, 16, 16, most);
			
			vec2f cb;
			cb.x=760.0;
			cb.y=40.0;
			Blockclock bclock(cb, counterp, 16, 16, most);

			SDL_Texture* nump = window.loadTexture("res/gfx/digit.png");
			vec2f cnp;
			cnp.x=50.0;
			cnp.y=40.0;
			Entity pdigit(cnp, nump, 8, 16);

			vec2f cnb;
			cnb.x=770.0;
			cnb.y=40.0;
			Entity bdigit(cnb, nump, 8, 16);

			//skills
			const int totalskills=2;
			int pur_skill=0;//purple choose skill number 0 (behead)
			int blue_skill=1;//blue choose skill number 1 (timefreeze)
			SDL_Texture* beheadTex = window.loadTexture("res/gfx/behead.png");
			SDL_Texture* timefTex = window.loadTexture("res/gfx/timef.png");
			if(beheadTex==NULL){std::cout<<"image failed"<<std::endl;}
			Behead behead(currentpos, beheadTex, 16, 16);
			Timefreeze timefreeze(currentpos, timefTex, 16, 16);
			Entity timecover(currentpos, timefTex, 16, 16);
			Skills *skills[totalskills]{&behead, &timefreeze};
			for(int i=0; i<totalskills; i++){
				//skills[i]->setPlayer(purp_ch, blue_ch);
				skills[i]->setLand(ground.land);
			}
			skills[pur_skill]->setPlayer(purp_ch, blue_ch);
			skills[blue_skill]->setPlayer(blue_ch, purp_ch);

			SDL_Texture* bword_tex = window.loadTexture("res/gfx/skillwordblueandwhite-sheet.png");
			Entity bword(vec2f(760.0, 80.0), bword_tex, 16, 7);
			SDL_Texture* pword_tex = window.loadTexture("res/gfx/skillwordpurpleandwhite-sheet.png");
			Entity pword(vec2f(40.0, 80.0), pword_tex, 16, 7);
			
			//skillbar
			SDL_Texture* blue_skill_tex = window.loadTexture("res/gfx/skbarblue.png");
			Entity blue_skillbar(vec2f(520.0, 80.0), blue_skill_tex, 96, 6);
			// SDL_Texture* blue_skillword_tex = window.loadTexture("res/gfx/skillwordblueandwhite.png");
			// Entity blue_skillword(vec2f(760.0, 80.0), blue_skillword_tex, 16, 7);
			SDL_Texture* purple_skill_tex = window.loadTexture("res/gfx/skbarpurple.png");
			Entity purple_skillbar(vec2f(80.0, 80.0), purple_skill_tex, 96, 6);
			purple_skillbar.Alterframe(vec2f(96.0, 0.0));
			// SDL_Texture* purple_skillword_tex = window.loadTexture("res/gfx/skillwordpurpleandwhite.png");
			// Entity purple_skillword(vec2f(40.0, 80.0), purple_skillword_tex, 16, 7);
				
			//wall & map
			SDL_Texture* walltex = window.loadTexture("res/gfx/mapblock.png");
			Entity wall(currentpos, walltex, 16, 16);
			
			//hpbar
			SDL_Texture* blue_hp_tex = window.loadTexture("res/gfx/Blue_hp_bar2.png");
			Entity blue_hp(vec2f(480.0, 40.0), blue_hp_tex, 128, 16);
			SDL_Texture* purple_hp_tex = window.loadTexture("res/gfx/Purp_hp_bar2.png");
			Entity purple_hp(vec2f(40.0, 40.0), purple_hp_tex, 128, 16);
			// SDL_Texture* blue_back_tex = window.loadTexture("res/gfx/blue16.png");
			// SDL_Texture* purple_back_tex = window.loadTexture("res/gfx/purple16.png");
			SDL_Texture* gray_back_tex = window.loadTexture("res/gfx/gray16.png");
			Entity blue_back(cb, gray_back_tex, 16.0, 16.0);
			Entity purple_back(cp, gray_back_tex, 16.0, 16.0);cout<<"worked here"<<endl;

			//skill release bar
			SDL_Texture* p_sr_t = window.loadTexture("res/gfx/puple_skill_release.png");
			Entity p_sr(vec2f(0, 0), p_sr_t, 8, 21);
			SDL_Texture* b_sr_t = window.loadTexture("res/gfx/blue_skill_release.png");
			Entity b_sr(vec2f(0, 0), b_sr_t, 8, 21);

			SDL_Texture* startgametex = window.loadTexture("res/gfx/startgame.png");
			Entity startgame(vec2f(324, 290), startgametex, 64, 16);




			//main
			vec2f tbp;
			vec2f trans_down(0.0f, 120.0f);
			vec2f trans_none(0.0f, 0.0f);
			//main
			bool gamerunning = true;
			bool blue_pressed[4] = {};
			bool purple_pressed[4] = {};
			bool blue_shot = false;
			bool purple_shot = false;
			int blue_skill_itr=-1, purple_skill_itr=-1;
			int shake_itr = -1;
			int start_itr = 0;
			int end_itr = 0;
			int end = 0;
			SDL_Event event;
			const float timeStep = 0.01f;
			float accumulator = 0.0f;
			float currenttime = utils::hireTimeInSeconds();
			//gamerunning start
			while(gamerunning){
				float newtime = utils::hireTimeInSeconds();
				float frametime = newtime - currenttime;
				currenttime = newtime;
				accumulator += frametime;
				//start accumulator
				while(accumulator >= timeStep)
				{
					while(SDL_PollEvent(&event))
					{
						if(event.type == SDL_QUIT){
							gamerunning = false;
							bigloop=false;
						}
						if(start_itr == 240 && end == 0){
							if(event.type == SDL_KEYDOWN)
							{
								switch(event.key.keysym.sym)
								{
									case SDLK_RIGHT:
										if(blue_ch.get_moving() == -1)
											if(blue_pressed[0] == false){
												blue_ch.move_trigger(0);
												blue_pressed[0] = true;
											}
										break;
									case SDLK_DOWN:
										if(blue_ch.get_moving() == -1)
											if(blue_pressed[1] == false){
												blue_ch.move_trigger(1);
												blue_pressed[1] = true;
											}
										break;
									case SDLK_LEFT:
										if(blue_ch.get_moving() == -1)
											if(blue_pressed[2] == false){
												blue_ch.move_trigger(2);
												blue_pressed[2] = true;
											}
										break;
									case SDLK_UP:
										if(blue_ch.get_moving() == -1)
											if(blue_pressed[3] == false){
												blue_ch.move_trigger(3);
												blue_pressed[3] = true;
											}
										break;
									case SDLK_d:
										if(purp_ch.get_moving() == -1)
											if(purple_pressed[0] == false){
												purp_ch.move_trigger(0);
												purple_pressed[0] = true;
											}
										break;
									case SDLK_s:
										if(purp_ch.get_moving() == -1)
											if(purple_pressed[1] == false){
												purp_ch.move_trigger(1);
												purple_pressed[1] = true;
											}
										break;
									case SDLK_a:
										if(purp_ch.get_moving() == -1)
											if(purple_pressed[2] == false){
												purp_ch.move_trigger(2);
												purple_pressed[2] = true;
											}
										break;
									case SDLK_w:
										if(purp_ch.get_moving() == -1)
											if(purple_pressed[3] == false){
												purp_ch.move_trigger(3);
												purple_pressed[3] = true;
											}
										break;
									case SDLK_q:
										if(purple_skill_itr == -1) purple_skill_itr = 0;
										cout<<"qdown: "<<purple_skill_itr<<endl;
										break;
									// case SDLK_r:
									// 	{	
									// 		if(skills[blue_skill]->getAble()){
									// 			//std::cout<<"main able"<<std::endl;
									// 			skills[blue_skill]->doit();
									// 		}
									// 		if(skills[pur_skill]->getAble()){
									// 			//std::cout<<"main able"<<std::endl;
									// 			skills[pur_skill]->doit();
									// 		}
									// 		//timefreeze.doit();

									// 		break;
									// 	}
									// // 	Map temp;
									// // 	temp.init();
									// // 	ground = temp;
									// // 	purp_ch.update(ground.land);
									// // 	ball1.update(ground.land);
									// // 	accumulator -= timeStep;
									// 	break;
									case SDLK_l:
										if(blue_skill_itr == -1) blue_skill_itr = 0;
										cout<<"qdown: "<<blue_skill_itr<<endl;
										break;
									case SDLK_o:
									{for(int j=0;j<15;j++){
										for(int i=0;i<21;i++){
											cout<<ground.land[i][j]<<' ';
										}
										cout<<endl;
									}
									break;}
								}
							}
							if(event.type == SDL_KEYUP)
							{
								switch(event.key.keysym.sym)
								{
									case SDLK_q:
										if(purple_skill_itr<120){
											int wts=pclock.get_now()-1;
											if(wts>=0&&purp_ch.get_can_shoot()){
												tbp = purp_ch.get_pos();
												if(purp_ch.get_facing() != -1 && sblock[wts].able(purp_ch.absdir(), tbp, ground.land)){
													sblock[wts].spawn(tbp);
													sblock[wts].shoot(purp_ch.absdir(), ground.land);
													cout<<"wts = "<<wts<<endl;
													pclock.minus();
													if(purp_ch.get_moving() == -1) purple_shot = true;
												}
												else if(sblock[wts].able(purp_ch.absdir(), tbp, ground.land) == false && purp_ch.get_moving() == -1 && (purp_ch.get_facing() == -1 || purp_ch.get_facing() == 1)){
													if(purp_ch.block_up(ground.land, blue_ch, false)){
														pclock.minus();
														if(purp_ch.get_facing() != -1) purple_shot = true;
													}
												}
											}
										}
										else{
											if(skills[pur_skill]->getAble()){
												//std::cout<<"main able"<<std::endl;
												Mix_Volume(-1,30);
												Mix_PlayChannel(-1, skillMusic, 0);
												skills[pur_skill]->doit();
											}
										}
										purple_skill_itr = -1;
										break;
									case SDLK_l:
										if(blue_skill_itr<120){
											int bts=bclock.get_now()-1;
											if(bts>=0&&blue_ch.get_can_shoot()){
												tbp = blue_ch.get_pos();
												if(sbblock[bts].able(blue_ch.absdir(), tbp, ground.land)){
													sbblock[bts].spawn(tbp);
													sbblock[bts].shoot(blue_ch.absdir(), ground.land);
													cout<<"bts = "<<bts<<endl;
													bclock.minus();
													if(blue_ch.get_moving() == -1) blue_shot = true;
												}
												else if(sbblock[bts].able(blue_ch.absdir(), tbp, ground.land) == false && blue_ch.get_moving() == -1 && (blue_ch.get_facing() == -1 || blue_ch.get_facing() == 1)){
													if(blue_ch.block_up(ground.land, purp_ch, true)){
														bclock.minus();
														if(blue_ch.get_facing()!=-1) blue_shot = true;
													}
												}
											}
										}
										else{
											if(skills[blue_skill]->getAble()){
												//std::cout<<"main able"<<std::endl;
												Mix_Volume(-1,30);
												Mix_PlayChannel(-1, skillMusic, 0);
												skills[blue_skill]->doit();

											}
										}
										blue_skill_itr = -1;
										break;
									case SDLK_RIGHT:
										if(blue_pressed[0] == true)
											if(blue_shot == false) blue_ch.move_trigger(0);
										if(blue_shot == true) blue_ch.reset_facing();
										blue_pressed[0] = false;
										blue_shot = false;
										break;
									case SDLK_DOWN:
										if(blue_pressed[1] == true)
											if(blue_shot == false) blue_ch.move_trigger(1);
										if(blue_shot == true) blue_ch.reset_facing();
										blue_pressed[1] = false;
										blue_shot = false;
										break;
									case SDLK_LEFT:
										if(blue_pressed[2] == true)
											if(blue_shot == false) blue_ch.move_trigger(2);
										if(blue_shot == true) blue_ch.reset_facing();
										blue_pressed[2] = false;
										blue_shot = false;
										break;
									case SDLK_UP:
										if(blue_pressed[3] == true)
											if(blue_shot == false) blue_ch.move_trigger(3);
										if(blue_shot == true) blue_ch.reset_facing();
										blue_pressed[3] = false;
										blue_shot = false;
										break;
									case SDLK_d:
										if(purple_pressed[0] == true)
											if(purple_shot == false) purp_ch.move_trigger(0);
										if(purple_shot == true) purp_ch.reset_facing();
										purple_pressed[0] = false;
										purple_shot = false;
										break;
									case SDLK_s:
										if(purple_pressed[1] == true)
											if(purple_shot == false) purp_ch.move_trigger(1);
										if(purple_shot == true) purp_ch.reset_facing();
										purple_pressed[1] = false;
										purple_shot = false;
										break;
									case SDLK_a:
										if(purple_pressed[2] == true)
											if(purple_shot == false) purp_ch.move_trigger(2);
										if(purple_shot == true) purp_ch.reset_facing();
										purple_pressed[2] = false;
										purple_shot = false;
										break;
									case SDLK_w:
										if(purple_pressed[3] == true)
											if(purple_shot == false) purp_ch.move_trigger(3);
										if(purple_shot == true) purp_ch.reset_facing();
										purple_pressed[3] = false;
										purple_shot = false;
										break;
								}
							}
						}
					}
					if(start_itr!=240) start_itr++;
					if(end!=0) end_itr++;
					if(purple_skill_itr!=-1) purple_skill_itr++;
					if(blue_skill_itr!=-1) blue_skill_itr++;
					if(shake_itr!=-1) shake_itr++;
					if(shake_itr == -1) trans_down = vec2f(0, 120);
					if(shake_itr == 20) shake_itr = -1;
					if(shake_itr == 0) trans_down = trans_down+vec2f(0, 3);
					if(shake_itr == 1) trans_down = trans_down+vec2f(-3, 0);
					if(shake_itr == 2) trans_down = trans_down+vec2f(0, -3);
					if(shake_itr == 3) trans_down = trans_down+vec2f(0, -3);
					if(shake_itr == 4) trans_down = trans_down+vec2f(3, 0);
					if(shake_itr == 5) trans_down = trans_down+vec2f(3, 0);
					if(shake_itr == 6) trans_down = trans_down+vec2f(0, 3);
					if(shake_itr == 7) trans_down = trans_down+vec2f(0, 3);
					if(shake_itr == 8) trans_down = trans_down+vec2f(-3, 0);
					if(shake_itr == 9) trans_down = trans_down+vec2f(0, -3);
					if(shake_itr == 10) trans_down = trans_down+vec2f(0, 2);
					if(shake_itr == 11) trans_down = trans_down+vec2f(-2, 0);
					if(shake_itr == 12) trans_down = trans_down+vec2f(0, -2);
					if(shake_itr == 13) trans_down = trans_down+vec2f(0, -2);
					if(shake_itr == 14) trans_down = trans_down+vec2f(2, 0);
					if(shake_itr == 15) trans_down = trans_down+vec2f(2, 0);
					if(shake_itr == 16) trans_down = trans_down+vec2f(0, 2);
					if(shake_itr == 17) trans_down = trans_down+vec2f(0, 2);
					if(shake_itr == 18) trans_down = trans_down+vec2f(-2, 0);
					if(shake_itr == 19) trans_down = trans_down+vec2f(0, -2);
					trans_none = trans_down+vec2f(0, -120);
					//update entities & players
					accumulator -= timeStep;
					if(end == 0 || end == 2) purp_ch.update(ground.land);
					if(end == 0 || end == 3) blue_ch.update(ground.land);
						// blue_ch.midair(ground.land);
						// purp_ch.midair(ground.land);
					if(end == 0){
						if(purp_ch.collision(blue_ch, ground.land)){
							shake_itr = 0;
							Mix_Volume(-1, 30);
							Mix_PlayChannel(-1, cMusic, 0);
						}
					}

					for(int i=0; i<5; i++){
						sblock[i].update(blue_ch, ground.land, 1);
						sbblock[i].update(purp_ch, ground.land, 2);
					}
					for(int i=0; i<totalskills; i++){
						//std::cout<<" totsk i = "<<i<<std::endl;
						skills[i]->update();
					}
					pclock.update();
					vec2f pdigitf;
					pdigitf.x=pclock.get_now()*8.0;
					pdigitf.y=0;
					pdigit.Alterframe(pdigitf);

					bclock.update();
					vec2f bdigitf;
					bdigitf.x=bclock.get_now()*8.0;
					bdigitf.y=0;
					bdigit.Alterframe(bdigitf);

					startgame.Alterframe(vec2f(int(start_itr/60)*64, 0));
					if(end == 1){
						purp_ch.Alterframe(vec2f(int(end_itr/15)*32+11*32, 0));
						blue_ch.Alterframe(vec2f(int(end_itr/15)*32+11*32, 0));
					}
					else if(end == 2){
						blue_ch.Alterframe(vec2f(int(end_itr/15)*32+11*32, 0));
					}
					else if(end == 3){
						purp_ch.Alterframe(vec2f(int(end_itr/15)*32+11*32, 0));
					}
				}
				//end accumulator
				//const float alpha = accumulator/timeStep;
				window.clear();
				window.render(platform0, 3, trans_none);
				for(int i=0;i<21;i++){
					for(int j=0;j<15;j++){
						vec2f temp(i*16*2.5, j*16*2.5);
						if(ground.land[i][j]==1){
							wall.Alterpos(temp);
							window.render(wall, 2.5, trans_down);
						}
						if(ground.land[i][j]==3){
							vec2f cframe = vec2f(16.0f, 0.0f);
							block.Alterframe(cframe);
							block.Alterpos(temp);
							//block.spawn(temp);
							window.render(block, 2.5, trans_down);
						}
						if(ground.land[i][j]==2){
							vec2f cframe = vec2f(32.0f, 0.0f);
							vec2f initframe = vec2f(0.0f, 0.0f);
							block.Alterpos(temp);
							block.Alterframe(cframe);
							window.render(block, 2.5, trans_down);
							block.Alterframe(initframe);
						}
						if(ground.land[i][j]==103){
							vec2f cframe = vec2f(16.0f, 0.0f);
							bblock.Alterframe(cframe);
							bblock.Alterpos(temp);
							//block.spawn(temp);
							window.render(bblock, 2.5, trans_down);
						}
						if(ground.land[i][j]==102){
							vec2f cframe = vec2f(32.0f, 0.0f);
							vec2f initframe = vec2f(0.0f, 0.0f);
							bblock.Alterpos(temp);
							bblock.Alterframe(cframe);
							window.render(bblock, 2.5, trans_down);
							bblock.Alterframe(initframe);
						}
					}
				}	
				if(behead.getIS_ON()){window.render(behead, 7.5, trans_down);}
				if(timefreeze.getIS_ON()){window.render(timefreeze, 55, trans_down);}	
				window.render(blue_back, 2.5);
				window.render(purple_back, 2.5);
				window.renderplayer(purp_ch, 1.25, trans_down);
				window.renderplayer(blue_ch, 1.25, trans_down);
				if(timefreeze.getIS_ON()){timecover.Alterpos(timefreeze.getoppo()->get_pos());window.render(timecover, 2.5, trans_down); }
				for(int i=0; i<5; i++){
					window.render(sblock[i], 2.5, trans_down);
					window.render(sbblock[i], 2.5, trans_down);
				}
				window.render(pclock, 2.5);
				window.render(bclock, 2.5);
				window.render(pdigit, 2.5);
				window.render(bdigit, 2.5);
				window.render(bword, 2.5);
				window.render(pword, 2.5);
				window.render(blue_skillbar, 2.5);
				window.render(purple_skillbar, 2.5);
				
				//skill bar
				// std::cout<<" skillbar "<<((skills[blue_skill]->getnowticks()/skills[blue_skill]->getCD())*96.0)<<std::endl;
				if(skills[blue_skill]->getAble()){
					blue_skillbar.Alterframe(vec2f(96.0, 6.0));
					bword.Alterframe(vec2f(16, 0));
				}
				else{
					blue_skillbar.Alterframe(vec2f((int((skills[blue_skill]->getnowticks()/skills[blue_skill]->getCD())*96.0)), 0.0));
					bword.Alterframe(vec2f(0, 0));
				}
				if(skills[pur_skill]->getAble()){
					purple_skillbar.Alterframe(vec2f(0.0, 6.0));
					pword.Alterframe(vec2f(16, 0));
				}
				else{
					purple_skillbar.Alterframe(vec2f((96.0-int((skills[pur_skill]->getnowticks()/skills[pur_skill]->getCD())*96.0)), 0.0));
					pword.Alterframe(vec2f(0, 0));
				}



				//hp bar
				if(blue_ch.get_hp()>=0) blue_hp.Alterframe(vec2f(int((1-blue_ch.get_hp())*28.0)*128, 0.0));
				else blue_hp.Alterframe(vec2f(28*128, 0));
				if(purp_ch.get_hp()>=0) purple_hp.Alterframe(vec2f(int((1-purp_ch.get_hp())*28.0)*128, 0.0));
				else purple_hp.Alterframe(vec2f(28*128, 0));
				window.renderex(blue_hp, 2.5, vec2f(0, 0), SDL_FLIP_HORIZONTAL, 0);
				window.render(purple_hp, 2.5);

				//skill release render
				if(purple_skill_itr!=-1){
					int temp; //= max(int(purple_skill_itr/24), 5);
					if(int(purple_skill_itr/24)<5){temp = int(purple_skill_itr/24);}
					else{temp=5;}
					p_sr.Alterframe(vec2f(temp*8, 0));
					p_sr.Alterpos(vec2f(purp_ch.get_pos().x+40, purp_ch.get_pos().y+10));
					window.render(p_sr, 1.25, trans_down);
				}
				if(blue_skill_itr!=-1){
					int temp; //= max(int(blue_skill_itr/24), 5);
					if(int(blue_skill_itr/24)<5){temp = int(blue_skill_itr/24);}
					else{temp=5;}
					b_sr.Alterframe(vec2f(temp*8, 0));
					b_sr.Alterpos(vec2f(blue_ch.get_pos().x+40, blue_ch.get_pos().y+10));
					window.render(b_sr, 1.25, trans_down);
				}
				if(end == 0){
					if(blue_ch.get_hp()<=0 && purp_ch.get_hp()<=0){
						end = 1;
						cout<<"draw"<<endl;
						Mix_Volume(-1, 30);
						Mix_PlayChannel(-1, deadMusic, 0);
						// restartstate=0;
						// gamerunning = false;
						// gb=false;
						// rb=true;
					}
					else if(blue_ch.get_hp()<=0){
						end = 2;
						cout<<"purple wins"<<endl;
						Mix_Volume(-1, 30);
						Mix_PlayChannel(-1, deadMusic, 0);
						// restartstate=1;
						// gamerunning = false;
						// gb=false;
						// rb=true;
					}
					else if(purp_ch.get_hp()<=0){
						end = 3;
						cout<<"blue wins"<<endl;
						Mix_Volume(-1, 30);
						Mix_PlayChannel(-1, deadMusic, 0);
						// restartstate=2;
						// gamerunning = false;
						// gb=false;
						// rb=true;
					}
				}
				//start game
				if(start_itr<240) window.render(startgame, 3);

				if(end_itr == 120){
					switch(end)
					{
						case 1:
							restartstate=0;
							gamerunning = false;
							gb=false;
							rb=true;
							break;
						case 2:
							restartstate=1;
							gamerunning = false;
							gb=false;
							rb=true;
							break;
						case 3:
							restartstate=2;
							gamerunning = false;
							gb=false;
							rb=true;
							break;
					}
				}
				window.display();
			}
			//gamerunning end
		}
		if(rb){
			bool restartcontinue=true;
			while(restartcontinue){
				if(restartstate==0){
					window.clear();
					window.render(platform0, 5);
					window.render(edrawin, 0.45);
					window.render(epetc, 3);
					window.display();
					SDL_Event event5;//press space to restart
					while(SDL_PollEvent(&event5)){
						if(event5.type == SDL_QUIT){
							restartcontinue=false;
							bigloop=false;
						}
						if(event5.type == SDL_KEYDOWN)
						{
							switch(event5.key.keysym.sym)
							{
								case SDLK_SPACE:
									restartcontinue=false;
									mb=true;
									rb=false;
									break;
							}

						}
					}
				}
				if(restartstate==1){
					window.clear();
					window.render(platform0, 5);
					window.render(epurpwin, 0.45);
					window.render(epetc, 3);
					window.display();
					SDL_Event event5;//press space to restart
					while(SDL_PollEvent(&event5)){
						if(event5.type == SDL_QUIT){
							restartcontinue=false;
							bigloop=false;
						}
						if(event5.type == SDL_KEYDOWN)
						{
							switch(event5.key.keysym.sym)
							{
								case SDLK_SPACE:
									restartcontinue=false;
									mb=true;
									rb=false;
									break;
							}

						}
					}
				}
				if(restartstate==2){
					window.clear();
					window.render(platform0, 5);
					window.render(ebluewin, 0.45);
					window.render(epetc, 3);
					window.display();
					SDL_Event event5;//press space to restart
					while(SDL_PollEvent(&event5)){
						if(event5.type == SDL_QUIT){
							restartcontinue=false;
							bigloop=false;
						}
						if(event5.type == SDL_KEYDOWN)
						{
							switch(event5.key.keysym.sym)
							{
								case SDLK_SPACE:
									restartcontinue=false;
									mb=true;
									rb=false;
									break;
							}

						}
					}
				}




			}

			Mix_HaltMusic();
			Mix_PlayMusic(mMusic, -1);

		}

	}
	window.cleanup();
	SDL_Quit();

	return 0;
}