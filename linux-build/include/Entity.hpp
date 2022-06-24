#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Entity{
public:
	Entity(float p_x, float p_y, float p_w, float p_h, SDL_Texture* p_tex);
	float getX();
	float getY();
	void setX(float newx);
	void setY(float newy);
	void setVelX(float new_velx);
	void setVelY(float new_vely);
	void jump();
	void setAnimate(bool isAnimate);
	void getAnimate();
	void executeAllMotions();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	float x, y;
	float velx, vely;
	float acclx, accly;
	float jumpaccumulator, jumpdeltatime, jumptime, xjump;
	bool isJump;
	bool animate = false;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};

