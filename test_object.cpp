#include "SDL.h"
#include "object.h"
// 这里迫不得已只能undef，并没有找到更好的解决办法
#undef main
/* Moving Rectangle */
int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    // SDL_Texture *texture;
    SDL_Event event;
    
    
    // 对SDL进行初始化，这里只用到了视频，所以只初始化VIDEO
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }
    
    

    window = SDL_CreateWindow("SDL_TestObject",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              1024, 768,
                              SDL_WINDOW_RESIZABLE);

    

    renderer = SDL_CreateRenderer(window, -1, 0);

    // texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
    // 创建一个有三个节点的Object进行测试
    SDL_Texture *sharedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 100, 50);
    // 画一个红色的矩形
    SDL_SetRenderTarget(renderer, sharedTexture);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_Rect r;
    r.w = 100;
    r.h = 50;
    SDL_RenderDrawRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(renderer, &r);
    
    // 创建测试用的Object和List，并创建节点
    base::CObject testObject;
    std::list<base::CNode> testList;
    // 创建包含节点的list
    for (int i = 1; i <= 3; i++)
    {
        base::CNode node(50 * i, 50 * i, r.w, r.h, sharedTexture); // 节点位于对角线上 50,50 ; 100,100 ; 150,150
        testList.push_back(node);
    }
    testObject.SetNodeList(&testList);  // 设置list
    testObject.Draw(renderer);  // 测试Draw的功能

    while (1)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
        // r.x = rand() % 500;
        // r.y = rand() % 500;

        // SDL_SetRenderTarget(renderer, sharedTexture);
        // SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        // SDL_RenderClear(renderer);
        // SDL_RenderDrawRect(renderer, &r);
        // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
        // SDL_RenderFillRect(renderer, &r);
        // SDL_SetRenderTarget(renderer, NULL);
        // SDL_RenderCopy(renderer, sharedTexture, NULL, NULL);
        // SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}