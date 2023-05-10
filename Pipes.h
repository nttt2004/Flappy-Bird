
#ifndef PIPES_H_
#define PIPES_H_

#include "CommonFunction.h"
#include "ImageObjectBase.h"
#include "Bird.h"

#define PIPE_WIDTH 52
#define PIPE_HEIGHT  320
#define PIPE_GAP 160
#define PIPE_DISTANCE  300
#define PIPE_SPEED 6
#define NUM_PIPES 3
#define PIPE_MinHeight 100
#define PIPE_MaxHeight 300

class Pipes : public ImageObjectBase
{
public:
  Pipes();
  ~Pipes();

  bool LoadImg(std::string path, SDL_Renderer* screen);
  void Show(SDL_Renderer* des, SDL_Rect birdRect);
 // bool CheckCol(SDL_Rect birdRect, SDL_Rect pipeRect);
  bool CheckPass(SDL_Rect rect);
  void GetRectSlot();

  bool isGameOver(SDL_Rect birdRect);

  int gPipes[NUM_PIPES][2];
  void initPipe();
  SDL_Rect GetRect() const { return rect_; }
  //void Render(SDL_Renderer screen);
  //int GetScore(SDL_Rect birdRect, int& score);
  //int score;
private:
    //int score;
   //SDL_Rect pipeNorth;
   //SDL_Rect pipeSouth;
   //Bird* bird;
   SDL_Rect slot_rect_;
   //bool passed;

};


#endif // PIPES_H_


