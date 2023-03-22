#pragma once

#include "Project_Base.h"
#include "LTexture.h"
#include "Ship.h"

static Ship ship;
static int score = 0;
static bool quit = false;

void update();

void handleEvents();

void render();

// SDL_UTILS_H_INCLUDED
