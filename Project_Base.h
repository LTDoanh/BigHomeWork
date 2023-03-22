#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;


static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 600;
static const char* WINDOW_TITLE = "Star Trip";

static const int FPS = 60;
static const int METEORITE_SPEED = 5;
static const int BULLET_SPEED = 10;
static const int SHIP_SPEED = 5;

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;

static TTF_Font* font = nullptr;
static Mix_Music* music = nullptr;
static Mix_Chunk* shoot_sound = nullptr;
static Mix_Chunk* explode_sound = nullptr;

// PROJECT_BASE_H_INCLUDED
