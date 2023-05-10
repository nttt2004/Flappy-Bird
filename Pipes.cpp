
#include "Pipes.h"

Pipes::Pipes()
{
 //bool passed = false;

}

Pipes::~Pipes()
{

}

bool Pipes::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = loadImg(path, screen);
    return ret;
}

//void Pipes::createPipe(SDL_Renderer* des)

//void Pipes::updatePipe(SDL_Renderer* des)

void Pipes::initPipe()
{
    for(int i=0; i<NUM_PIPES; i++){
        gPipes[i][0] = i*PIPE_DISTANCE + SCREEN_WIDTH;
        gPipes[i][1] = rand()%(PIPE_MaxHeight-PIPE_MinHeight)+PIPE_MinHeight;
    }
}


//bool Pipes::CheckCollision(int birdX, int birdY)

/*
bool Pipes::CheckCollision(SDL_Rect birdRect, SDL_Rect pipeRect)
{
    if(birdRect.x <= pipeRect.x+pipeRect.w && pipeRect.x <= birdRect.x+birdRect.w && birdRect.y <= pipeRect.y +pipeRect.h && pipeRect.y <= birdRect.y + birdRect.h){
        return true;
    }
    return false;

}
*/
void Pipes::GetRectSlot()
{
    for(int i=0; i<NUM_PIPES; i++){
     slot_rect_.x = gPipes[i][0] + PIPE_WIDTH;
     slot_rect_.y = gPipes[i][1];
     slot_rect_.w = 5;
     slot_rect_.h = PIPE_GAP;
    }
}
/*
bool Pipes::CheckCol(SDL_Rect birdRect, SDL_Rect pipeRect)
{
}
*/

bool Pipes::CheckPass(SDL_Rect birdrect)
{
    for(int i=0; i<NUM_PIPES; i++){
      if(SDLCommonFunc::CheckCollision(birdrect, slot_rect_))
        return true;
      return false;
    }
}

bool Pipes::isGameOver(SDL_Rect birdRect)
{
    //birdRect = bird->GetRect();
    for(int i=0; i<NUM_PIPES; i++){
      SDL_Rect pipeNorth_rect = {gPipes[i][0], gPipes[i][1]-PIPE_HEIGHT, PIPE_WIDTH, PIPE_HEIGHT};
      SDL_Rect pipeSouth_rect = {gPipes[i][0], gPipes[i][1]+PIPE_GAP, PIPE_WIDTH, PIPE_HEIGHT};
      if(SDLCommonFunc::CheckCollision(birdRect, pipeNorth_rect)||SDLCommonFunc::CheckCollision(birdRect, pipeSouth_rect))
        return true;
    }
    if(birdRect.y + birdRect.h < 0 || birdRect.y + birdRect.h > SCREEN_HEIGHT - 40)
        return true;
    return false;
}

/*
int GetScore(SDL_Rect birdRect, int& score)
{
    if(!(Pipes::isGameOver(birdRect)) && Pipes::CheckPass(birdRect))
        score++;

}

void Pipes::Render(SDL_Renderer* screen)
{
    for (int i = 0; i < NUM_PIPES; i++)
    {

   }
}
*/


void Pipes::Show(SDL_Renderer* des, SDL_Rect birdRect)
{
        /*
        pipeNorth.x = SCREEN_WIDTH;
        pipeNorth.y = 0;
        pipeNorth.w = PIPE_WIDTH;
        pipeNorth.h = rand()%(PIPE_MaxHeight - PIPE_MinHeight + 1)+PIPE_MinHeight;

        pipeSouth.x = SCREEN_WIDTH;
        pipeSouth.y = pipeNorth.h + PIPE_GAP;
        pipeSouth.w = PIPE_WIDTH;
        pipeSouth.h = SCREEN_HEIGHT - pipeSouth.y;

        gPipes.push_back(pipeNorth);
        gPipes.push_back(pipeSouth);
        */

    //di chuyen ong sang trai
    for(int i=0; i<NUM_PIPES; i++){
         gPipes[i][0] -= PIPE_SPEED;
    }
    //xoa ong
    if(gPipes[0][0] < -PIPE_WIDTH){
       for (int i = 1; i < NUM_PIPES ; i++) {
         gPipes[i - 1][0] = gPipes[i][0];
         gPipes[i - 1][1] = gPipes[i][1];
        }
      //gPipes[NUM_PIPES - 1][0] = gPipes[NUM_PIPES - 2][0] + PIPE_WIDTH + PIPE_DISTANCE;
      //gPipes[NUM_PIPES - 1][1] = rand() % (SCREEN_HEIGHT - PIPE_GAP- PIPE_MinHeight) + PIPE_MinHeight;
      gPipes[NUM_PIPES - 1][0] = 530 + 100 + PIPE_WIDTH + PIPE_DISTANCE;
      gPipes[NUM_PIPES - 1][1] = rand()%(PIPE_MaxHeight-PIPE_MinHeight)+PIPE_MinHeight;
    }
    for(int i=0; i<NUM_PIPES; i++){
        SDL_Rect pipeNorth_rect = {gPipes[i][0], gPipes[i][1]-PIPE_HEIGHT, PIPE_WIDTH, PIPE_HEIGHT};
        SDL_Rect pipeSouth_rect = {gPipes[i][0], gPipes[i][1]+PIPE_GAP, PIPE_WIDTH, PIPE_HEIGHT};
        SDL_RenderCopy(des, p_object_, NULL, &pipeNorth_rect);
        SDL_RenderCopy(des, p_object_, NULL, &pipeSouth_rect);
    }

    for(int i=0; i<NUM_PIPES; i++)
    {
        bool isCol = Pipes::isGameOver(birdRect);
            if (isCol == true)
            {
                Mix_Chunk* beep_sound = Mix_LoadWAV("audio//game_over.wav");
                if (beep_sound != NULL)
                    Mix_PlayChannel(-1, beep_sound, 0);
                break;
            }

        bool ret = CheckPass(birdRect);
            if (ret == true)
            {
                Mix_Chunk* beep_sound = Mix_LoadWAV("audio//point.wav");
                if (beep_sound != NULL)
                    Mix_PlayChannel(-1, beep_sound, 0);
                //m_count++;

            }
    }

}

