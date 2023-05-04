#include "Game.h"

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

    // Tải background có tên game
    if (!titleTexture.loadFromFile("title.png")) {
        cout << "Failed to load title texture!" << endl;
        return false;
    }

    // Tải nút chơi
    if (!playTexture.loadFromFile("play.png")) {
        cout << "Failed to load play texture!" << endl;
        return false;
    }

    // Tải nút hướng dẫn
    if (!guideTexture.loadFromFile("guide.png")) {
        cout << "Failed to load guide button texture!" << endl;
        return false;
    }
    // Tải giao diện hướng dẫn
    if (!guide2Texture.loadFromFile("guide2.png")) {
        cout << "Failed to load guide2 texture!" << endl;
        return false;
    }

    // Tải nút thoát
    if (!quitTexture.loadFromFile("quit.png")) {
        cout << "Failed to load quit texture!" << endl;
        return false;
    }

    // Tải nút chơi lại
    if (!replayTexture.loadFromFile("replay.png")) {
        cout << "Failed to load replay texture!" << endl;
        return false;
    }

    // Tải nút home
    if (!homeTexture.loadFromFile("home.png")) {
        cout << "Failed to load home texture!" << endl;
        return false;
    }
    if (!homeIconTexture.loadFromFile("homeIcon.png")) {
        cout << "Failed to load home icon texture!" << endl;
        return false;
    }

    // Tải nút cài đặt
    if (!settingTexture.loadFromFile("setting.png")) {
        cout << "Failed to load setting texture!" << endl;
        return false;
    }
    // Tải giao diện cài đặt
    if (!setting2Texture.loadFromFile("setting2.png")) {
        cout << "Failed to load setting2 texture!" << endl;
        return false;
    }

    // Tải nút tạm dừng/tiếp tục
    if (!pauseTexture.loadFromFile("pause.png")) {
        cout << "Failed to load on pause texture!" << endl;
        return false;
    }
    if (!continueTexture.loadFromFile("continue.png")) {
        cout << "Failed to load off continue texture!" << endl;
        return false;
    }

    // Tải nút bật/tắt âm thanh
    if (!onMusicTexture.loadFromFile("onMusic.png")) {
        cout << "Failed to load on music texture!" << endl;
        return false;
    }
    if (!offMusicTexture.loadFromFile("offMusic.png")) {
        cout << "Failed to load off music texture!" << endl;
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
    titleTexture.free();
    playTexture.free();
    guideTexture.free();
    guide2Texture.free();
    quitTexture.free();
    homeTexture.free();
    homeIconTexture.free();
    settingTexture.free();
    setting2Texture.free();
    pauseTexture.free();
    continueTexture.free();
    onMusicTexture.free();
    offMusicTexture.free();
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

    //Vẽ title
    titleTexture.render(0, 0);

    // Vẽ nút bật/tắt âm thanh lên màn hình
    if (isMute) {
        offMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }
    else {
        onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }

    // Vẽ các phím
    playTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth()/2, WINDOW_HEIGHT/2 - 50 - 3*playTexture.getHeight()/2);
    guideTexture.render(WINDOW_WIDTH/2 - guideTexture.getWidth()/2, WINDOW_HEIGHT/2 - guideTexture.getHeight()/2);
    settingTexture.render(WINDOW_WIDTH/2 - settingTexture.getWidth()/2, WINDOW_HEIGHT/2 + settingTexture.getHeight()/2 + 50);
    quitTexture.render(WINDOW_WIDTH/2 - quitTexture.getWidth()/2, WINDOW_HEIGHT/2 + 3*quitTexture.getHeight()/2 + 100);

    //  Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

/** Hàm vẽ hướng dẫn **/
void renderGuide()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    guide2Texture.render(0, 0);

    // Vẽ nút bật/tắt âm thanh lên màn hình
    if (isMute) {
        offMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }
    else {
        onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }

    // Vẽ nút home lên màn hình
    homeIconTexture.render(WINDOW_WIDTH - homeIconTexture.getWidth() - 10, homeIconTexture.getHeight() + 20);

    // Vẽ nút play và nút quit lên màn hình
    playTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth() - 50, 520);
    quitTexture.render(WINDOW_WIDTH/2 + 50, 520);

    //  Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

void renderSetting()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    setting2Texture.render(0, 0);

    // Vẽ nút bật/tắt âm thanh lên màn hình
    if (isMute) {
        offMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }
    else {
        onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }

    // Vẽ nút home lên màn hình
    homeIconTexture.render(WINDOW_WIDTH - homeIconTexture.getWidth() - 10, homeIconTexture.getHeight() + 20);

    // Vẽ nút play và nút quit lên màn hình
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

    // Vẽ nút bật/tắt âm thanh lên màn hình
    if (isMute) {
        offMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }
    else {
        onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }

    // Vẽ nút home lên màn hình
    homeIconTexture.render(WINDOW_WIDTH - homeIconTexture.getWidth() - 10, homeIconTexture.getHeight() + 20);

    // Vẽ nút tạm ngừng/tiếp tục
    if (isPause) {
        continueTexture.render(WINDOW_WIDTH - pauseTexture.getWidth() - 10, 2*pauseTexture.getHeight() + 30);
    }
    else {
        pauseTexture.render(WINDOW_WIDTH - pauseTexture.getWidth() - 10, 2*pauseTexture.getHeight() + 30);
    }

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

    //Vẽ background có title
    titleTexture.render(0, 0);

    // Vẽ nút bật/tắt âm thanh lên màn hình
    if (isMute) {
        offMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }
    else {
        onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }

    string endText = "YOUR SCORE: " + to_string(score);
    //Tải và hiển thị điểm lên màn hình;
    if (!endTexture.loadFromRenderedText(endText, TEXT_COLOR, font)) {
        cout << "Failed to load end texture!" << endl;
        return;
    }
    endTexture.render(WINDOW_WIDTH/2 - endTexture.getWidth()/2, 150);

    int x = WINDOW_WIDTH/2 - replayTexture.getWidth()/2;

    homeTexture.render(x, WINDOW_HEIGHT/2 - homeTexture.getHeight());

    replayTexture.render(x, WINDOW_HEIGHT/2 + 50);

    quitTexture.render(x, WINDOW_HEIGHT/2 + 100 + replayTexture.getHeight());

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
        // Nếu nhấn chuột trái thì kiểm tra nút được nhấn
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            // Lấy tọa độ của chuột
            int x = e.button.x;
            int y = e.button.y;

            // Kiểm tra xem chuột có nhấn vào nút bật/tắt âm thanh không
            if (x >= WINDOW_WIDTH - onMusicTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 10 && y <= 10 + onMusicTexture.getHeight()) {
                if(isMute) {
                    Mix_ResumeMusic();
                    Mix_Volume(-1, 64);
                }
                else {
                    Mix_PauseMusic();
                    Mix_Volume(-1, 0);
                }
                isMute = !isMute;
            }
            if (isMenu) {
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
                else if (x >= xGuide && x <= xGuide + settingTexture.getWidth() && y >= yGuide + 50 + settingTexture.getHeight() && y <= yGuide + 50 + 2*settingTexture.getHeight()) {
                    isSetting = true;
                    isMenu = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if (x >= xGuide && x <= xGuide + quitTexture.getWidth() && y >= yGuide + 100 + 2*quitTexture.getHeight() && y <= yGuide + 100 + 3*quitTexture.getHeight()) {
                    running = false;
                }
            }
            else if (isGuide) {
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
                // Kiểm tra xem chuột có nhấn vào nút home không
                else if (x >= WINDOW_WIDTH - homeIconTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 20 + homeIconTexture.getHeight() && y <= 20 + 2*homeIconTexture.getHeight()) {
                    isMenu = true;
                    isGuide = false;
                }
            }
            else if (isSetting) {
                // Nếu nhấn nút play thì bắt đầu chạy game
                if (x >= WINDOW_WIDTH/2 - 50 - playTexture.getWidth() && x <= WINDOW_WIDTH/2 - 50 && y >= 520 && y <= 520 + playTexture.getHeight()) {
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    isSetting = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if(x >= WINDOW_WIDTH/2 + 50 && x <= WINDOW_WIDTH/2 + 50 + quitTexture.getWidth() && y >= 520 && y <= 520 + quitTexture.getHeight()) {
                    running = false;
                }
                // Kiểm tra xem chuột có nhấn vào nút home không
                else if (x >= WINDOW_WIDTH - homeIconTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 20 + homeIconTexture.getHeight() && y <= 20 + 2*homeIconTexture.getHeight()) {
                    isMenu = true;
                    isSetting = false;
                }
            }
            else if (gameOver) {
                int xReplay = WINDOW_WIDTH/2 - replayTexture.getWidth()/2;
                // Nếu nhấn nút replay thì chạy lại game
                if (x >= xReplay && x <= xReplay + replayTexture.getWidth() && y >= WINDOW_HEIGHT/2 + 50 && y <= WINDOW_HEIGHT/2 + 50 + replayTexture.getHeight()) {
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    gameOver = false;
                }
                // Nếu nhấn nút quit thì thoát game
                else if(x >= xReplay && x <= xReplay + quitTexture.getWidth() && y >= WINDOW_HEIGHT/2 + quitTexture.getHeight() + 100 && y <= WINDOW_HEIGHT/2 + 2*quitTexture.getHeight() + 100) {
                    running = false;
                }
                else if (x >= xReplay && x <= xReplay + replayTexture.getWidth() && y >= WINDOW_HEIGHT/2 - homeTexture.getHeight() && y <= WINDOW_HEIGHT/2) {
                    isMenu = true;
                    gameOver = false;
                }
            }
            else {
                // Kiểm tra xem chuột có nhấn vào nút home không
                if (x >= WINDOW_WIDTH - homeIconTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 20 + homeIconTexture.getHeight() && y <= 20 + 2*homeIconTexture.getHeight()) {
                    isMenu = true;
                }

                // Kiểm tra xem chuột có nhấn vào nút tạm dừng/tiếp tục khong
                if (x >= WINDOW_WIDTH - pauseTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 30 + 2*pauseTexture.getHeight() && y <= 30 + 3*pauseTexture.getHeight()) {
                    isPause= !isPause;
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
                                // Tạo ngẫu nhiên thêm 1 ô phát sáng
                                int temp = rand() % BUTTON_NUM;
                                while (temp == sequence.back()) {
                                    temp = rand() % BUTTON_NUM;
                                }
                                sequence.push_back(temp);
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
        else if (isSetting) {
            renderSetting();
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
