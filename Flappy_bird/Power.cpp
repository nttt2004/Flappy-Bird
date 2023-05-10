#include "Power.h"

Power::Power()
{

}

Power::~Power()
{

}
void Power::AddPos(const int& xpos)
{
    pos_list_.push_back(xpos);
}

bool Power::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = loadImg(path, screen);
    return ret;
}

void Power::Show(SDL_Renderer* des)
{
     // SDL_Rect power_rect = {rect_.x,20, POWER_WIDTH, POWER_HEIGHT};
      //SDL_RenderCopy(des, p_object_, NULL, &power_rect);
   if(p_object_ != NULL){
     SDL_Rect power_rect = {rect_.x, rect_.y, POWER_WIDTH, POWER_HEIGHT};
     SDL_RenderCopy(des, p_object_, NULL, &power_rect);
   }
}

void Power::Renderer(SDL_Renderer* des)
{
  if(number_ == pos_list_.size())
  {
      for(int i=0; i<pos_list_.size(); i++)
      {
          rect_.x = pos_list_.at(i);
          Show(des);
      }
  }

}
void Power::Init()
{
    number_ = 3;
    if(pos_list_.size()>0)
    {
        pos_list_.clear();
    }

    AddPos(20);
    AddPos(60);
    AddPos(100);

}
void Power::Decrease()
{
    number_--;
    pos_list_.pop_back();
}
