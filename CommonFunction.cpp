#include "CommonFunction.h"

bool init()
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

void close()
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

SDL_Texture* loadTexture(string path)
{
    // Biến lưu texture mới
    SDL_Texture* newTexture = nullptr;

    // Tải surface từ file ảnh
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    // Nếu tải surface không thành công thì in ra lỗi
    if (loadedSurface == nullptr)
    {
        cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        // Tạo texture từ surface đã tải
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        // Nếu tạo texture không thành công thì in ra lỗi
        if (newTexture == nullptr)
        {
            cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
        }

        // Giải phóng surface đã tải
        SDL_FreeSurface(loadedSurface);
    }

    //Trả về texture mới
    return newTexture;
}

Mix_Music* loadMusic(string path)
{
    // Biến lưu âm nhạc mới
    Mix_Music* newMusic = nullptr;

    // Tải âm nhạc từ file âm thanh
    newMusic = Mix_LoadMUS(path.c_str());
    // Nếu tải âm nhạc không thành công thì in ra lỗi
    if (newMusic == nullptr) {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    // Trả về âm nhạc mới
    return newMusic;
}

Mix_Chunk* loadSound(string path)
{
    // Biến lưu âm thanh hiệu ứng mới
    Mix_Chunk* newSound = nullptr;

    // Tải âm nhạc từ file âm thanh hiệu ứng
    newSound = Mix_LoadWAV(path.c_str());
    // Nếu tải âm thanh hiệu ứng không thành công thì in ra lỗi
    if (newSound == nullptr) {
        cout << "Failed to load sound! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    // Trả về âm thanh hiệu ứng mới
    return newSound;
}

bool loadMedia()
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

