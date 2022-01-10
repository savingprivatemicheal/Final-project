#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if(window == NULL){
		std::cout<<"Window failed to init. Error: "<<SDL_GetError()<<std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// SDL_RenderClear(renderer);
	// SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::loadTexture(const char*p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if(texture==NULL)
		std::cout<<"Failed to load texture. Error: "<<SDL_GetError()<<std::endl;
	return texture;
}

void RenderWindow::cleanup()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, float ratio, vec2f trans)
{
	SDL_Rect src;
	src.x=p_entity.getcurrentframe().x;
	src.y=p_entity.getcurrentframe().y;
	src.w=p_entity.getcurrentframe().w;
	src.h=p_entity.getcurrentframe().h;

	SDL_Rect dst;
	dst.x=p_entity.getpos().x+trans.x;
	dst.y=p_entity.getpos().y+trans.y;
	dst.w=p_entity.getcurrentframe().w*ratio;
	dst.h=p_entity.getcurrentframe().h*ratio;

	SDL_RenderCopy(renderer, p_entity.gettex(), &src, &dst);
}
void RenderWindow::renderex(Entity& p_entity, float ratio, vec2f trans, SDL_RendererFlip flip, double theta)
{
	SDL_Rect src;
	src.x=p_entity.getcurrentframe().x;
	src.y=p_entity.getcurrentframe().y;
	src.w=p_entity.getcurrentframe().w;
	src.h=p_entity.getcurrentframe().h;

	SDL_Rect dst;
	dst.x=p_entity.getpos().x+trans.x;
	dst.y=p_entity.getpos().y+trans.y;
	dst.w=p_entity.getcurrentframe().w*ratio;
	dst.h=p_entity.getcurrentframe().h*ratio;

	SDL_RenderCopyEx(renderer, p_entity.gettex(), &src, &dst, theta, NULL, flip);
}
void RenderWindow::renderplayer(Player& p_player, float ratio, vec2f trans)
{
	SDL_Rect src;
	src.x=p_player.getcurrentframe().x;
	src.y=p_player.getcurrentframe().y;
	src.w=p_player.getcurrentframe().w;
	src.h=p_player.getcurrentframe().h;

	SDL_Rect dst;
	dst.x=p_player.get_pos().x+trans.x;
	dst.y=p_player.get_pos().y+trans.y;
	dst.w=p_player.getcurrentframe().w*ratio;
	dst.h=p_player.getcurrentframe().h*ratio;

	const double theta = p_player.get_angle();

	SDL_RenderCopyEx(renderer, p_player.gettex(), &src, &dst, theta, NULL, p_player.get_flip());
}
void RenderWindow::display(){
	SDL_RenderPresent(renderer);
}