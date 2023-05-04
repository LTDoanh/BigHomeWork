#include "Game.h"

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
