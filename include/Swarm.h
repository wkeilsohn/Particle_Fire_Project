#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

using namespace std;

class Swarm
{
    public:
        const static int NPARTICLES = 5000;

        Swarm();
        virtual ~Swarm();
        void update(int elapsed);

        const Particle *const getParticles(){return m_pParticles;};

    protected:

    private:
        Particle *m_pParticles;
        int lastTime;
};

#endif // SWARM_H
