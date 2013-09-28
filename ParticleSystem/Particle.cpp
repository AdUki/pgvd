#include "Particle.h"
#include "main.h"

#include <cmath>

Particle::Particle(unsigned texture, float velX, float velY,
                   float posX, float posY, float opacity,
                   double life, bool reverseFade, Particle *particle)
{
    this->texture = texture;
    this->velX = velX;
    this->velY = velY;
    this->life = life;
    this->posX = posX;
    this->posY = posY;
    this->opacity = opacity;
    this->reverseFade = reverseFade;

    time = 0;
    rotation = rand() % 360;
    newParticle = particle;
}

Particle::~Particle()
{
    if (newParticle != 0 && isDead()) {
        newParticle->posX = posX; newParticle->posY = posY;
        newParticle->velX += velX; newParticle->velY += velY;
        particles.push_back(*newParticle);
    }
}

bool Particle::isDead()
{
    return life - time <= 0;
}

void Particle::update()
{
    time += 0.5d;
    rotation += 0.5f;
    velY += gravity; velX += wind;
    posX += velX; posY += velY;
    /*
    std::cout <<
        time << std::endl <<
        velX << std::endl <<
        velY << std::endl <<
        posX << std::endl <<
        posY << std::endl;
    */
}

void Particle::draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();

        if (reverseFade) glColor4f ( 1.0, 1.0, 1.0,
            opacity * ((0.5d*life - fabs(life*0.5d - time)) / (life*0.5d) ));
        else glColor4f ( 1.0, 1.0, 1.0,
            opacity * ((life - time)/life) );

        glTranslatef ( posX, posY, 0 );
        glRotatef( rotation, 0, 0, 1);
        glBegin ( GL_QUADS );
            glTexCoord2f(1,0); glVertex2f(1,-1);
            glTexCoord2f(1,1); glVertex2f(1,1);
            glTexCoord2f(0,1); glVertex2f(-1,1);
            glTexCoord2f(0,0); glVertex2f(-1,-1);
        glEnd();
    glPopMatrix();
}
