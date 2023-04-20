#include "Game.h"

/** Hàm khởi tạo các thành phần cơ bản của SDL **/
bool Game::init()
{
    // Biến lưu kết quả trả về
    bool success = true;

    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        // Tạo window với tiêu đề và kích thước cho trước
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) // Nếu tạo window không thành công thì in ra lỗi
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else {
            //Tạo renderer cho window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) // Nếu tạo renderer không thành công thì in ra lỗi
            {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                // Khởi tạo IMG để load file ảnh png và jpg
                int imgFlags = IMG_INIT_PNG || IMG_INIT_JPG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }

                // Khởi tạo âm thanh với tần số lấy mẫu, định dạng âm thanh, số kênh và kích thước đệm cho trước
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
                    success = false;
                }

                // Khởi tạo font chữ
                if (TTF_Init() == -1)
                {
                    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

/** Hàm tải các tài nguyên cho game **/
bool Game::loadMedia()
{
    // Biến lưu kết quả trả về
    bool success = true;

    // Tải background texture
    if (!backgroundTexture.loadFromFile("background.jpg"))
    {
        cout << "Failed to load background texture!" << endl;
        success = false;
    }

    // Tải ship texture
    if (!shipTexture.loadFromFile("ship.png"))
    {
        cout << "Failed to load ship texture!" << endl;
        success = false;
    }

    // Tải meteorite texture
    if(!meteoriteTexture.loadFromFile("meteorite.png"))
    {
        cout << "Failed to load meteorite texture!" << endl;
        success = false;
    }

    // Tải bullet texture
    if(!bulletTexture.loadFromFile("bullet.png"))
    {
        cout << "Failed to load bullet texture!" << endl;
        success = false;
    }

    // Tải game over texture
    if(!gameOverTexture.loadFromFile("gameover.png"))
    {
        cout << "Failed to load game over texture!" << endl;
        success = false;
    }

    // Tải font chữ
    font = TTF_OpenFont("font.ttf",28);
    if(font == nullptr)
    {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }

    // Tải nhạc nền
    music = Mix_LoadMUS("music.mp3");
    if(music == nullptr)
    {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // Tải âm thanh bắn đạn
    shoot_sound = Mix_LoadWAV("shoot.wav");
    if(shoot_sound == nullptr)
    {
        cout << "Failed to load shoot sound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // Tải âm thanh nổ thiên thạch
    explode_sound = Mix_LoadWAV("explode.wav");
    if(explode_sound == nullptr)
    {
        cout << "Failed to load explode sound! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    return success;
}

/** Hàm giải phóng các thành phần cơ bản của SDL **/
void Game::close()
{
    // Giải phóng các texture đã tải
    backgroundTexture.free();
    shipTexture.free();
    meteoriteTexture.free();
    bulletTexture.free();
    gameOverTexture.free();

    // Giải phóng các đối tượng trong vector meteorites
    for (int i = 0; i < meteorites.size(); i++) {
        delete meteorites[i];
    }
    meteorites.clear();

    // Giải phóng các đối tượng trong vector bullets
    for (int i = 0; i < bullets.size(); i++)
    {
        delete bullets[i];
    }
    bullets.clear();

    // Giải phóng các âm thanh đã tải
    Mix_FreeMusic(music);
    music = nullptr;

    Mix_FreeChunk(shoot_sound);
    shoot_sound = nullptr;

    Mix_FreeChunk(explode_sound);
    explode_sound = nullptr;

    // Giải phóng font chữ đã tải
    TTF_CloseFont(font);
    font = nullptr;

    // Giải phóng renderer và window
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;

    // Thoát các thành phần của SDL
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

/** Hàm cập nhật trạng thái của game **/
void Game::update()
{
    // Cập nhật trạng thái của tàu
    ship.update();

    // Cập nhật trạng thái của các đạn
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i]->update();
        // Nếu đạn chết thì xóa khỏi vector và giải phóng bộ nhớ
        if (!bullets[i]->isAlive())
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }

    // Cập nhật trạng thái của các thiên thạch
    for(int i = 0; i < meteorites.size(); i++)
    {
        meteorites[i]->update();
        // Nếu thiên thạch chết thì xóa khỏi vector và giải phóng bộ nhớ
        if(!meteorites[i]->isAlive())
        {
            delete meteorites[i];
            meteorites.erase(meteorites.begin() + i);
            i--;
        }
    }

    // Kiểm tra va chạm giữa các đạn và thiên thạch
    for(int i = 0; i < bullets.size(); i++)
    {
        for(int j = 0; j < meteorites.size(); j++)
        {
            if(meteorites[j]->checkCollision(bullets[i]->getX(), bullets[i]->getY()))
            {
                // Thiết lập trạng thái sống cho đạn và thiên thạch là false
                bullets[i]->setAlive(false);
                meteorites[j]->setAlive(false);

                // Tăng điểm số lên 1
                score++;

                // Phát âm thanh nổ thiên thạch
                Mix_PlayChannel(-1,explode_sound,0);
            }
        }
    }

    // Kiểm tra va chạm giữa tàu và thiên thạch
    for(int i = 0; i < meteorites.size();i++)
    {
        if(ship.checkCollision(meteorites[i]->getX(), meteorites[i]->getY()))
        {
            // Thiết lập trạng thái sống cho tàu là false
            ship.setAlive(false);

            // Phát âm thanh nổ thiên thạch
            Mix_PlayChannel(-1,explode_sound,0);
        }
    }

    // Tạo một thiên thạch mới sau mỗi 2 giây
    static int timer = 0;
    timer++;
    if(timer == FPS*2)
    {
        timer=0;
        Meteorite* meteorite = new Meteorite();
        meteorites.push_back(meteorite);
    }
}

/** Hàm xử lí sự kiện **/
void Game::handleEvents()
{
    // Biến lưu sự kiện
    SDL_Event e;

    // Lặp qua hàng đợi các sự kiện
    while(SDL_PollEvent(&e) != 0)
    {
    // Nếu nhấn nút thoát cửa sổ thì thoát game
        if(e.type == SDL_QUIT)
        {
            quit = true;
        }

        // Nếu nhấn phím space thì bắn đạn
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
        {
            ship.shoot();
        }
    }
}

/** Hàm vẽ các đối tượng lên màn hình **/
void render(){
    // Xóa màn hình
    SDL_RenderClear(renderer);

    // Vẽ background texture
    backgroundTexture.render(0,0);

    // Vẽ các đạn
    for(int i = 0; i < bullets.size(); i++){
        bullets[i]->render();
    }

    // Vẽ các thiên thạch
    for(int i = 0; i < meteorites.size(); i++){
        meteorites[i]->render();
    }

    // Vẽ tàu nếu còn sống
    if(ship.isAlive()){
        ship.render();
    }

    // Tạo texture cho điểm số và vẽ lên màn hình
    LTexture scoreTexture;
    SDL_Color scoreColor = {255, 255, 255};
    string scoreText = "Score: " + to_string(score);
    if(!scoreTexture.loadFromRenderedText(scoreText, scoreColor, font))
    {
        cout << "Failed to render score texture!" << endl;
    }
    else
    {
        scoreTexture.render(10, 10);
        scoreTexture.free();
    }

    // Nếu tàu chết thì vẽ game over texture lên màn hình
    if(!ship.isAlive()){
        gameOverTexture.render((SCREEN_WIDTH - gameOverTexture.getWidth()) / 2, (SCREEN_HEIGHT-gameOverTexture.getHeight()) / 2);
    }

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}
