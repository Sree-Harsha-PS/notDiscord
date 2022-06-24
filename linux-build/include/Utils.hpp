#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class textBox{}; //a box when focused on(use a bool), you can type any text(from the keyboard) into this box that will constantly update. Parameter provided - x, y, w, h and color/texture
class button{}; //a simple button with options to control text, size, colour/texture. write functions when button is clicked and a function to render it.
class text{}; // a tkinter equivalient of Label(), can control the text, width, height, position(x and y)
