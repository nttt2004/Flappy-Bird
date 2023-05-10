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
ImageObjectBase menu_background;

Base g_base;
Pipes g_pipes;
Power g_power;
Menu g_menu;

TTF_Font* g_font_text = NULL;
Mix_Chunk* g_music = NULL;

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

        g_font_text = TTF_OpenFont("font//DlxFont.ttf", 15);
        if (g_font_text == NULL)
            success = false;

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
bool LoadMenuBackground()
{
    bool ret = menu_background.loadImg("image//background03.jpg", g_screen);
    if (!ret) return false;
    return true;
}

bool LoadBase()
{
    bool ret = g_base.LoadImg("image//base.png", g_screen);
    if (!ret) return false;
    return true;

}

bool LoadPipeNorth()
{
    bool ret = g_pipes.LoadImg("image//pipe.png", g_screen);
    if (!ret) return false;
    return true;

}

bool LoadPipeSouth()
{
    bool ret = g_pipes.LoadImg("image//pipe.png", g_screen);
    if (!ret) return false;
    return true;

}

bool LoadLogo()
{
    bool ret = g_menu.LoadImg("image//Logo.png", g_screen);
    if (!ret) return false;
    return true;
}
bool LoadPlayButton()
{
    bool ret = g_menu.LoadImg("image//start_game.png", g_screen);
    if (!ret) return false;
    return true;
}
bool LoadExitButton()
{
    bool ret = g_menu.LoadImg("image//exit_game.png", g_screen);
    if (!ret) return false;
    return true;
}

bool LoadPower()
{
    bool ret = g_power.LoadImg("image//Power.png", g_screen);
    if(!ret) return false;
    return true;
}

bool LoadMusic()
{
    bool success = true;

    g_music = Mix_LoadWAV("audio//chiptune-grooving-142242.wav");
    if (g_music == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }else
        Mix_PlayChannel(-1, g_music, 0);
    return success;
}

void close()
{
    g_background.Free();
    g_base.Free();
    g_pipes.Free();
    g_power.Free();

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
    if (LoadBase() == false)
        return -1;

    if(LoadPipeNorth() == false)
        return -1;
    if(LoadPipeSouth() == false)
        return -1;
    if(LoadPower() == false)
        return -1;
    if(LoadMusic() == false)
        return -1;
    if(LoadMenuBackground() == false)
        return -1;
    if(LoadLogo() == false)
        return -1;
    if(LoadPlayButton() == false)
        return -1;
    if(LoadExitButton() == false)
        return -1;

    Bird p_bird;
    p_bird.loadImg("image//bird.png", g_screen);
    p_bird.set_clips();

    g_pipes.initPipe();
    //SDL_Rect bird={p_bird->x_pos_; p_bird->y_pos_;BIRD_HEIGHT;BIRD_WIDTH};
    //SDL_Rect pipe={}
    /*
    //show mark value
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);
    */
    TextObject score_game;
    score_game.SetColor(TextObject::WHITE_TEXT);
    Uint32 score_value = 0;

    //////////////////////////////////////////////////////////////////////
    //Start menu 1
    bool quit_menu = false;
    bool  is_quit = false;
   // menu_background.LoadImg("image//background04.png", g_screen);
    while(!quit_menu)
    {
        //bool quit_game = false;
        menu_background.Render(g_screen);
        while(SDL_PollEvent(&g_event) != 0)
        {
            quit_menu = true;
            menu_background.Free();
            g_menu.Free();

            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
                //play_again = false;
            }
            else
            {
                g_menu.handleEvent(g_event, g_screen);
            }
        }
          SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
          SDL_RenderClear(g_screen);

          menu_background.Render(g_screen, NULL);
          g_menu.Show(g_screen);
          SDL_RenderPresent(g_screen);
          SDL_Delay(1000);


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
        if(g_pipes.isGameOver(p_bird.GetRectFrame())){
             std::cout<<"Game Over";
             //close();
             //return 0;
         }



        //tam
        /*
         if(g_pipes.isGameOver(p_bird.GetRectFrame())){
            //stop();
            //std::cout<< g_pipes.GetScore(p_bird.GetRectFrame(), score)<<std::endl;
            //std::cout<<score<<std::endl;
            std::cout << "Game Over";
            close();
            //return 0;
         }
         */
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
        score_game.RenderText(g_screen, 450, 15);


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
