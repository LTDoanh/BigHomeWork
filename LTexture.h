#pragma once

#include "Project_Base.h"

class LTexture
{
public:
    // Các hàm cơ bản
	LTexture();

	~LTexture();

	void free();

	bool loadFromFile(string path);

	bool loadFromRenderedText(string text, SDL_Color color);

	void render(int x, int y);

	int getWidth();

	int getHeight();

private:
    // Biến lưu texture
	SDL_Texture* p_Texture;

	// Biến lưu kích thước của texture
	int p_Width;
	int p_Height;
};


// LTEXTURE_H_INCLUDED
