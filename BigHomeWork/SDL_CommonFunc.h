#ifndef SDL_COMMONFUNC_H_INCLUDED
#define SDL_COMMONFUNC_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 1000;
const int SCREEN_BPP = 32;

SDL_Surface* gScreen = nullptr;
SDL_Surface* gBackground = nullptr;
SDL_Event gEvent;

SDL_Surface* LoadImage(string file);



#endif // SDL_COMMONFUNC_H_INCLUDED
