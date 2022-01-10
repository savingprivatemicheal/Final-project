//
// Created by 錡亭勳 on 2021/12/15.
//

#include "Mapspawn.hpp"
//mapBlock::mapBlock(Entity e0, vec2f from, vec2f to) :e(e0) {}



void Map::init(){
    //this->window=&platform;
    tx=21;
    ty=13;
    land = new int*[tx];
    for(int i=0;i<tx;i++) land[i] = new int [ty];
    srand(time(0));
    initLand();
    spawnMidRec();
    spawnSideRecs();
    finalGrow();

};

void Map::initLand() {
    //arrmap.reserve(315);
    for(int i=0; i<tx; i++){
        
        for(int j=0; j<ty; j++){
            land[i][j]=-1;
            std::cout<<'Q'<<land[i][j]<<' ';
            //SDL_Texture* blockTexture = window->loadTexture("res/gfx/mazeSprite.png");
            //vec2f currentpos = vec2f(static_cast<float>(i*16), static_cast<float>(j*16));
            //Entity mazeBlock(currentpos, blockTexture, 16.0f, 16.0f);
            //arrmap.push_back(mazeBlock);
            //window->render(arrmap[i*21+j]);
            
        }
        std::cout<<std::endl;
    }
    // int k=0;
    // while(k<1000){
    //     for(int i=0; i<21; i++){
    //         for(int j=0; j<15; j++){
    //             window->render(arrmap[i*21+j]);
    //         }
    //     }
    //     k+=1;
    // }
}
void Map::checkspace(){
    right=0;
    left=0;
    for(int i=1; i<(tx-1); i++){
        for(int j=1; j<(ty-1); j++){
            int k=0;
            for(int m=-1; m<=1; m++){
                for(int n=-1; n<=1; n++){
                    if(i+m>=0&&i+m<tx&&j+n>=0&&j+n<ty&&land[i+m][j+n]==-1){
                        k+=1;
                    }
                }
            }
            if(k==0){
                land[i][j]=0;
            }
            if(i<mid_x&&land[i][j]==0){left+=1;}
            if(i>mid_x&&land[i][j]==0){right+=1;}
        }
    }
    for(int i=0; i<ty; i++){
        for(int j=0; j<tx; j++){
            std::cout<<land[j][i];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
void Map::spawnMidRec() {
    //maze size max= 17*15
    mid=157;
    mid_x=((tx+1)/2)-1;//11-1
    std::cout<<"mid_x = "<<mid_x<<std::endl;
    mid_y=((ty+1)/2)-1;//8-1
    std::cout<<"mid_y = "<<mid_y<<std::endl;
    x1=rand()%2+3;//turn right
    std::cout<<"x1 = "<<x1<<std::endl;
    x2=rand()%2+4;//turn left, x1+x2<=12(including walls)
    std::cout<<"x2 = "<<x2<<std::endl;
    y1=rand()%2+2;//turn up
    std::cout<<"y1 = "<<y1<<std::endl;
    y2=rand()%3+1;//turn down, y1+y2<=10(including walls)
    std::cout<<"y2 = "<<y2<<std::endl;
    for(int i=mid_x-x2; i<=mid_x+x1; i++){
        for(int j=mid_y-y2; j<=mid_y+y1; j++){
            if(i==mid_x-x2||i==mid_x+x1||j==mid_y-y2||j==mid_y+y1){
                land[i][j]=1;
            }
            else{land[i][j]=0;}
        }
    }
}
void Map::spawnSideRecs(){
    rmid_x=mid_x+x1;
    rmid_y=mid_y+y2;
    rx1=rand()%(5-x1)+3;//turn right, current x<=19, i don't know why 19
    std::cout<<"rx1 = "<<rx1<<std::endl;
    rx2=rand()%(x1+x2)+2;//turn left, rx2 doesn't exeed midrec(including walls)
    std::cout<<"rx2 = "<<rx2<<std::endl;
    ry1=rand()%(mid_y+y2-2)+2;//turn up
    std::cout<<"ry1 = "<<ry1<<std::endl;
    ry2=rand()%(4-y2)+1;//turn down, currenty<=13(including walls)
    std::cout<<"ry2 = "<<ry2<<std::endl;
    std::cout<<"ri = "<<rmid_x-rx2<<" ~ "<<rmid_x+rx1<<std::endl;
    std::cout<<"rj = "<<rmid_y-ry1<<" ~ "<<rmid_y+ry2<<std::endl;
    for(int i=rmid_x-rx2; i<=rmid_x+rx1; i++){
        for(int j=rmid_y-ry1; j<=rmid_y+ry2; j++){
            if(i==rmid_x-rx2||i==rmid_x+rx1||j==rmid_y-ry1||j==rmid_y+ry2){
                land[i][j]=1;
            }
            else{land[i][j]=0;}
        }
    }
    lmid_x=mid_x-x2+1;//+1 because mid_x-x2 is the outside of the wall
    lmid_y=mid_y-y1+1;
    lx1=rand()%(x1+x2)+1;//turn right, current x<=19
    std::cout<<"lx1 = "<<lx1<<std::endl;
    lx2=rand()%(6-x2)+4;//turn left, rx2 doesn't exeed the whole screen(including walls)
    std::cout<<"lx2 = "<<lx2<<std::endl;
    ly1=rand()%(mid_y-y1-2)+2;//turn up
    std::cout<<"ly1 = "<<ly1<<std::endl;
    ly2=rand()%(11-lmid_y)+1;//turn down, currenty<=11(including walls)
    std::cout<<"ly2 = "<<ly2<<std::endl;
    std::cout<<"li = "<<lmid_x-lx2<<" ~ "<<lmid_x+lx1<<std::endl;
    std::cout<<"lj = "<<lmid_y-ly1<<" ~ "<<lmid_y+ly2<<std::endl;
    for(int i=lmid_x-lx2; i<=lmid_x+lx1; i++){
        for(int j=lmid_y-ly1; j<=lmid_y+ly2; j++){
            if(i==lmid_x-lx2||i==lmid_x+lx1||j==lmid_y-ly1||j==lmid_y+ly2){
                land[i][j]=1;
            }
            else{land[i][j]=0;}
        }
    }
    checkspace();

}
void Map::finalGrow(){
    for(int i=1; i<(tx-1); i++){
        for(int j=1; j<(ty-1); j++){
            //vertical
            if(j<(ty-2)&&land[i][j]==1&&land[i][j+1]==1){
                if((i<mid_x&&(left-right<=10))||(i>mid_x&&(right-left<=10))){
                    int t=rand()%10;
                    if(t==0){
                        for(int m=-1; m<=1; m++){
                            for(int n=-1; n<=1; n++){
                                if(land[i+m][j+n]==-1){land[i+m][j+n]=1;}
                                if(land[i+m][j+1+n]==-1){land[i+m][j+1+n]=1;}
                            }

                        }
                        if(i<mid_x){left+=2;}
                        if(i>mid_x){right+=2;}
                    }
                }
                
            }   //horizontal
            else if(i<(tx-2)&&land[i][j]==1&&land[i+1][j]==1){
                if((i<mid_x&&(left-right<=10))||(i>mid_x&&(right-left<=10))){
                    int t=rand()%10;
                    if(t==0){
                        for(int m=-1; m<=1; m++){
                            for(int n=-1; n<=1; n++){
                                if(land[i+m][j+n]==-1){land[i+m][j+n]=1;}
                                if(land[i+1+m][j+n]==-1){land[i+1+m][j+n]=1;}
                            }
                        }
                        if(i<mid_x){left+=2;}
                        if(i>mid_x){right+=2;}
                    }
                }
                
            }
            else{;}
        }
    }
    checkspace();
    for(int i=(tx-2); i>=1; i--){
        for(int j=(ty-2); j>=1; j--){
            //vertical
            if(j<(ty-2)&&land[i][j]==1&&land[i][j+1]==1){
                if((i<mid_x&&(left-right<=10))||(i>mid_x&&(right-left<=10))){
                   int t=rand()%10;
                    if(t==0){
                        for(int m=-1; m<=1; m++){
                            for(int n=-1; n<=1; n++){
                                if(land[i+m][j+n]==-1){land[i+m][j+n]=1;}
                                if(land[i+m][j+1+n]==-1){land[i+m][j+1+n]=1;}
                                
                            }
                        }
                    } 
                }
                
            }   //horizontal
            else if(i<(tx-2)&&land[i][j]==1&&land[i+1][j]==1){
                if((i<mid_x&&(left-right<=10))||(i>mid_x&&(right-left<=10))){
                   int t=rand()%10;
                    if(t==0){
                        for(int m=-1; m<=1; m++){
                            for(int n=-1; n<=1; n++){
                                if(land[i+m][j+n]==-1){land[i+m][j+n]=1;}
                                if(land[i+1+m][j+n]==-1){land[i+1+m][j+n]=1;}
                                
                            }
                        }
                    } 
                }
                
            }
        }
    }
    checkspace();
}

vec2f Map::setinit1(){
    float i=mid_x;
    std::cout<<"i = "<<i<<std::endl;
    float j=mid_y;
    std::cout<<"j = "<<j<<std::endl;
    for(; land[static_cast<int>(i)-1][static_cast<int>(j)]==0; i--){
        std::cout<<" changing i "<<i<<std::endl;
        ;
    }
    for(; land[static_cast<int>(i)][static_cast<int>(j)-1]==0; j--){
        std::cout<<" changing j "<<j<<std::endl;
        ;
    }
    vec2f temp;
    temp.x=i*40.0;
    temp.y=j*40.0;
    std::cout<<"temp i = "<<temp.x<<std::endl;
    std::cout<<"temp j = "<<temp.y<<std::endl;
    //vec2f pos1=vec2f(i, j);
    return temp;
}

vec2f Map::setinit2(){
    float i=mid_x;
    float j=mid_y;
    for(; land[static_cast<int>(i)+1][static_cast<int>(j)]==0; i++){
        ;
    }
    for(; land[static_cast<int>(i)][static_cast<int>(j)+1]==0; j++){
        ;
    }
    vec2f pos2=vec2f(i*40.0, j*40.0);
    return pos2;
}
