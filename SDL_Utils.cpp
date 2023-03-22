#include "SDL_Utils.h"

void handleEvents()
{
    // Biến lưu sự kiện
    SDL_Event e;

    // Lặp qua hàng đợi các sự kiện
    while(SDL_PollEvent(&e)!=0)
    {
    // Nếu nhấn nút thoát cửa sổ thì thoát game
        if(e.type==SDL_QUIT)
        {
            quit=true;
        }

        // Nếu nhấn phím space thì bắn đạn
        if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_SPACE)
        {
            ship.shoot();
        }
    }
}

// Hàm cập nhật trạng thái của game
void update()
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
            meteorites.erase(meteorites.begin()+i);
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
    static int timer=0;
    timer++;
    if(timer==FPS*2)
    {
        timer=0;
        Meteorite* meteorite = new Meteorite();
        meteorites.push_back(meteorite);
    }
}

// Hàm vẽ các đối tượng lên màn hình
void render(){
    // Xóa màn hình
    SDL_RenderClear(renderer);

    // Vẽ background texture
    backgroundTexture.render(0,0);

    // Vẽ các đạn
    for(int i=0;i<bullets.size();i++){
        bullets[i]->render();
    }

    // Vẽ các thiên thạch
    for(int i=0;i<meteorites.size();i++){
        meteorites[i]->render();
    }

    // Vẽ tàu nếu còn sống
    if(ship.isAlive()){
        ship.render();
    }

    // Tạo texture cho điểm số và vẽ lên màn hình
    LTexture scoreTexture;
    SDL_Color scoreColor={255,255,255};
    string scoreText = "Score: " + to_string(score);
    if(!scoreTexture.loadFromRenderedText(scoreText,scoreColor)){
        cout << "Failed to render score texture!" << endl;
    }
    else{
        scoreTexture.render(10,10);
        scoreTexture.free();
    }

    // Nếu tàu chết thì vẽ game over texture lên màn hình
    if(!ship.isAlive()){
        gameOverTexture.render((SCREEN_WIDTH-gameOverTexture.getWidth())/2,(SCREEN_HEIGHT-gameOverTexture.getHeight())/2);
    }

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

