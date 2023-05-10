
#ifndef BIRD_H_
#define BIRD_H_

#define BIRD_WIDTH 92
#define BIRD_HEIGHT 64
#define BIRD_JUMP_VEL_Y 10
#define BIRD_MAX_VEL_Y 10

#include "CommonFunction.h"
#include "ImageObjectBase.h"

class Bird : public ImageObjectBase
{
public:
    Bird();
    ~Bird();

    virtual bool loadImg(std::string path, SDL_Renderer* screen); // cuong hoa
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();

    void DoBird();
    SDL_Rect GetRectFrame();

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[3];
    int frame_;

    Input input_type_; //jump
};


#endif // BIRD_H_
