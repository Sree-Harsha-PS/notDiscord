#include "Entity.hpp"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

//member initialization list?

Entity::Entity(float p_x, float p_y, float p_w, float p_h, SDL_Texture* p_tex)
:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_w;
	currentFrame.h = p_h;

	velx=0;
	vely=0;
}

float Entity::getX(){
	return x;
}

float Entity::getY(){
	return y;
}

void Entity::setX(float newx){
	x=newx;
}

void Entity::setY(float newy){
	y=newy;
}

void Entity::setVelX(float new_velx){
	velx=new_velx;
}

void Entity::setVelY(float new_vely){
	vely=new_vely;
}

void Entity::setAnimate(bool isAnimate){
	animate = isAnimate;
}
/*
void Entity::getAnimate(){
	return animate;
}
*/
void Entity::jump(){
	isJump=true;
	jumpaccumulator=0;
	jumpdeltatime = 10;
	jumptime = 350;
	xjump=1;
}

void Entity::executeAllMotions(){
	x+=velx;
	if(!isJump){
		y+=vely;
	}

	if(isJump){
		if(jumpaccumulator<=jumptime){

		if(jumpaccumulator<(jumptime/2)){
			y-=100/(xjump);
			xjump+=1;
		}

		if(jumpaccumulator>=(jumptime/2)){
			y+=100/(xjump-1);
			xjump-=1;
		}

		jumpaccumulator+=jumpdeltatime;
		SDL_Delay(jumpdeltatime);
		}
		else{
			isJump=false;
		}
	}
}

SDL_Texture* Entity::getTex(){
	return tex;
}

SDL_Rect Entity::getCurrentFrame(){
	return currentFrame;
}