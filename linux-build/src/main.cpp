#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argv, char* args[]){

	if(SDL_Init(SDL_INIT_VIDEO) > 0){
		std::cout<<"Hey.. SDL_Init HAS FAILED. SDL ERROR: "<<SDL_GetError()<<std::endl;
	}

	if(!IMG_Init(IMG_INIT_PNG)){
		std::cout<<"Hey.. IMG_Init HAS FAILED. SDL ERROR: "<<SDL_GetError()<<std::endl;
	}

	RenderWindow window("GAME v1.0", 1280, 720);
	SDL_Texture* kroclxTex = window.loadTexture("res/gfx/scroll5.png");
	SDL_Texture* rectTex = window.loadTexture("res/gfx/scroll6.png");
	SDL_Texture* rect2Tex = window.loadTexture("res/gfx/rect2.png");
	// SDL_Texture* titleTex = window.loadTexture("res/gfx/title2.png");
	SDL_Texture* logoTex = window.loadTexture("res/gfx/logo1.png");
	SDL_Texture* textbox1Tex = window.loadTexture("res/gfx/rect3.png");
	SDL_Texture* sendTex = window.loadTexture("res/gfx/send.png");
	SDL_Texture* textboxTex = window.loadTexture("res/gfx/send2.png");
	SDL_Texture* lrectTex = window.loadTexture("res/gfx/lrect.png");
	SDL_Texture* menu1Tex = window.loadTexture("res/gfx/menu.png");
	Entity Rbackrect(1250, 6, 30, 650, kroclxTex);
	Entity rect(1256, 250, 18, 100, rectTex);
	Entity rect2(400, 0, 1250, 720, rect2Tex);
	//Entity title(150, 0, 150, 50, titleTex);
	Entity logo(0, 0, 220, 50, logoTex);
	Entity textbox1(405, 658, 1250, 55, textbox1Tex);
	Entity send(1220, 660, 50, 55, sendTex);
	Entity textbox(410, 660, 800, 55, textboxTex);
	Entity lrect(10, 60, 380, 650, lrectTex);
	Entity menu1(12, 600, 373, 50, menu1Tex);
	bool gameRunning = true;
	SDL_Event event;

	while(gameRunning){
		while(SDL_PollEvent(&event)){

			if(event.type == SDL_QUIT){
				gameRunning = false;
			}
		window.clear();
		window.render(rect2);
		window.render(Rbackrect);
		window.render(rect);
		// window.render(title);
		window.render(logo);
		window.render(textbox1);
		window.render(send);
		window.render(textbox);
		window.render(lrect);
		window.render(menu1);
		window.display();
	}
}

	window.cleanUp();
	SDL_Quit();

	return 0;
}