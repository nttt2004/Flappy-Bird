
#ifndef BASE_H_
#define BASE_H_

#define BASE_HEIGHT 40
#define BASE_SPEED 5
#define BASE_WIDTH 2100

#include "CommonFunction.h"
#include "ImageObjectBase.h"

class Base : public ImageObjectBase
{
public:
    Base();
    ~Base();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
private:
    int gBaseX;
    int gBaseY;
};

#endif // BASE_H_
