#include "CommonFunction.h"
#include "ImageObjectBase.h"
#include "ImpTimer.h"
#include "Base.h"
#include "Bird.h"
#include "Pipes.h"
#include "Power.h"
#include "TextObject.h"
#include "Menu.h"

ImageObjectBase g_background;
ImageObjectBase ready_background;

Base g_base;
Pipes g_pipes;
//Power g_power;
//Menu g_menu;

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_MENU = NULL;

//Mix_Chunk* g_music = NULL;
Mix_Music* g_music = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("FLAPPY BIRD",
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
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);//tăng tốc độ vẽ
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        // Init text ttf
        if (TTF_Init() == -1)
            success = false;

        g_font_text = TTF_OpenFont("font//DlxFont.ttf", 30);
        if (g_font_text == NULL)
            success = false;

        g_font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
        if (g_font_MENU == NULL)
        {
            return false;
        }

        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1)
            success = false;

        //Init audio

        /*

        g_sound_bullet[0] = Mix_LoadWAV("audio//flap.wav");
        g_sound_bullet[1] = Mix_LoadWAV("audio//point.wav");

        g_sound_exp[0] = Mix_LoadWAV("audio//game_over.wav");
        if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL||g_sound_exp[0] == NULL)
        {
            return false;
        }
        */
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.loadImg("image//background01.jpg", g_screen);
    if (!ret) return false;
    return true;
}

bool LoadReadyBackground()
{
    bool ret = ready_background.loadImg("image//get_ready.png", g_screen);
    if(!ret) return false;
    return true;
}

bool LoadBase()
{
    bool ret = g_base.LoadImg("image//base.png", g_screen);
    if (!ret) return false;
    return true;

}

bool LoadPipe()
{
    bool ret = g_pipes.LoadImg("image//pipe.png", g_screen);
    if (!ret) return false;
    return true;

}

bool LoadMusic()
{
    bool success = true;

    /*g_music = Mix_LoadWAV("audio//chiptune-grooving-142242.wav");
    if (g_music == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }else
        Mix_PlayChannel(-1, g_music, 0);*/
        g_music = Mix_LoadMUS("audio//chiptune-grooving-142242.mp3");
    if (g_music == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

void close()
{
    g_background.Free();
    g_base.Free();
    g_pipes.Free();
    //g_power.Free();

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

    int score = 0;//tam

    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;
    if(LoadReadyBackground() == false)
        return -1;
    if (LoadBase() == false)
        return -1;
    if(LoadPipe() == false)
        return -1;
    //if(LoadPower() == false)
        //return -1;
    if(LoadMusic() == false)
        return -1;

    bool  is_quit = false;
    Mix_PlayMusic(g_music, -1);
    //Make menu game
    int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Play Game", "Exit", "image//background05.png");
    if (ret_menu == 1)
        is_quit = true;
   // bool ready = false;
again_label:
    TextObject score_game;
    score_game.SetColor(TextObject::WHITE_TEXT);
    Uint32 score_value = 0;

    Bird p_bird;
    p_bird.loadImg("image//bird.png", g_screen);
    p_bird.set_clips();

    g_pipes.initPipe();
    if(Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }


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

        //g_power.Show(g_screen);

        //g_pipes.createPipe(g_screen);
        //g_pipes.updatePipe(g_screen);
        g_pipes.Show(g_screen, p_bird.GetRectFrame());
        //g_pipes.Render(g_screen);

        //g_pipes.CheckPass(p_bird.GetRectFrame());


        //g_pipes.CheckCollision(p_bird.GetRect(), g_pipes.GetRect());



        if(g_pipes.CheckPass(p_bird.GetRectFrame()))
        {
            score_value++;
        }
        bool game_over = g_pipes.isGameOver(p_bird.GetRectFrame());
        if(game_over == true)
        {
            SDL_Delay(500);
            Mix_PauseMusic();
            int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU,
                                                   "YES", "NO",
                                                    "image//game_over01.png");

            if (ret_menu == 1)
            {
                is_quit = true;
                continue;
            }

            else
            {
                is_quit = false;
                //g_pipes.Free();
                goto again_label;
            }

        }

        //Show game time
        /*
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks()/1000; //giay
        Uint32 val_time = 300 - time_val;
        if(val_time <= 0)
        {
            //if(MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_INCONSTOP) == IDOK)
            //{
                is_quit = true;
                break;
            //}
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(g_font_text, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
        }
        */

        std::string val_str_score = std::to_string(score_value);
        std::string strScore("");
        strScore += val_str_score;

        score_game.SetText(strScore);
        score_game.LoadFromRenderText(g_font_text, g_screen);
        score_game.RenderText(g_screen, SCREEN_WIDTH*0.5-15, 15);


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
