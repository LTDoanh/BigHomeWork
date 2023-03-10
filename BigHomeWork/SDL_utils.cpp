#include "SDL_utils.h"


/**Hàm khởi tạo SDL**/
bool Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == nullptr )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ){
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				else{
                    //Get window surface
                    gScreen = SDL_GetWindowSurface( gWindow );
                }
			}
		}
	}

	return success;
}

/**Hàm load image từ file**/
SDL_Surface* LoadImage(string file_name)
{
    //The final optimized image
    SDL_Surface* optimizedImage = nullptr;

    //Load image at specified path
    SDL_Surface* loadedImage = IMG_Load( file_name.c_str() );
    if( loadedImage == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", file_name.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedImage = SDL_ConvertSurface( loadedImage, gScreen->format, 0 );
        if( optimizedImage == nullptr )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", file_name.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

/**Hàm đưa các image đã load vào màn hình**/
void ApplySurface(SDL_Surface* src, SDL_Surface* dst, int x, int y)
{
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    SDL_BlitSurface(src, nullptr, dst, &dstrect);
}

/**Hàm giải phóng các đối tượng biến global**/
void Clean()
{
    SDL_FreeSurface(gScreen);
    gScreen = nullptr;
    SDL_FreeSurface(gBackground);
    gBackground = nullptr;

    //
    SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
