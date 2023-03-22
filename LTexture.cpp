#include "LTexture.h"

// Hàm khởi tạo
LTexture::LTexture()
{
	p_Texture = nullptr;

	p_Width = 0;
	p_Height = 0;
}

// Hàm hủy
LTexture::~LTexture()
{
	free();
}

// Hàm giải phóng texture
void LTexture::free()
{
	if (p_Texture != nullptr)
	{
		p_Texture = nullptr;
		p_Width = 0;
		p_Height = 0;
	}
}

// Hàm tải texture từ file
bool LTexture::loadFromFile(string path)
{
	// Giải phóng texture cũ nếu có
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	// Tạo surface từ file ảnh
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == nullptr)
	{
		cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));

		// Tạo texture từ surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == nullptr)
		{
			cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			// Lấy kích thước của texture
			p_Width = loadedSurface->w;
			p_Height = loadedSurface->h;
		}

		// Giải phóng surface
		SDL_FreeSurface(loadedSurface);
	}

	// Tra về kết quả
	p_Texture = newTexture;
	return p_Texture != nullptr;
}

// Hàm tạo texture từ chuỗi văn bản
bool LTexture::loadFromRenderedText(std::string text, SDL_Color color) {
    // Giải phóng texture cũ nếu có
    free();

    // Biến lưu kết quả trả về
    bool success=true;

    // Tạo surface từ chuỗi văn bản và font chữ
    SDL_Surface* textSurface=TTF_RenderText_Solid(font, text.c_str(), color);
    if(textSurface == nullptr){
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else{
        // Tạo texture từ surface
        p_Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(p_Texture == nullptr){
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else{
            // Lấy kích thước của texture
            p_Width = textSurface->w;
            p_Height = textSurface->h;
        }

        // Giải phóng surface
        SDL_FreeSurface(textSurface);
    }

    return success;
}

// Hàm render texture lên màn hình
void LTexture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, p_Width, p_Height};

	// Render texture lên màn hình
	SDL_RenderCopy(renderer, p_Texture, nullptr, &renderQuad);
}

// Hàm lấy chiều rộng của texture
int LTexture::getWidth()
{
	return p_Width;
}

// Hàm lấy chiều cao của texture
int LTexture::getHeight()
{
	return p_Height;
}
