#include "CommonFunction.h"
#include "ImageObjectBase.h"
#include "ImpTimer.h"
#include "Base.h"
#include "Bird.h"

ImageObjectBase g_background;
Base g_base;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("theGame",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.loadImg("image//background.png", g_screen);
    if (!ret) return false;
    return true;

}


bool LoadBase()
{
    bool ret = g_base.LoadImg("image//base.png", g_screen);
    if (!ret) return false;
    return true;

}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}




int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;
    if (LoadBase() == false)
    return -1;

    Bird p_bird;
    p_bird.loadImg("image//bird.png", g_screen);
    p_bird.set_clips();

    bool  is_quit = false;
    while (!is_quit)
    {
        fps_timer.start();

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_bird.HandelInputAction(g_event, g_screen);

        }


        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        g_base.Show(g_screen);

        p_bird.DoBird();
        p_bird.Show(g_screen);

        SDL_RenderPresent(g_screen);


        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
                SDL_Delay(delay_time);
        }

    }


    return 0;

}
