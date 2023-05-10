#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Global.h"
#include "Constants.h"
#include "LTexture.h"
#include "Player.h"
#include "HScores.h"

extern HScores hscores;

extern LTexture backgroundTexture; // ảnh nền
extern LTexture titleTexture; // ảnh nền có chứa tên game
extern LTexture playTexture; // ảnh nút play
extern LTexture guideTexture; // ảnh nút guide
extern LTexture guide2Texture; // ảnh nền của thư mục hướng dẫn
extern LTexture quitTexture; // ảnh nút quit
extern LTexture onMusicTexture; // ảnh nút bật âm thanh
extern LTexture offMusicTexture; // ảnh nút tắt âm thanh
extern LTexture homeTexture; // ảnh nút home
extern LTexture homeIconTexture; // ảnh nút home (icon)
extern LTexture settingTexture; // ảnh nút setting
extern LTexture setting2Texture; // ảnh nền của thư mục setting
extern LTexture modeTexture; // ảnh chữ "MODE"
extern LTexture easyModeTexture; // ảnh chữ "easy" mode
extern LTexture defaultModeTexture; // ảnh chữ "default" mode
extern LTexture normalModeTexture; // ảnh chữ "normal" mode
extern LTexture hardModeTexture; // ảnh chữ "hard" mode
extern LTexture volumeTexture; // ảnh chữ "volume"
extern LTexture volumeNumberTexture; // ảnh mức độ của âm thanh
extern LTexture volumeUpTexture; // ảnh nút tăng âm lượng
extern LTexture volumeDownTexture; // ảnh nút giảm âm lượng
extern LTexture rankingTexture; // ảnh nút ranking
extern LTexture ranking2Texture; // ảnh nền của thư mục ranking
extern LTexture playerTexture;
extern LTexture highScoreTexture;
extern LTexture levelTexture;
extern LTexture timeLeftTexture;
extern LTexture scoreTexture;
extern LTexture endTexture;
extern LTexture enterNameTexture;
extern LTexture nameTexture;
extern LTexture replayTexture;
extern LTexture onButtonTexture;
extern LTexture offButtonTexture;


/** Hàm khởi tạo SDL **/
bool init();

/** Hàm tải các thành phần của trò chơi **/
bool loadMedia();

/** Hàm giải phóng các thành phần của trò chơi **/
void close();

/** Hàm vẽ menu lên màn hình **/
void renderMenu();

/** Hàm vẽ thư mục hướng dẫn lên màn hình **/
void renderGuide();

/** Hàm vẽ thư mục cài đặt lên màn hình **/
void renderSetting();

/** Hàm vẽ thư mục BXH lên màn hình **/
void renderRanking();

/** Hàm vẽ các ô của trò chơi lên màn hình **/
void renderButtons();

/** Hàm vẽ các thành phần của trò chơi (chính) lên màn hình **/
void renderGame();

/** Hàm vẽ thư mục nhập tên nếu đạt high score **/
void renderHighScore();

/** Hàm vẽ thư mục game over **/
void renderGameOver();

/** Hàm xử lý các sự kiện đầu vào **/
void handleEvents();

/** Cập nhật trạng thái của game **/
void update();

/** Hàm chạy trò chơi **/
void run();

#endif // GAME_H_INCLUDED
