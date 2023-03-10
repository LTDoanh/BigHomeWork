#ifndef SDL_UTILS_H_INCLUDED
#define SDL_UTILS_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 1000;
const int SCREEN_BPP = 32;

static SDL_Window* gWindow = nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Surface* gScreen = nullptr;
static SDL_Surface* gBackground = nullptr;
static SDL_Event gEvent;

bool Init();

SDL_Surface* LoadImage(string file);

void ApplySurface(SDL_Surface* src, SDL_Surface* dst, int x, int y);

void Clean();

#endif
