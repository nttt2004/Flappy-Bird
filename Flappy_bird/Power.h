
#ifndef POWER_H
#define POWER_H
#include "ImageObjectBase.h"
#include <vector>
#define POWER_WIDTH 50
#define POWER_HEIGHT 50

class Power : public ImageObjectBase
{
public:
    Power();
    ~Power();
    void SetNumber(const int&num){number_ = num;}
    void AddPos(const int& xpos);
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void Renderer(SDL_Renderer* des);
    void Init();
    void Decrease();
private:
    int number_; //so mang
    std::vector <int> pos_list_;

};
#endif // POWER_H
