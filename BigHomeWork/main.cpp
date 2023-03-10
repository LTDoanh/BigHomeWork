#include "SDL_utils.h"
#include "MainObject.h"

int main(int argc, char* argv[])
{
    if(!Init()) {
        cout << "Khoi tao SDL that bai\n";
        return 0;
    }

    gBackground = LoadImage("Background.jpg");
    if (gBackground == nullptr) {
        cout << "Load BackGround that bai\n";
        return 0;
    }

    ApplySurface(gBackground, gScreen, 0, 0);

    MainObject wingsObject;
    wingsObject.SetRect(300, 300);
    bool mainCheck = wingsObject.LoadImg("X-Wings2.png");
    if(!mainCheck){
        cout << "Load tau that bai";
        return 0;
    }

    wingsObject.Show(gScreen);

    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    Clean();
    SDL_Quit();
    return 1;
}
