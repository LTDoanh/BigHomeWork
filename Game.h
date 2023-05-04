#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Global.h"
#include "Constants.h"
#include "LTexture.h"

extern LTexture backgroundTexture;
extern LTexture titleTexture;
extern LTexture playTexture;
extern LTexture guideTexture;
extern LTexture guide2Texture;
extern LTexture quitTexture;
extern LTexture onMusicTexture;
extern LTexture offMusicTexture;
extern LTexture homeTexture;
extern LTexture homeIconTexture;
extern LTexture settingTexture;
extern LTexture setting2Texture;
extern LTexture pauseTexture;
extern LTexture continueTexture;
extern LTexture levelTexture;
extern LTexture timeLeftTexture;
extern LTexture scoreTexture;
extern LTexture endTexture;
extern LTexture replayTexture;

bool init();
void close();
void renderMenu();
void renderGuide();
void renderSetting();
void renderButtons();
void renderGame();
void renderGameOver();
void handleEvents();
void update();
void run();

#endif // GAME_H_INCLUDED
