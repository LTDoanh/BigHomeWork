#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Global.h"
#include <iostream>
using namespace std;

class LTexture
{
public:
    // Các hàm cơ bản
	LTexture();

	void free();

	bool loadFromFile(string path);

	bool loadFromRenderedText(string text, SDL_Color color, TTF_Font* font);

	void render(int x, int y);

	int getWidth();

	int getHeight();

private:
    // Biến lưu texture
	SDL_Texture* texture;

	// Biến lưu kích thước của texture
	int width;
	int height;
};

#endif // LTEXTURE_H_INCLUDED
