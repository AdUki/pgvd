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
