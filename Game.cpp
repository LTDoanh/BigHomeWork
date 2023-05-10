#include "Game.h"

/** Hàm khởi tạo SDL **/
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

    return true;
}

/** Hàm tải các thành phần của trò chơi **/
bool loadMedia()
{
    // Tải font chữ
    font = TTF_OpenFont("font.ttf", 24);
    if (font == nullptr) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
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
        cout << "Failed to load guide background texture!" << endl;
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
        cout << "Failed to load setting background texture!" << endl;
        return false;
    }

    // Tải chế độ và các chế độ chơi
    if (!modeTexture.loadFromRenderedText("MODE:", TEXT_COLOR, font)) {
        cout << "Failed to load mode texture!" << endl;
        return false;
    }
    if (!easyModeTexture.loadFromRenderedText("Easy", TEXT_COLOR, font)) {
        cout << "Failed to load easy mode texture!" << endl;
        return false;
    }
    if (!defaultModeTexture.loadFromRenderedText("Default", TEXT_COLOR, font)) {
        cout << "Failed to load default mode texture!" << endl;
        return false;
    }
    if (!normalModeTexture.loadFromRenderedText("Normal", TEXT_COLOR, font)) {
        cout << "Failed to load normal mode texture!" << endl;
        return false;
    }
    if (!hardModeTexture.loadFromRenderedText("Hard", TEXT_COLOR, font)) {
        cout << "Failed to load hard mode texture!" << endl;
        return false;
    }

    // Tải âm lượng và nút tăng/giảm âm lượng
    if (!volumeTexture.loadFromRenderedText("VOLUME:", TEXT_COLOR, font)) {
        cout << "Failed to load volume texture!" << endl;
        return false;
    }
    if (!volumeUpTexture.loadFromRenderedText("+", TEXT_COLOR, font)) {
        cout << "Failed to load volume up texture!" << endl;
        return false;
    }
    if (!volumeDownTexture.loadFromRenderedText("-", TEXT_COLOR, font)) {
        cout << "Failed to load volume down texture!" << endl;
        return false;
    }

    // Tải nút BXH
    if (!rankingTexture.loadFromFile("ranking.png")) {
        cout << "Failed to load ranking texture!";
        return false;
    }
    // Tải giao diện BXH
    if (!ranking2Texture.loadFromFile("ranking2.png")) {
        cout << "Failed to load ranking texture!";
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

    // Tải nút bật/tắt
    if (!onButtonTexture.loadFromFile("on.png")) {
        cout << "Failed to load on button texture!";
        return false;
    }
    if (!offButtonTexture.loadFromFile("off.png")) {
        cout << "Failed to load off button texture!";
        return false;
    }

    // Tải nhạc nền
    music = Mix_LoadMUS("music.mp3");
    if(music == nullptr)
    {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    // Tải âm thanh nhấn nút
    clickSound = Mix_LoadWAV("click.wav");
    if (clickSound == nullptr) {
        cout << "Failed to load click sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    // Tải âm thanh nhấn đúng nút khi chơi game
    beepSound = Mix_LoadWAV("beep.wav");
    if (beepSound == nullptr) {
        cout << "Failed to load beep sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    // Tải âm thanh nhấn sai nút khi chơi game
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
    modeTexture.free();
    easyModeTexture.free();
    defaultModeTexture.free();
    normalModeTexture.free();
    hardModeTexture.free();
    volumeTexture.free();
    volumeNumberTexture.free();
    volumeUpTexture.free();
    volumeDownTexture.free();
    rankingTexture.free();
    ranking2Texture.free();
    playerTexture.free();
    highScoreTexture.free();
    onMusicTexture.free();
    offMusicTexture.free();
    levelTexture.free();
    timeLeftTexture.free();
    scoreTexture.free();
    endTexture.free();
    enterNameTexture.free();
    nameTexture.free();
    replayTexture.free();
    onButtonTexture.free();
    offButtonTexture.free();

    // Giải phóng font chữ
    TTF_CloseFont(font);
    font = nullptr;

    // Giải phóng âm thanh
    Mix_FreeMusic(music);
    music = nullptr;
    Mix_FreeChunk(clickSound);
    clickSound = nullptr;
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

/** Hàm vẽ menu lên màn hình **/
void renderMenu()
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

    // Vẽ nút chơi
    playTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth()/2, WINDOW_HEIGHT/2 - BUTTON_GAP - 3*playTexture.getHeight()/2);
    // Vẽ nút hướng dẫn
    guideTexture.render(WINDOW_WIDTH/2 - guideTexture.getWidth()/2, WINDOW_HEIGHT/2 - guideTexture.getHeight()/2);
    // Vẽ nút cài đặt
    settingTexture.render(WINDOW_WIDTH/2 - settingTexture.getWidth()/2, WINDOW_HEIGHT/2 + settingTexture.getHeight()/2 + BUTTON_GAP);
    // Vẽ nút BXH
    rankingTexture.render(WINDOW_WIDTH/2 - rankingTexture.getWidth()/2, WINDOW_HEIGHT/2 + 3*rankingTexture.getHeight()/2 + 2*BUTTON_GAP);
    // Vẽ nút thoát
    quitTexture.render(WINDOW_WIDTH/2 - quitTexture.getWidth()/2, WINDOW_HEIGHT/2 + 5*quitTexture.getHeight()/2 + 3*BUTTON_GAP);

    //  Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

/** Hàm vẽ thư mục hướng dẫn lên màn hình **/
void renderGuide()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    // Vẽ background có hướng dẫn lên màn hình
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

/** Hàm vẽ thư mục cài đặt lên màn hình **/
void renderSetting()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    // Vẽ background setting
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

    // Vẽ chế độ chơi game
    modeTexture.render(150, 200);
    // Chế độ dễ
    if (isEasy) {
        onButtonTexture.render(160 + modeTexture.getWidth(), 200);
    }
    else {
        offButtonTexture.render(170 + modeTexture.getWidth(), 200);
    }
    easyModeTexture.render(180 + modeTexture.getWidth() + onButtonTexture.getWidth(), 200);
    // Chế độ mặc định
    if (isDefault) {
        onButtonTexture.render(WINDOW_WIDTH/2 + 70, 200);
    }
    else {
        offButtonTexture.render(WINDOW_WIDTH/2 + 70, 200);
    }
    defaultModeTexture.render(WINDOW_WIDTH/2 + 80 + onButtonTexture.getWidth(), 200);
    // Chế độ trung bình
    if (isNormal) {
        onButtonTexture.render(160 + modeTexture.getWidth(), 250);
    }
    else {
        offButtonTexture.render(170 + modeTexture.getWidth(), 250);
    }
    normalModeTexture.render(180 + modeTexture.getWidth() + onButtonTexture.getWidth(), 250);
    // Chế độ khó
    if (isHard) {
        onButtonTexture.render(WINDOW_WIDTH/2 + 70, 250);
    }
    else {
        offButtonTexture.render(WINDOW_WIDTH/2 + 70, 250);
    }
    hardModeTexture.render(WINDOW_WIDTH/2 + 80 + onButtonTexture.getWidth(), 250);

    // Vẽ âm lượng
    volumeTexture.render(150, 350);
    volumeDownTexture.render(WINDOW_WIDTH/2 - 50, 350);
    int number = 50;
    string numberText = to_string(number);
    if (!volumeNumberTexture.loadFromRenderedText(numberText, TEXT_COLOR, font)) {
        cout << "Failed to load volume number texture!" << endl;
        return;
    }
    volumeNumberTexture.render(WINDOW_WIDTH/2, 350);
    volumeUpTexture.render(WINDOW_WIDTH/2 + 80, 350);

    // Vẽ nút play và nút quit lên màn hình
    playTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth() - 50, 520);
    quitTexture.render(WINDOW_WIDTH/2 + 50, 520);

    //  Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

/** Hàm vẽ thư mục BXH lên màn hình **/
void renderRanking()
{
    // Xóa toàn bộ màn hình
    SDL_RenderClear(renderer);

    // Vẽ background ranking
    ranking2Texture.render(0, 0);

    // Vẽ nút bật/tắt âm thanh lên màn hình
    if (isMute) {
        offMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }
    else {
        onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }

    // Vẽ nút home lên màn hình
    homeIconTexture.render(WINDOW_WIDTH - homeIconTexture.getWidth() - 10, homeIconTexture.getHeight() + 20);

    // Vẽ tên và điểm của top 5 players lên màn hình
    for (int i = 0; i < HighScores.size(); i++) {
        // Vẽ tên
        if (!playerTexture.loadFromRenderedText(HighScores[i].name, TEXT_COLOR, font)) {
            cout << "Failed to load player name texture!" << endl;
            return;
        }
        // Vẽ điểm
        playerTexture.render(150, 150 + i*60);
        if (!highScoreTexture.loadFromRenderedText(to_string(HighScores[i].score), TEXT_COLOR, font)) {
            cout << "Failed to load highscore texture!" << endl;
            return;
        }
        highScoreTexture.render(550, 150 + i*60);
    }

    // Vẽ nút play và nút quit lên màn hình
    playTexture.render(WINDOW_WIDTH/2 - playTexture.getWidth() - 50, 520);
    quitTexture.render(WINDOW_WIDTH/2 + 50, 520);

    //  Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

/** Hàm vẽ các ô của trò chơi lên màn hình **/
void renderButtons()
{
    // Đặt màu cho bộ vẽ
    SDL_SetRenderDrawColor(renderer, BUTTON_COLOR.r, BUTTON_COLOR.g, BUTTON_COLOR.b, BUTTON_COLOR.a);
    // Vẽ các nút bằng cách điền các hình vuông
    for (int i = 0; i < BUTTON_NUM; i++) {
        SDL_RenderFillRect(renderer, &buttons[i]);
    }
}

/** Hàm vẽ các thành phần của trò chơi (chính) lên màn hình **/
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

    // Vẽ nút bật/tắt âm thanh lên màn hình
    if (isMute) {
        offMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }
    else {
        onMusicTexture.render(WINDOW_WIDTH - onMusicTexture.getWidth() - 10, 10);
    }

    // Vẽ nút home lên màn hình
    homeIconTexture.render(WINDOW_WIDTH - homeIconTexture.getWidth() - 10, homeIconTexture.getHeight() + 20);

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

/** Hàm vẽ thư mục nhập tên nếu đạt high score **/
void renderHighScore()
{
    if (!enterNameTexture.loadFromRenderedText("ENTER YOUR NAME", TEXT_COLOR, font)) {
        cout << "Failed to load enter name texture!" << endl;
        return;
    }
    enterNameTexture.render(WINDOW_WIDTH/2 - enterNameTexture.getWidth()/2, 220);
    if (!nameOfPlayer.empty()) {
        if (!nameTexture.loadFromRenderedText(nameOfPlayer, TEXT_COLOR, font)) {
            cout << "Failed to load name texture!" << endl;
            return;
        }
        nameTexture.render(WINDOW_WIDTH/2 - nameTexture.getWidth()/2, WINDOW_HEIGHT/2);
    }
}

/** Hàm vẽ thư mục game over **/
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

    if(isHighScore) {
        renderHighScore();
    }
    else {
        homeTexture.render(x, WINDOW_HEIGHT/2 - homeTexture.getHeight());

        replayTexture.render(x, WINDOW_HEIGHT/2 + 50);

        quitTexture.render(x, WINDOW_HEIGHT/2 + 100 + replayTexture.getHeight());
    }

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
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    Mix_ResumeMusic();
                    Mix_Volume(-1, 64);
                }
                else {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    Mix_PauseMusic();
                    Mix_Volume(-1, 0);
                }
                isMute = !isMute;
            }
            if (isMenu) {
                int xGuide = WINDOW_WIDTH/2 - guideTexture.getWidth()/2;
                int yGuide = WINDOW_HEIGHT/2 - guideTexture.getHeight()/2;
                // Nếu nhấn nút play thì bắt đầu chạy game
                if (x >= xGuide && x <= xGuide + playTexture.getWidth() && y >= yGuide - BUTTON_GAP - playTexture.getHeight() && y <= yGuide - BUTTON_GAP) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    isMenu = false;
                }
                // Nếu nhấn nút guide thì hiển thị hướng dẫn
                else if (x >= xGuide && x <= xGuide + guideTexture.getWidth() && y >= yGuide && y <= yGuide + guideTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    isMenu = false;
                    isGuide = true;
                }
                else if (x >= xGuide && x <= xGuide + settingTexture.getWidth() && y >= yGuide + BUTTON_GAP + settingTexture.getHeight() && y <= yGuide + BUTTON_GAP + 2*settingTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    isSetting = true;
                    isMenu = false;
                }
                // Nếu nhấn nút ranking thì hiển thị BXH
                else if (x >= xGuide && x <= xGuide + rankingTexture.getWidth() && y >= yGuide + 2*BUTTON_GAP + 2*quitTexture.getHeight() && y <= yGuide + 2*BUTTON_GAP + 3*quitTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    isRanking = true;
                    readHS = true;
                    isMenu = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if (x >= xGuide && x <= xGuide + quitTexture.getWidth() && y >= yGuide + 3*BUTTON_GAP + 3*quitTexture.getHeight() && y <= yGuide + 3*BUTTON_GAP + 4*quitTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    running = false;
                }
            }
            else if (isGuide) {
                // Nếu nhấn nút play thì bắt đầu chạy game
                if (x >= WINDOW_WIDTH/2 - 50 - playTexture.getWidth() && x <= WINDOW_WIDTH/2 - 50 && y >= 520 && y <= 520 + playTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    isGuide = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if(x >= WINDOW_WIDTH/2 + 50 && x <= WINDOW_WIDTH/2 + 50 + quitTexture.getWidth() && y >= 520 && y <= 520 + quitTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    running = false;
                }
                // Kiểm tra xem chuột có nhấn vào nút home không
                else if (x >= WINDOW_WIDTH - homeIconTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 20 + homeIconTexture.getHeight() && y <= 20 + 2*homeIconTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    isMenu = true;
                    isGuide = false;
                }
            }
            else if (isSetting) {
                // Nếu nhấn nút play thì bắt đầu chạy game
                if (x >= WINDOW_WIDTH/2 - 50 - playTexture.getWidth() && x <= WINDOW_WIDTH/2 - 50 && y >= 520 && y <= 520 + playTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    isSetting = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if(x >= WINDOW_WIDTH/2 + 50 && x <= WINDOW_WIDTH/2 + 50 + quitTexture.getWidth() && y >= 520 && y <= 520 + quitTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    running = false;
                }
                // Kiểm tra xem chuột có nhấn vào nút home không
                else if (x >= WINDOW_WIDTH - homeIconTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 20 + homeIconTexture.getHeight() && y <= 20 + 2*homeIconTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    isMenu = true;
                    isSetting = false;
                }
            }
            else if (isRanking) {
                // Nếu nhấn nút play thì bắt đầu chạy game
                if (x >= WINDOW_WIDTH/2 - 50 - playTexture.getWidth() && x <= WINDOW_WIDTH/2 - 50 && y >= 520 && y <= 520 + playTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                    startTime = SDL_GetTicks();
                    isReset = true;
                    isRanking = false;
                }
                // Nếu nhấn nút quit thì thoát game mà không hiển thị điểm số
                else if(x >= WINDOW_WIDTH/2 + 50 && x <= WINDOW_WIDTH/2 + 50 + quitTexture.getWidth() && y >= 520 && y <= 520 + quitTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    running = false;
                }
                // Kiểm tra xem chuột có nhấn vào nút home không
                else if (x >= WINDOW_WIDTH - homeIconTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 20 + homeIconTexture.getHeight() && y <= 20 + 2*homeIconTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    isMenu = true;
                    isRanking = false;
                }
            }
            else if (gameOver) {
                int xReplay = WINDOW_WIDTH/2 - replayTexture.getWidth()/2;

                // Kiểm tra có phải high score không
                if (!isHighScore) {
                    // Nếu nhấn nút replay thì chạy lại game
                    if (x >= xReplay && x <= xReplay + replayTexture.getWidth() && y >= WINDOW_HEIGHT/2 + 50 && y <= WINDOW_HEIGHT/2 + 50 + replayTexture.getHeight()) {
                        // Đặt thời điểm bắt đầu hiển thị chuỗi là thời gian hiện tại
                        startTime = SDL_GetTicks();
                        isReset = true;
                        gameOver = false;
                    }
                    // Nếu nhấn nút quit thì thoát game
                    else if(x >= xReplay && x <= xReplay + quitTexture.getWidth() && y >= WINDOW_HEIGHT/2 + quitTexture.getHeight() + 100 && y <= WINDOW_HEIGHT/2 + 2*quitTexture.getHeight() + 100) {
                        // Phát âm thanh click
                        Mix_PlayChannel(-1, clickSound, 0);
                        running = false;
                    }
                    // Nếu nhấn nút home thì quay về trang chính
                    else if (x >= xReplay && x <= xReplay + replayTexture.getWidth() && y >= WINDOW_HEIGHT/2 - homeTexture.getHeight() && y <= WINDOW_HEIGHT/2) {
                        // Phát âm thanh click
                        Mix_PlayChannel(-1, clickSound, 0);
                        isMenu = true;
                        gameOver = false;
                    }
                }
            }
            else {
                // Kiểm tra xem chuột có nhấn vào nút home không
                if (x >= WINDOW_WIDTH - homeIconTexture.getWidth() - 10 && x <= WINDOW_WIDTH - 10 && y >= 20 + homeIconTexture.getHeight() && y <= 20 + 2*homeIconTexture.getHeight()) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);
                    isMenu = true;
                }

                if (!showSequence) {
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
                                // Kiểm tra có phải highscore không
                                isHighScore = hscores.is_high_score(score, HighScores);
                                // Đặt biến kết thúc trò chơi là true
                                gameOver = true;
                            }
                            break;
                        }
                    }
                }
            }
        }
        // Nếu nhấn phím
        else if (e.type == SDL_KEYDOWN) {
            if (isHighScore) {
                SDL_Keycode key = e.key.keysym.sym;

                // Nếu nhấn phím backspace thì xóa kí tự cuối cùng trong chuỗi
                if (key == SDLK_BACKSPACE) {
                    if (!nameOfPlayer.empty()) {
                        nameOfPlayer.pop_back();
                    }
                }
                // Nếu nhấn phím enter thì dừng nhập tên
                else if (key == SDLK_RETURN) {
                    // Lưu lại tên và điểm của người chơi vào file txt
                    hscores.write_high_scores(nameOfPlayer, score, HighScores);
                    isHighScore = false;
                }
            }
        }
        // Nếu nhập kí tự
        else if (e.type == SDL_TEXTINPUT) {
            if (isHighScore) {
                // Lấy kí tự nhập
                string input = e.text.text;

                // Thêm kí tự vào chuỗi
                nameOfPlayer += input;
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

    HighScores = hscores.read_high_scores();

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
            nameOfPlayer = "";

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
        else if (isRanking) {
            if (readHS) {
                HighScores = hscores.read_high_scores();
                readHS = false;
            }
            renderRanking();
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
