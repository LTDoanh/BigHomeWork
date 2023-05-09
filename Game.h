#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Global.h"
#include "Constants.h"
#include "LTexture.h"
#include "Player.h"
#include "HScores.h"

extern HScores hscores;

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
extern LTexture modeTexture;
extern LTexture easyModeTexture;
extern LTexture defaultModeTexture;
extern LTexture normalModeTexture;
extern LTexture hardModeTexture;
extern LTexture volumeTexture;
extern LTexture volumeNumberTexture;
extern LTexture volumeUpTexture;
extern LTexture volumeDownTexture;
extern LTexture rankingTexture;
extern LTexture ranking2Texture;
extern LTexture playerTexture;
extern LTexture highScoreTexture;
extern LTexture pauseTexture;
extern LTexture continueTexture;
extern LTexture levelTexture;
extern LTexture timeLeftTexture;
extern LTexture scoreTexture;
extern LTexture endTexture;
extern LTexture enterNameTexture;
extern LTexture nameTexture;
extern LTexture replayTexture;
extern LTexture onButtonTexture;
extern LTexture offButtonTexture;

bool init();
bool loadMedia();
void close();
void renderMenu();
void renderGuide();
void renderSetting();
void renderRanking();
void renderButtons();
void renderGame();
void renderHighScore();
void renderGameOver();
void handleEvents();
void update();
void run();

#endif // GAME_H_INCLUDED
