#include "Project_Base.h"
#include "CommonFunction.h"
#include "SDL_Utils.h"

int main(int argc,char* args[])
{
    // Khởi tạo các thành phần của game
      if(!init()){
          std::cout<<"Failed to initialize!"<<std::endl;
      }
      else{
          // Tải các tài nguyên cho game
          if(!loadMedia()){
              std::cout<<"Failed to load media!"<<std::endl;
          }
          else{
              // Phát nhạc nền
              Mix_PlayMusic(music,-1);

              // Biến lưu thời gian bắt đầu vòng lặp
              Uint32 startTime=0;

              // Vòng lặp chính của game
              while(!quit){
                  // Lưu lại thời gian bắt đầu vòng lặp
                  startTime=SDL_GetTicks();

                  // Xử lý các sự kiện từ bàn phím và chuột
                  handleEvents();

                  // Cập nhật trạng thái của game
                  update();

                  // Vẽ các đối tượng lên màn hình
                  render();

                  // Giữ cho FPS ổn định
                  if(SDL_GetTicks()-startTime<1000/FPS){
                      SDL_Delay(1000/FPS-(SDL_GetTicks()-startTime));
                  }
              }
          }
      }

      // Giải phóng các tài nguyên và thoát game
      close();

      return 0;
}
