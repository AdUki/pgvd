#ifndef GL_MAIN_H_INCLUDED
#define GL_MAIN_H_INCLUDED

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
	#include <GL/freeglut.h>
	#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <list>

#define FIRE_AMOUNT 3
#define FIRE_SPREAD 0.09
#define FIRE_LIFE 30
#define SMOKE_AMOUNT 3
#define SMOKE_SPREAD 0.0
#define SMOKE_LIFE 30

class Particle;

extern std::list<Particle> particles;

extern unsigned TEX_SMOKE;
extern unsigned TEX_FIRE;
extern float gravity;
extern float wind;

#endif // GL_MAIN_H_INCLUDED
