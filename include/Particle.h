#ifndef PARTICLE_H
#define PARTICLE_H

using namespace std;

class Particle
{
    public:
        double m_x;
        double m_y;

        //double m_xspeed; // These work for squares, but for circles, you need a bit more calculus.
        //double m_yspeed;

        double m_speed;
        double m_dirrection;

        Particle();
        virtual ~Particle();
        void update(int interval);

    protected:

    private:
        void init();
};

#endif // PARTICLE_H
