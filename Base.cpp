
#include "Base.h"

Base::Base()
{
    gBaseX = 0;
    gBaseY = SCREEN_HEIGHT - BASE_HEIGHT;
}

Base::~Base()
{

}

bool Base::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = loadImg(path, screen);
    return ret;
}

void Base::Show(SDL_Renderer* des)
{
    SDL_Rect base_rect = {gBaseX, gBaseY, SCREEN_WIDTH, BASE_HEIGHT};
    SDL_RenderCopy(des, p_object_, NULL, &base_rect);
}
