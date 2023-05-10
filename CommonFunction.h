
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
#include "ImageObjectBase.h"
#include "TextObject.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


//Screen
const int FRAME_PER_SECOND = 30; // fps
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 512;

const int RENDER_DRAW_COLOR = 0xff;

//#define NUM_OF_MENU_OPTIONS 2

typedef struct Input
{
    int jump_;
};

namespace SDLCommonFunc{
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
  int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
                            const std::string& menu1,
                            const std::string& menu2,
                            const std::string& img_name);

}


#endif // COMMON_FUNCTION_H_
