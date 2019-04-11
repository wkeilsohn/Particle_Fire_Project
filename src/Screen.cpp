#include "../include/Screen.h"

using namespace std;

Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL){

}

Screen::~Screen()
{
    //dtor
}

bool Screen::init(){

     if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        //cout << "SDL init failed" << endl;
        return false; // Just testing that it launched.
    };

    m_window = SDL_CreateWindow("Particle Fire Explosion",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN);

    if(m_window == NULL) {
        //cout << "Failed to create window" << endl;
        SDL_Quit();
        return false; // Testing that the window is made.
    }

    m_renderer = SDL_CreateRenderer(m_window, -1,
    SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888,
    SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

    if(m_renderer == NULL){
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    if(m_texture == NULL){
        //cout << "Failed to create texture/renderer" <<endl;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    return true;
}

void Screen::update(){
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

bool Screen::processEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return false;
        }
    }
    return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){

    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT){
        return;
    }

    Uint32 color = 0;

    color += 0xFF;
    color <<= 8;
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;

    m_buffer1[(y * SCREEN_WIDTH) + x] = color;

}

void Screen::close(){

    delete [] m_buffer1;
    delete [] m_buffer2;

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);

    SDL_DestroyWindow(m_window); // Cleans up the window.
    SDL_Quit(); // Cleans up SDL.

}
/*
void Screen::clear(){
    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}*/

void Screen::boxBlur(){
   Uint32 *temp = m_buffer1; // You need this b/c unlike python you can not swap two variable at the same time.

   m_buffer1 = m_buffer2;
   m_buffer2 = temp;

   for(int y = 0; y < SCREEN_HEIGHT; y++){
    for(int x = 0; x < SCREEN_WIDTH; x++) {
        // B/c you want the average of all values within a 3x3 space you need to loop trough another rowxcolumn space:

        int redTotal = 0;
        int greenTotal = 0;
        int blueTotal = 0;


        for(int row = -1; row <= 1; row++ ){
            for(int col = -1; col <= 1; col++ ){
                int currentX = x + col;
                int currentY = y + row;

                if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT){
                    Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX]; // Gets us the overall color.

                    Uint8 red = color >> 32; // Alpha is first, thus all your numbers are off by 8
                    Uint8 green = color >> 24;
                    Uint8 blue = color >> 16;

                    redTotal += red;
                    greenTotal += green;
                    blueTotal += blue;
                }
            }
        }

        Uint8 red = redTotal/9;
        Uint8 green = redTotal/9;
        Uint8 blue = blueTotal/9;

        setPixel(x, y, red, green, blue);
    }
   }
}
