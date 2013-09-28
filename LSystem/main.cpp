/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include "main.h"
#include "lsystem.h"

GLdouble totalMovedX = 0.0;
GLdouble totalMovedY = 0.0;
GLdouble currentScale = 1.0;

/* Everytime we need to redraw the window, a call to drawL is made */
void redraw(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScaled(currentScale, currentScale, 1);
    glTranslated(totalMovedX, totalMovedY, 0);

    L->draw();

	glutSwapBuffers();
}

/* Stretch the viewport to fit the window */
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

static void timerCallback (int value)
{
   /* Do timer processing */
   glutPostRedisplay();

   /* call back again after elapsedUSecs have passed */
   glutTimerFunc (100, timerCallback, value);
}

void mouse(int button, int state, int x, int y) {
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
    case '7': L->decDepth(); break;
    case '9': L->addDepth(); break;
    case '3':
        if (++L == systems.end()) L = systems.begin();
        goto reset;
    case '1':
        if (L == systems.begin()) L = systems.end();
        L--;
    reset:
        L->setDepth(1);
        totalMovedX = 0;
        totalMovedY = 0;
        currentScale = 1;
		glutSetWindowTitle(L->getTitle().c_str());
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    initSystems();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 700); /* Set the window size */
	glutInitWindowPosition(100, 100); /* Intial window position */
	glutCreateWindow(L->getTitle().c_str()); /* Set the title */

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(key);

	glClearColor(0.0, 0.0, 0.0, 1.0); // Set a black background
	glColor3f(1.0, 0.0, 0.0); // Set the default pen color to red
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.75, 3.75, -2.75, 2.75);
	glMatrixMode(GL_MODELVIEW);
	glLineWidth(1.0);

    timerCallback(0);
	glutMainLoop();

	return 0;
}
