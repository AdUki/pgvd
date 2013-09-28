/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include "main.h"
#include "Particle.h"
#include <SOIL.h>
#include <time.h>

#define WINDOW_SIZE 800

GLdouble totalMovedX = 0.0;
GLdouble totalMovedY = 0.0;
GLdouble currentScale = 1.0;
GLdouble positionX = 0.0;
GLdouble positionY = -9.0;

std::list<Particle> particles;

inline float random(float randomizer)
{
    return (float)(rand() % (int)
        (randomizer*1000.0f) - (int)(randomizer*1000.0f)/2)
        / 1000.0f;
}

int LoadGLTextures()  // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    TEX_FIRE = SOIL_load_OGL_texture (
        "fire.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if(TEX_FIRE == 0) return false;


    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, TEX_FIRE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    /* load an image file directly as a new OpenGL texture */
    TEX_SMOKE = SOIL_load_OGL_texture (
        "smoke.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if(TEX_SMOKE == 0) return false;


    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, TEX_SMOKE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true; // Return Success
}

void timeline (int value)
{
    for(std::list<Particle>::iterator iter = particles.begin();
        iter != particles.end(); iter++)
    {
        iter->update();
        if (iter->isDead())
            iter = particles.erase(iter);
    }

    for (int n = 0; n < FIRE_AMOUNT; n++)
        particles.push_back( Particle(TEX_FIRE, random(FIRE_SPREAD), random(FIRE_SPREAD),
            positionX + random(2), positionY + random(2), 1.0f, FIRE_LIFE + random(FIRE_LIFE/2), false));

    for (int n = 0; n < SMOKE_AMOUNT; n++)
    particles.push_back( Particle(TEX_FIRE, random(FIRE_SPREAD), random(FIRE_SPREAD),
            positionX + random(2), positionY + random(2), 1.0f, 10, false,
            new Particle(TEX_SMOKE, 0.0f, 0.0f, 0.0f, 0.0f, 0.2f, SMOKE_LIFE + random(SMOKE_LIFE/2), true)));

    glutPostRedisplay();
    glutTimerFunc (1000/120, timeline, value);
}

/* Everytime we need to redraw the window, a call to drawL is made */
void redraw(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
    glScaled(currentScale, currentScale, 1);
    glTranslated(totalMovedX, totalMovedY, 0);

    // drawing particles
    for(std::list<Particle>::iterator iter = particles.begin();
        iter != particles.end(); iter++)
    {
        iter->draw();
    }

	glutSwapBuffers();

	static bool timeStarted = false;
	if (timeStarted == false)
    {
        timeStarted = true;
        timeline(0);
    }
}

/* Stretch the viewport to fit the window */
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void mouse(int x, int y) {
    positionX = 20.0d*((double)x/(double)WINDOW_SIZE) - 10.0d;
    positionY = -(20.0d*((double)y/(double)WINDOW_SIZE) - 10.0d);
}

void wheel(int wheel, int direction, int x, int y)
{
    if ( glutGetModifiers() & GLUT_ACTIVE_SHIFT ) {
        if (direction > 0) wind += 0.0005d;
        else wind -= 0.0005f;
    } else {
        if (direction > 0) gravity += 0.0005d;
        else gravity -= 0.0005f;
    }
}

void key(unsigned char c, int x, int y) {
	switch(c) {
	case 'q': exit(1);
    case '4': totalMovedX += 0.2; break;
    case '6': totalMovedX -= 0.2; break;
    case '8': totalMovedY -= 0.2; break;
    case '2': totalMovedY += 0.2; break;
    case '+': currentScale += 0.1; break;
    case '-': currentScale -= 0.1; break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    std::cout << "To change gravity use mousewheel." << std::endl
              << "To change wind use shift and mousewheel." << std::endl;

    /* initialize random seed: */
    srand (time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE); /* Set the window size */
	glutInitWindowPosition(100, 100); /* Intial window position */
	glutCreateWindow("Particle Systems"); /* Set the title */

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(mouse);
	glutMouseWheelFunc(wheel);
	glutKeyboardFunc(key);

	glClearColor(0.0, 0.0, 0.0, 1.0); // Set a black background
	glColor3f(1.0, 0.0, 0.0); // Set the default pen color to red
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLineWidth(1.0);

    // Blending setup
	//glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    glEnable( GL_BLEND );

    // Init textures
    if (!LoadGLTextures()) std::cout << "Error loading textures!\n";

    glutMainLoop();

	return 0;
}
