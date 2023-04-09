
#include "Bird.h"

Bird::Bird()
{
    frame_ = 0;
    x_pos_ = SCREEN_WIDTH / 4;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
}

Bird::~Bird()
{


}

bool Bird::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = ImageObjectBase::loadImg(path, screen);
    if (ret==true)
    {
        width_frame_ = rect_.w / 3;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Bird::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {

        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = width_frame_ * 2;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;
    }
}

void Bird::Show(SDL_Renderer* des)
{
    frame_ ++;
    if (frame_ >= 3) frame_ = 0;
    rect_.x = x_pos_;
    rect_.y = y_pos_;


    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);



}

void Bird::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_SPACE:
        {
            input_type_.jump_ = 1;

        }
        break;

        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_SPACE:
        {
            input_type_.jump_ = 0;

        }
        break;
        default:
            break;
        }
    }
}

void Bird::DoBird()
{
    x_val_ = 0;
    y_val_ += 1;

    if (y_val_ >= BIRD_MAX_VEL_Y)
        {
            y_val_ = BIRD_MAX_VEL_Y;
        }
    if (input_type_.jump_ == 1)
        {
                y_val_ = -BIRD_JUMP_VEL_Y;
        }
    y_pos_ += y_val_;
}
