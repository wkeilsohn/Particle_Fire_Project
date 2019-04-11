#include "Particle.h"
#include <stdlib.h>
#include <math.h>

using namespace std;

Particle::Particle():m_x(0), m_y(0) // This creates the basic "explosion" effect.
{
/* Creates a random location for the particles.

    m_x = ((2.0 * rand())/RAND_MAX) - 1;
    m_y = ((2.0 * rand())/RAND_MAX) - 1;
*/

/* Used for square movement.
    m_xspeed = 0.01 * (((2.0 * rand())/RAND_MAX)- 1);
    m_yspeed = 0.01 * (((2.0 * rand())/RAND_MAX)- 1);

    m_dirrection = (2 * M_PI *rand())/RAND_MAX;
    m_speed = (0.01 * rand())/RAND_MAX; // Sets the overall speed

    m_speed *= m_speed;
*/

init();

}


Particle::~Particle()
{
    //dtor
}

void Particle::init(){
    m_x = 0;
    m_y = 0;
    m_dirrection = (2 * M_PI *rand())/RAND_MAX;
    m_speed = (0.01 * rand())/RAND_MAX; // Sets the overall speed

    m_speed *= m_speed;
}

void Particle::update(int interval){

/* This is great for square parameters, but not for round ones.
    m_x += m_xspeed;
    m_y += m_yspeed;

    if(m_x <= -1.0 || m_x >= 1.0){
        m_xspeed = -m_xspeed;
    }

    if(m_y <= -1.0 || m_y >= 1.0) {
        m_yspeed = -m_yspeed;
    }
*/
    m_dirrection += interval * (2 * exp(-3000));

    double xspeed = m_speed * cos(m_dirrection);
    double yspeed = m_speed * sin(m_dirrection);

    m_x += xspeed * interval; // Sets the relative speed.
    m_y += yspeed * interval;

    if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > +1) {
        init();
    }
    if(rand() < RAND_MAX/100){
        init();
    }
}
