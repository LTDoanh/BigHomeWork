#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Khai báo các hằng số
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BUTTON_SIZE = 100;
const int BUTTON_GAP = 20;
const int BUTTON_ROW = 4;
const int BUTTON_COL = 4;
const int BUTTON_NUM = BUTTON_ROW * BUTTON_COL;
const int DELAY_TIME = 1000; // Thời gian chờ giữa các lượt
const int FLASH_TIME = 500; // Thời gian nhấp nháy của nút
const SDL_Color BG_COLOR = {0, 0, 0, 255}; // Màu nền
const SDL_Color BUTTON_COLOR = {238, 64, 240, 255}; // Màu nút
const SDL_Color FLASH_COLOR = {255, 255, 255, 255}; // Màu nhấp nháy
const SDL_Color TEXT_COLOR = {255, 255, 255, 255}; // Màu chữ
const SDL_Color CLICKED_COLOR = {255, 255, 0, 255}; // Màu nhấn nút

// Khai báo các biến toàn cục
SDL_Window* window = nullptr; // Cửa sổ chính
SDL_Renderer* renderer = nullptr; // Bộ vẽ
SDL_Rect buttons[BUTTON_NUM]; // Mảng các nút
vector<int> sequence; // Chuỗi các nút cần nhấn
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
bool isReset = true;

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

LTexture backgroundTexture; // Hình nền
LTexture playTexture;
LTexture guideTexture;
LTexture guide2Texture;
LTexture quitTexture;
LTexture homeTexture;
LTexture onMusicTexture;
LTexture levelTexture;
LTexture timeLeftTexture;
LTexture scoreTexture;
LTexture endTexture;
LTexture replayTexture;


TTF_Font* font = nullptr; // Font chữ
Mix_Music* music = nullptr; // Nhạc nền của game
Mix_Chunk* beepSound = nullptr; // Âm thanh khi nhấn nút
Mix_Chunk* wrongSound = nullptr; // Âm thanh khi nhấn sai nút

/** Hàm khởi tạo các thành phần của trò chơi **/
bool init()
{
    // Khởi tạo thư viện SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    // Khởi tạo thư viện SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }
    // Khởi tạo thư viện SDL_ttf
    if (TTF_Init() < 0) {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    // Khởi tạo thư viện SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }

    // Tạo window
    window = SDL_CreateWindow("Memory Challenge", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    // Tạo renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Tải background
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        cout << "Failed to load background texture!" << endl;
        return false;
    }

    // Tải nút play
    if (!playTexture.loadFromFile("play.png")) {
        cout << "Failed to load play texture!" << endl;
        return false;
    }

    // Tải nút hướng dẫn
    if (!guideTexture.loadFromFile("guide.png")) {
        cout << "Failed to load guide button texture!" << endl;
        return false;
    }

    // Tải nút quit
    if (!quitTexture.loadFromFile("quit.png")) {
        cout << "Failed to load quit texture!" << endl;
        return false;
    }

    // Tải nút replay
    if (!replayTexture.loadFromFile("replay.png")) {
        cout << "Failed to load replay texture!" << endl;
        return false;
    }

    // Tải nút home
    if (!homeTexture.loadFromFile("home.png")) {
        cout << "Failed to load home texture!" << endl;
        return false;
    }

    // Tải nút on music
    if (!onMusicTexture.loadFromFile("onMusic.png")) {
        cout << "Failed to load on music texture!" << endl;
        return false;
    }

    // Tải font chữ
    font = TTF_OpenFont("font.ttf", 24);
    if (font == nullptr) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    // Tải âm thanh
    music = Mix_LoadMUS("music.mp3");
    if(music == nullptr)
    {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    beepSound = Mix_LoadWAV("beep.wav");
    if (beepSound == nullptr) {
        cout << "Failed to load beep sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    wrongSound = Mix_LoadWAV("wrong.wav");
    if (wrongSound == nullptr) {
        cout << "Failed to load wrong sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }

    // Tạo các nút
    for (int i = 0; i < BUTTON_NUM; i++) {
        buttons[i].x = (i % BUTTON_COL) * (BUTTON_SIZE + BUTTON_GAP) + (WINDOW_WIDTH - BUTTON_COL * (BUTTON_SIZE + BUTTON_GAP) + BUTTON_GAP) / 2;
        buttons[i].y = (i / BUTTON_COL) * (BUTTON_SIZE + BUTTON_GAP) + (WINDOW_HEIGHT - BUTTON_ROW * (BUTTON_SIZE + BUTTON_GAP) + BUTTON_GAP) / 2;
        buttons[i].w = BUTTON_SIZE;
        buttons[i].h = BUTTON_SIZE;
    }

    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(time(nullptr));

    return true;
}

/** Hàm giải phóng các thành phần của trò chơi **/
void close()
{
    // Giải phóng texture
    backgroundTexture.free();
    playTexture.free();
    guideTexture.free();
    guide2Texture.free();
    quitTexture.free();
    homeTexture.free();
    onMusicTexture.free();
    levelTexture.free();
    timeLeftTexture.free();
    scoreTexture.free();
    endTexture.free();
    replayTexture.free();

    // Giải phóng font chữ
    TTF_CloseFont(font);
    font = nullptr;

    // Giải phóng âm thanh
    Mix_FreeMusic(music);
    music = nullptr;
    Mix_FreeChunk(beepSound);
    beepSound = nullptr;
    Mix_FreeChunk(wrongSound);
    wrongSound = nullptr;

    // Giải phóng renderer
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    // Giải phóng window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Thoát khỏi các thư viện SDL
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/** Hàm vẽ menu **/
void renderMenu()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    //Vẽ background
    backgroundTexture.render(0, 0);

    // Vẽ các phím
    playTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth()/2, WINDOW_HEIGHT/2 - 50 - playTexture.getHeight() - guideTexture.getHeight()/2);
    guideTexture.render(WINDOW_WIDTH/2 - guideTexture.getWidth()/2, WINDOW_HEIGHT/2 - guideTexture.getHeight()/2);
    quitTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth()/2, WINDOW_HEIGHT/2 + guideTexture.getHeight()/2 + 50);

    //  Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

/** Hàm vẽ hướng dẫn **/
void renderGuide()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    // Tải ảnh hướng dẫn
    if (!guide2Texture.loadFromFile("guide2.png")) {
        cout << "Failed to load guide texture!" << endl;
        return;
    }
    guide2Texture.render(0, 0);

    playTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth() - 50, 520);
    quitTexture.render(WINDOW_WIDTH/2 + 50, 520);

    //  Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

/** Hàm vẽ các nút lên màn hình **/
void renderButtons()
{
    // Đặt màu cho bộ vẽ
    SDL_SetRenderDrawColor(renderer, BUTTON_COLOR.r, BUTTON_COLOR.g, BUTTON_COLOR.b, BUTTON_COLOR.a);
    // Vẽ các nút bằng cách điền các hình vuông
    for (int i = 0; i < BUTTON_NUM; i++) {
        SDL_RenderFillRect(renderer, &buttons[i]);
    }
}

/** Hàm vẽ các thành phần của trò chơi lên màn hình **/
void renderGame()
{
    // Xóa màn hình
    SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
    SDL_RenderClear(renderer);

    // Vẽ hình nền lên màn hình
    backgroundTexture.render(0, 0);

    // Vẽ các nút lên màn hình
    renderButtons();
    // Vẽ nút nhấp nháy nếu đang hiển thị chuỗi
    if (showSequence) {
        int flashIndex = sequence[index];
        SDL_SetRenderDrawColor(renderer, FLASH_COLOR.r, FLASH_COLOR.g, FLASH_COLOR.b, FLASH_COLOR.a);
        SDL_RenderFillRect(renderer, &buttons[flashIndex]);
    }
//    if (clicked) {
//        SDL_SetRenderDrawColor(renderer, CLICKED_COLOR.r, CLICKED_COLOR.g, CLICKED_COLOR.b, CLICKED_COLOR.a);
//        SDL_RenderFillRect(renderer, &buttons[clickedIndex]);
//    }

    // Vẽ nút home lên màn hình
    homeTexture.render(WINDOW_WIDTH - homeTexture.getWidth() - 10, 10);

    onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, homeTexture.getHeight() + 20);

    string levelText = "Level:" + to_string(level);
    // Tải và vẽ level lên màn hình
    if (!levelTexture.loadFromRenderedText(levelText, TEXT_COLOR, font)) {
        cout << "Failed to load level texture!" << endl;
        return;
    }
    levelTexture.render(WINDOW_WIDTH/2 - levelTexture.getWidth()/2, 20);

    string timeText = "Time Left: " + to_string(timeLeft);
    // Tải và vẽ time left lên màn hình
    if (!timeLeftTexture.loadFromRenderedText(timeText, TEXT_COLOR, font)) {
        cout << "Failed to load time left texture!" << endl;
        return;
    }
    timeLeftTexture.render(10, 20);

    string scoreText = "Score: " + to_string(score);
    // Tải và vẽ score lên màn hình
    if (!scoreTexture.loadFromRenderedText(scoreText, TEXT_COLOR, font)) {
        cout << "Failed to load score texture!" << endl;
        return;
    }
    scoreTexture.render(WINDOW_WIDTH/2 - scoreTexture.getWidth()/2, 550);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

void renderGameOver()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    //Vẽ lại background
    backgroundTexture.render(0, 0);

    string endText = "YOUR SCORE: " + to_string(score);
    //Tải và hiển thị điểm lên màn hình;
    if (!endTexture.loadFromRenderedText(endText, TEXT_COLOR, font)) {
        cout << "Failed to load end texture!" << endl;
        return;
    }
    endTexture.render(WINDOW_WIDTH/2 - endTexture.getWidth()/2, 150);

    int xReplay = WINDOW_WIDTH/2 - replayTexture.getWidth()/2;
    int yReplay = WINDOW_HEIGHT/2 - replayTexture.getHeight()/2;

    replayTexture.render(xReplay, yReplay);

    quitTexture.render(xReplay, yReplay + replayTexture.getHeight() + 50);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

/** Hàm xử lý các sự kiện đầu vào **/
void handleEvents()
{
    // Tạo biến lưu trữ sự kiện
    SDL_Event e;
    // Lặp qua hàng đợi các sự kiện
    while (SDL_PollEvent(&e) != 0) {
        // Nếu sự kiện là thoát cửa sổ
        if (e.type == SDL_QUIT) {
            // Đặt biến kết thúc trò chơi là true
            running = false;
        }
        if (isMenu) {
            // Nếu nhấn chuột trái thì kiểm tra nút được nhấn
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Lấy tọa độ của chuột
                int x = e.button.x;
                int y = e.button.y;

                int xGuide = WINDOW_WIDTH/2 - guideTexture.getWidth()/2;
                int yGuide = WINDOW_HEIGHT/2 - guideTexture.getHeight()/2;

                // Nếu nhấn nút play thì bắt đầu chạy game
                if (x >= xGuide && x <= xGuide + playTexture.getWidth() && y >= yGuide - 50 - playTexture.getHeight() && y <= yGuide - 50) {
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    isMenu = false;
                }
                // Nếu nhấn nút guide thì hiển thị hướng dẫn
                else if (x >= xGuide && x <= xGuide + guideTexture.getWidth() && y >= yGuide && y <= yGuide + guideTexture.getHeight()) {
                    isMenu = false;
                    isGuide = true;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if (x >= xGuide && x <= xGuide + quitTexture.getWidth() && y >= yGuide + 50 + quitTexture.getHeight() && y <= yGuide + 50 + 2*quitTexture.getHeight()) {
                    running = false;
                }
            }
        }
        else if (isGuide) {
            // Nếu nhấn chuột trái thì kiểm tra nút được nhấn
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Lấy tọa độ của chuột
                int x = e.button.x;
                int y = e.button.y;

                // Nếu nhấn nút play thì bắt đầu chạy game
                if (x >= WINDOW_WIDTH/2 - 50 - playTexture.getWidth() && x <= WINDOW_WIDTH/2 - 50 && y >= 520 && y <= 520 + playTexture.getHeight()) {
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    isGuide = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if(x >= WINDOW_WIDTH/2 + 50 && x <= WINDOW_WIDTH/2 + 50 + quitTexture.getWidth() && y >= 520 && y <= 520 + quitTexture.getHeight()) {
                    running = false;
                }
            }
        }
        else if (gameOver) {
            // Nếu nhấn chuột trái thì kiểm tra nút được nhấn
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Lấy tọa độ của chuột
                int x = e.button.x;
                int y = e.button.y;

                int xReplay = WINDOW_WIDTH/2 - replayTexture.getWidth()/2;
                int yReplay = WINDOW_HEIGHT/2 - replayTexture.getHeight()/2;
                // Nếu nhấn nút replay thì chạy lại game
                if (x >= xReplay && x <= xReplay + replayTexture.getWidth() && y >= yReplay && y <= yReplay + replayTexture.getHeight()) {
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    gameOver = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if(x >= xReplay && x <= xReplay + quitTexture.getWidth() && y >= yReplay + replayTexture.getHeight() + 50 && y <= yReplay + 2*replayTexture.getHeight() + 50) {
                    running = false;
                }
            }
        }
        else {
            // Nếu nhấn chuột trái thì kiểm tra nút được nhấn
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Nếu đang hiển thị chuỗi thì bỏ qua
                if (showSequence) {
                    return;
                }
                // Lấy tọa độ của chuột
                int x = e.button.x;
                int y = e.button.y;

                // Kiểm tra xem chuột có nhấn vào nút home không
                if (x >= WINDOW_WIDTH - homeTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 10 && y <= 10 + homeTexture.getHeight()) {
                    isMenu = true;
                }
                // Kiểm tra xem chuột có nhấn vào một nút nào không
                for (int i = 0; i < BUTTON_NUM; i++) {
                    if (x >= buttons[i].x && x <= buttons[i].x + buttons[i].w && y >= buttons[i].y && y <= buttons[i].y + buttons[i].h) {
                        //clicked = true;
                        //clickedIndex = i;
                        // Nếu nút nhấn đúng với nút cần nhấn tiếp theo trong chuỗi
                        if (i == sequence[index]) {
                            // Phát âm thanh khi nhấn nút
                            Mix_PlayChannel(-1, beepSound, 0);
                            index++;
                            score+=10;
                            // Nếu đã nhấn hết chuỗi
                            if (index == level) {
                                // Tăng cấp độ
                                level++;
                                // Đặt biến hiển thị chuỗi là true
                                showSequence = true;
                                // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                                startTime = SDL_GetTicks();
                                // Đặt chỉ số về 0
                                index = 0;
                                sequence.push_back(rand() % BUTTON_NUM);
                            }
                        }
                        // Nếu nút nhấn sai
                        else {
                            // Phát âm thanh khi nhấn sai nút
                            Mix_PlayChannel(-1, wrongSound, 0);
                            // Đặt biến kết thúc trò chơi là true
                            gameOver = true;
                        }
                        break;
                    }
                }
            }
        }
    }
}

/** Cập nhật trạng thái của game **/
void update()
{
    // Nếu đang hiển thị chuỗi thì kiểm tra thời gian để chuyển sang nút tiếp theo hoặc kết thúc hiển thị
    if (showSequence) {
        timeLeft = 10;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - startTime > FLASH_TIME) {
            index++;
            startTime = currentTime;
            if (index == level) {
                showSequence = false;
                index = 0;
            }
        }
    }
    else {
        // Tính thời gian còn lại bằng cách lấy cấp độ trừ đi số giây trôi qua kể từ lúc bắt đầu hiển thị chuỗi
        timeLeft = 10 - (SDL_GetTicks() - startTime)/1000;
        // Nếu thời gian còn lại âm hoặc bằng 0
        if (timeLeft <= 0) {
            // Đặt biến kết thúc trò chơi là true
            gameOver = true;
        }
    }
}

/** Hàm chạy trò chơi **/
void run()
{
    // Phát nhạc nền
    Mix_PlayMusic(music,-1);

    // Lặp cho đến khi kết thúc trò chơi hoặc thoát cửa sổ
    while (running) {

        // Xử lý các sự kiện đầu vào
        handleEvents();
        if (isReset) {
            // Xóa sequence cũ nếu có
            sequence.clear();
            // Tạo chuỗi ban đầu gồm 1 nút ngẫu nhiên
            sequence.push_back(rand() % BUTTON_NUM);

            showSequence = true;
            index = 0;
            level = 1;
            score = 0;
            timeLeft = 10;

            isReset = false;
        }

        if (isMenu) {
            renderMenu();
        }
        else if (isGuide) {
            renderGuide();
        }
        else if (gameOver) {
            renderGameOver();
        }
        else {
            // Cập nhật trạng thái của trò chơi
            update();

            // Vẽ các thành phần của trò chơi lên màn hình
            renderGame();
        }
    }
}

// Hàm chính của chương trình
int main(int argc, char* argv[])
{
    // Khởi tạo SDL và các thành phần liên quan
    if (!init()) {
        cout << "Không thể khởi tạo SDL." << endl;
        return -1;
    }
    // Chạy trò chơi
    run();
    // Giải phóng các thành phần đã khởi tạo
    close();
    return 0;
}

// Hàm khởi tạo
LTexture::LTexture() {
	texture = nullptr;

	width = 0;
	height = 0;
}

// Hàm giải phóng texture
void LTexture::free() {
	if (texture != nullptr)
	{
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

// Hàm tải texture từ file
bool LTexture::loadFromFile(string path) {
	// Giải phóng texture cũ nếu có
	free();

	SDL_Texture* newTexture = nullptr;

    // Tạo surface từ file ảnh
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == nullptr)
	{
		cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));

		// Tạo texture từ surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == nullptr)
		{
			cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			// Lấy kích thước của texture
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		// Giải phóng surface
		SDL_FreeSurface(loadedSurface);
	}

	// Tra về kết quả
    texture = newTexture;
    return texture != nullptr;
}

// Hàm tạo texture từ chuỗi văn bản
bool LTexture::loadFromRenderedText(string text, SDL_Color color, TTF_Font* font) {
    // Giải phóng texture cũ nếu có
    free();

    bool success=true;

    // Tạo surface từ chuỗi văn bản và font chữ
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(textSurface == nullptr){
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else{
        // Tạo texture từ surface
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == nullptr){
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else{
            // Lấy kích thước của texture
            width = textSurface->w;
            height = textSurface->h;
        }

        // Giải phóng surface
        SDL_FreeSurface(textSurface);
    }

    return success;
}

// Hàm render texture lên màn hình
void LTexture::render(int x, int y) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, width, height};

	// Render texture lên màn hình
	SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
}

// Hàm lấy chiều rộng của texture
int LTexture::getWidth() {
	return width;
}

// Hàm lấy chiều cao của texture
int LTexture::getHeight() {
	return height;
}
