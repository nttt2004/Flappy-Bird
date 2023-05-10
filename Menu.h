
#ifndef MENU_H_
#define MENU_H_

#include "CommonFunction.h"
#include "ImageObjectBase.h"

#define BUTTON_WIDTH 350
#define BUTTON_HEIGHT 150

class Menu : public ImageObjectBase
{
public:
    //Initializes internal variables
    Menu();
    ~Menu();

    //Load button
    bool LoadImg(std::string path, SDL_Renderer* screen);
    //void set_clips();

    //Sets top left position
    void setPosition(int x, int y);

    //Handles mouse event
    //bool isInside(SDL_Event* e);
    int handleEvent(SDL_Event event);
    //void handleEventSwitch(SDL_Event* e, bool& isOn);

    //Shows button sprite
    void ShowButton(SDL_Renderer* screen);
    //void ShowSwitch(SDL_Renderer* screen);

private:
    //Top left position
    SDL_Point bPos;

    //button size
    int button_width_;
    int button_height_;
    //SDL_Rect logo_rect;
    //SDL_Rect option1_rect;
    //SDL_Rect option2_rect;

    //Currently used global sprite
    //LButtonSprite mCurrentSprite;

    //Currently used global sprite
    //LSwitchSprite mSwitchCurrentSprite;

    //Render Rect
    //SDL_Rect button_clip[2];

};

#endif //MENU_H_
