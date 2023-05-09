#include "Game.h"

int main(int argc, char* argv[])
{
    // Khởi tạo SDL và các thành phần liên quan
    if (!init()) {
        cout << "Failed to initialize SDL!" << endl;
        return -1;
    }
    else if(!loadMedia()) {
            cout << "Failed to load media!" << endl;
            return -1;
    }
    // Chạy trò chơi
    run();
    // Giải phóng các thành phần đã khởi tạo
    close();
    return 0;
}
