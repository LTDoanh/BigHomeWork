#include "Global.h"

// Khai báo các biến toàn cục
SDL_Window* window = nullptr; // Cửa sổ chính
SDL_Renderer* renderer = nullptr; // Bộ vẽ
SDL_Rect buttons[BUTTON_NUM]; // Mảng các nút
std::vector<int> sequence; // Chuỗi các nút cần nhấn
int level = 1; // Cấp độ hiện tại
int index = 0; // Chỉ số của nút cần nhấn tiếp theo
bool showSequence = true; // Biến kiểm tra có đang hiển thị chuỗi hay không
//bool clicked = false; // Biến kiểm tra có đang click chuột vào nút hay không
//int clickedIndex = 0; // Chỉ số nút đã nhấn
Uint32 startTime = 0; // Thời điểm bắt đầu hiển thị chuỗi
bool gameOver = false; // Biến kiểm tra trò chơi kết thúc hay chưa
int score = 0; // Điểm số hiện tại
int timeLeft = 10; // Thời gian còn lại
bool running = true;
bool isMenu = true;
bool isGuide = false;
bool isRanking = false;
bool isReset = true;
bool isMute = false;
bool isPause = false;
bool isHighScore = false;
bool readHS = false;
string nameOfPlayer = "";

HScores hscores;
std::vector<Player> HighScores;

LTexture backgroundTexture;
LTexture titleTexture;
LTexture playTexture;
LTexture guideTexture;
LTexture guide2Texture;
LTexture quitTexture;
LTexture onMusicTexture;
LTexture offMusicTexture;
LTexture homeTexture;
LTexture homeIconTexture;
LTexture rankingTexture;
LTexture ranking2Texture;
LTexture playerTexture;
LTexture highScoreTexture;
LTexture levelTexture;
LTexture timeLeftTexture;
LTexture scoreTexture;
LTexture endTexture;
LTexture enterNameTexture;
LTexture nameTexture;
LTexture replayTexture;
LTexture onButtonTexture;
LTexture offButtonTexture;

TTF_Font* font = nullptr; // Font chữ
Mix_Music* music = nullptr; // Nhạc nền của game
Mix_Chunk* clickSound; // Âm thanh khi nhấn nút bất kì trong game
Mix_Chunk* beepSound = nullptr; // Âm thanh khi nhấn nút
Mix_Chunk* wrongSound = nullptr; // Âm thanh khi nhấn sai nút
