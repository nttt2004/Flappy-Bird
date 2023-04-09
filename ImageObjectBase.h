
#ifndef IMAGE_OBJECT_BASE
#define IMAGE_OBJECT_BASE

#include "CommonFunction.h"

class ImageObjectBase
{
public:
    ImageObjectBase();
    ~ImageObjectBase();
    void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; } // thêm kích thước
    SDL_Rect GetRect() const { return rect_; } // lấy kích thước
    SDL_Texture* GetObject() const { return p_object_; } //lấy vật thể

    virtual bool loadImg(std::string path, SDL_Renderer* screen); // tính đa hình trong c++
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
protected:
    SDL_Texture* p_object_; // luu tru cac hinh anh
    SDL_Rect rect_; // lưu kích thước
};

#endif
