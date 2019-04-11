#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "include/Screen.h"
#include "Particle.h"
#include "Swarm.h"
#include <stdlib.h>
#include <time.h>


using namespace std;

int main()
{

    srand(time(NULL));

    Screen screen;

    if(screen.init() == false){
        cout << "Error initializing SDL" << endl;
    }

    Swarm swarm;

    // bool quit = false; // Delt with elseware.

    while(true) {


        int elapsed = SDL_GetTicks();

        //screen.clear(); ?? This removes old particles. Instead of this, we can create a blur.
        swarm.update(elapsed);

        //int green = sin(elapsed) * 255; // Turns out this is really fast.
        int green = ((1 + sin(elapsed * 0.001)) * 128); // Good speed.
        int red = ((1 + sin(elapsed * 0.002)) * 128);
        int blue = ((1 + sin(elapsed * 0.003)) * 128);
/*
        for(int y = 0; y < Screen::SCREEN_HEIGHT; y++){
            for(int x = 0; x < Screen::SCREEN_WIDTH; x++){
                screen.setPixel(x, y, red, green, blue);
            }
        }
*/
        const Particle * const pParticles = swarm.getParticles();

        for(int i = 0; i< Swarm::NPARTICLES; i++){
            Particle particle = pParticles[i];

            int x = (particle.m_x + 1) * (Screen::SCREEN_WIDTH/2); // Determines the size of the explosion.
            int y = (particle.m_y * Screen::SCREEN_WIDTH/2) + (Screen::SCREEN_HEIGHT/2); // Makes it a circle and centers it.

            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();

        //screen.setPixel(400, 300, 255, 255, 255); // Sets a single pixel.

        screen.update(); // Draws the actual screen.

        if(screen.processEvents() == false) {
            break;
        }

    }

    return 0;
}
