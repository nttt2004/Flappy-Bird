#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
    // Định nghĩa các hằng số
    const int SCREEN_WIDTH = 288;
    const int SCREEN_HEIGHT = 512;

    const int BASE_HEIGHT = 40;

    const int PIPE_WIDTH = 52;
    const int PIPE_HEIGHT = 320;
    const int PIPE_GAP = 100;
    const int PIPE_SPEED = 125;

    const int BIRD_WIDTH = 34;
    const int BIRD_HEIGHT = 24;
    const int BIRD_JUMP_VEL_Y = -2;
    const int BIRD_MAX_VEL_Y = 1;

    const int GRAVITY = 1;//tốc độ rơi/trọng lực

    const int JUMP_FORCE = 12;

    // Khai báo các biến
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Texture* gBackground = NULL;
    SDL_Texture* gBase = NULL;
    //thêm
    const int gBaseX = 0;

    SDL_Texture* gPipeNorth = NULL;
    SDL_Texture* gPipeSouth = NULL;

    SDL_Texture* gBird[3];
    SDL_Rect gBirdRect;

    /*thêm
    int gBirdX = 20;
    int gBirdY = 20;
    */
    int gBirdX = (SCREEN_WIDTH - BIRD_WIDTH)/4;
    int gBirdY = (SCREEN_HEIGHT - BIRD_HEIGHT)/2;

    int gBirdFrame = 0;
    int gBirdVelY = 0;

    vector<SDL_Rect> gPipes;
    int gScore = 0;
    
    bool gGameOver = false;

// Hàm khởi tạo SDL
bool initSDL()
{
        bool success = true;
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            gWindow = SDL_CreateWindow("Flying Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (gWindow == NULL)
            {
                cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
                if (gRenderer == NULL)
                {
                    cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
                    success = false;
                }
                else
                {
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags))
                    {
                        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                        success = false;
                    }
                }
            }
        }
        return success;
}

// Hàm load hình ảnh
SDL_Texture* loadTexture(string path)
{
        SDL_Texture* newTexture = NULL;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            cout << "Could not load image " << path << "! SDL_Error: " << SDL_GetError() << endl;
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            if (newTexture == NULL)
            {
                cout << "Could not create texture from " << path << "! SDL_Error: " << SDL_GetError() << endl;
            }
            SDL_FreeSurface(loadedSurface);
        }
        return newTexture;
}

// Hàm tạo đường ống mới
void createPipe()
{
    SDL_Rect pipeNorth, pipeSouth;
    pipeNorth.x = SCREEN_WIDTH - PIPE_WIDTH;
    pipeNorth.y = -(rand() % PIPE_HEIGHT);
    pipeNorth.w = PIPE_WIDTH;
    pipeNorth.h = PIPE_HEIGHT;

    // Tính toán tọa độ đường ống phía nam dựa trên đường ống phía bắc
    pipeSouth.x = SCREEN_WIDTH - PIPE_WIDTH;
    pipeSouth.y = pipeNorth.y + PIPE_HEIGHT + PIPE_GAP;
    pipeSouth.w = PIPE_WIDTH;
    pipeSouth.h = SCREEN_HEIGHT - pipeSouth.y;

    // Thêm hai đường ống vào danh sách
    gPipes.push_back(pipeNorth);
    gPipes.push_back(pipeSouth);
}

// Hàm tải các hình ảnh và khởi tạo biến
bool loadMedia()
{
    bool success = true;
    gBackground = loadTexture("image//background.png");
    if (gBackground == NULL)
    {
    cout << "Failed to load background texture!" << endl;
    success = false;
    }

    gBase = loadTexture("image//base.png");
    if (gBase == NULL)
    {
        cout << "Failed to load base texture!" << endl;
        success = false;
    }

    gPipeNorth = loadTexture("image//pipeNorth.png");
    if (gPipeNorth == NULL)
    {
        cout << "Failed to load pipeNorth texture!" << endl;
        success = false;
    }

    gPipeSouth = loadTexture("image//pipeSouth.png");
    if (gPipeSouth == NULL)
    {
        cout << "Failed to load pipeSouth texture!" << endl;
        success = false;
    }

    gBird[0] = loadTexture("image//bird0.png");
    gBird[1] = loadTexture("image//bird1.png");
    gBird[2] = loadTexture("image//bird2.png");
    for (int i = 0; i < 3; i++)
    {
        if (gBird[i] == NULL)
        {
            cout << "Failed to load bird texture!" << endl;
            success = false;
        }
    }

    return success;
}

// Hàm giải phóng các biến và thoát SDL
void closeSDL()
{
    SDL_DestroyTexture(gBackground);
    SDL_DestroyTexture(gBase);
    SDL_DestroyTexture(gPipeNorth);
    SDL_DestroyTexture(gPipeSouth);
    for (int i = 0; i < 3; i++)
    {
      SDL_DestroyTexture(gBird[i]);
    }
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

// Hàm kiểm tra va chạm giữa chim và đường ống
bool checkCollision(SDL_Rect birdRect, SDL_Rect pipeRect)
{
    if (birdRect.x + BIRD_WIDTH > pipeRect.x && birdRect.x < pipeRect.x + PIPE_WIDTH)
    {
       if (birdRect.y < pipeRect.y + PIPE_HEIGHT || birdRect.y + BIRD_HEIGHT > pipeRect.y + PIPE_HEIGHT + PIPE_GAP)
       {
         return true;
       }
    }
    return false;
}

// Hàm cập nhật trạng thái của trò chơi
void update()
{
    // Cập nhật vị trí của các đường ống
    for (unsigned int i = 0; i < gPipes.size(); i++)
    {
      gPipes[i].x -= PIPE_SPEED;
    }

    // Xóa các đường ống đã vượt qua màn hình
    if (!gPipes.empty() && gPipes[0].x + PIPE_WIDTH < 0)
    {
        gPipes.erase(gPipes.begin());
        gPipes.erase(gPipes.begin());
        gScore++;
    }

    // Di chuyển nền
    /*gBaseX -= BASE_SPEED;
    if (gBaseX < -SCREEN_WIDTH)
    {
        gBaseX = 0;
    }
     */
    // Kiểm tra va chạm giữa chim và đường ống
    SDL_Rect birdRect = {gBirdX, gBirdY, BIRD_WIDTH, BIRD_HEIGHT};

    for (unsigned int i = 0; i < gPipes.size(); i++)
    {
        SDL_Rect pipeRect = gPipes[i];
        if (checkCollision(birdRect, pipeRect))
        {
            gGameOver = true;
        }
    }

    // Cập nhật trạng thái của chim
    if (!gGameOver)
    {
        gBirdFrame++;
        if (gBirdFrame / 10 >= 3)
        {
            gBirdFrame = 0;
        }
        gBirdY += gBirdVelY;
        gBirdVelY += GRAVITY;

        if (gBirdVelY > BIRD_MAX_VEL_Y)
        {
            gBirdVelY = BIRD_MAX_VEL_Y;
        }

        // Kiểm tra xem chim có vượt quá màn hình hay không
        if (gBirdY < 0 || gBirdY + BIRD_HEIGHT > SCREEN_HEIGHT - BASE_HEIGHT)
        {
            gGameOver = true;
        }
    }
}

// Hàm vẽ các đối tượng lên màn hình
void render(){
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    SDL_RenderCopy(gRenderer, gBackground, NULL, NULL);

    for (unsigned int i = 0; i < gPipes.size(); i++)
    {
        SDL_Rect pipeRect = gPipes[i];
        if (i % 2 == 0)
        {
            SDL_RenderCopy(gRenderer, gPipeNorth, NULL, &pipeRect);
        }
        else
        {
            SDL_RenderCopy(gRenderer, gPipeSouth, NULL, &pipeRect);
        }
    }

    SDL_Rect baseRect = {gBaseX, SCREEN_HEIGHT - BASE_HEIGHT, SCREEN_WIDTH, BASE_HEIGHT};
    SDL_RenderCopy(gRenderer, gBase, NULL, &baseRect);

    if (!gGameOver)
    {
        SDL_Rect birdRect = {gBirdX, gBirdY, BIRD_WIDTH, BIRD_HEIGHT};
        SDL_RenderCopy(gRenderer, gBird[gBirdFrame / 10], NULL, &birdRect);
    }

    SDL_RenderPresent(gRenderer);
}

    // Hàm chạy trò chơi
void runGame()
{
    // Khởi tạo biến
    bool quit = false;
    SDL_Event e;


    // Tải hình ảnh và khởi tạo biến
    if (!loadMedia())
    {
        cout << "Failed to load media!" << endl;
        quit = true;
    }

    // Vòng lặp chính của trò chơi
    while (!quit)
    {
        SDL_RenderClear(gRenderer);
        // Xử lý sự kiện
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    if (!gGameOver)
                    {

                        gBirdVelY += BIRD_JUMP_VEL_Y;
                        createPipe();
                    }
                    else
                    {
                        // Reset lại trò chơi khi người chơi bấm phím SPACE sau khi kết thúc trò chơi
                        //resetGame();
                    }
                }
            }
        }

        // Cập nhật trạng thái và vẽ đối tượng lên màn hình
        //createPipe();
        render();
        update();
    }
}

    // Hàm giải phóng tài nguyên và thoát SDL
void close()
{
    // Giải phóng hình ảnh
    SDL_DestroyTexture(gBackground);
    SDL_DestroyTexture(gPipeNorth);
    SDL_DestroyTexture(gPipeSouth);
    SDL_DestroyTexture(gBase);
    for (int i = 0; i < 3; i++)
    {
    SDL_DestroyTexture(gBird[i]);
    }
    // Giải phóng cửa sổ và renderer
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    // Thoát SDL
    SDL_Quit();
}

// Hàm main
int main(int argc, char* argv[])
{
    // Khởi tạo SDL và tạo cửa sổ
    if (!initSDL())
    {
        cout << "Failed to initialize!" << endl;
        return 1;
    }
    // Chạy trò chơi
    runGame();

    // Giải phóng tài nguyên và thoát SDL
    close();

    return 0;
    }




