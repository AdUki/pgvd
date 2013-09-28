/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#ifndef PARTICLE_H
#define PARTICLE_H

#include <list>

class Particle
{
    public:
        Particle(unsigned texture, float velX, float velY,
                 float posX, float posY, float opacity,
                 double life, bool reverseFade, Particle *particle = 0);
        virtual ~Particle();

        void update();
        void draw();
        bool isDead();

        static Particle* Fire();

    protected:
        Particle *newParticle;
    private:
        unsigned texture;

        double life;
        double time;

        float posX;
        float posY;
        float velX;
        float velY;

        float rotation;
        float opacity;

        bool reverseFade;
};

#endif // PARTICLE_H
