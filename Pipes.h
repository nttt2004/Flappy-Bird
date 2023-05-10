
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
  bool CheckPass(SDL_Rect rect);
  bool isGameOver(SDL_Rect birdRect);

  int gPipes[NUM_PIPES][2];
  void initPipe();
  SDL_Rect GetRect() const { return rect_; }

private:
   SDL_Rect slot_rect_;
};


#endif // PIPES_H_


