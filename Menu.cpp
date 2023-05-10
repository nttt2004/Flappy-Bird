#include "Menu.h"
//Button
Menu::Menu()
{
   bPos.x = 0;
   bPos.y = 0;
}
Menu::~Menu()
{

}

void Menu::setPosition(int x, int y)
{
    bPos.x = x;
    bPos.y = y;
}

bool Menu::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageObjectBase::loadImg(path, screen);
    if(ret)
    {
        button_height_ = rect_.h;
        button_width_ = rect_.w / 2;
    }
    return ret;
}

int Menu::handleEvent(SDL_Event event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_p:
        {
            //input_type_.play_ = 1;
            return 1;
        }
        break;
        case SDLK_e:
        {
            //input_type_.exit_ = 0;
            return 0;
        }
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_p:
        {
            //input_type_.jump_ = 0;
            return 0;
        }
        break;
        case SDLK_e:
        {
            //input_type_.exit_ = 0;
            return 0;
        }
        default:
            break;
        }
    }
}

void Menu::ShowButton(SDL_Renderer* screen)
{
    //Show current button sprite
   // SDL_Rect* current_clip = &button_clip[mCurrentSprite];
    SDL_Rect renderQuad = { bPos.x, bPos.y, button_width_, button_height_ };
    SDL_RenderCopy(screen, p_object_, NULL, &renderQuad);
}


