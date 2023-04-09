
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND = 25; // fps
const int SCREEN_WIDTH = 288;
const int SCREEN_HEIGHT = 512;

const int RENDER_DRAW_COLOR = 0xff;

#define NUM_OF_MENU_OPTIONS 2

typedef struct Input
{
    int jump_;
};



#endif // COMMON_FUNCTION_H_
