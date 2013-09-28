/* ============================================================================
**
** Text visualization
** Copyright (C) 2013 Simon Mikuda
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
**
** ========================================================================= */

#include "main.h"

#include <iostream>
#include <string>
#include <cmath>

#include "camera.h"
#include "element.h"
#include "composite.h"

#define TEXT_SIZE 100

#define WIN_SIZE_X 1500
#define WIN_SIZE_Y 900
#define NUM_COLORS 24
#define NUM_STRINGS 9
#define LINE_WIDTH 5000
#define LINE_HEIGHT glutStrokeHeight(GLUT_STROKE_ROMAN)

enum KEYS {
  NO_KEY = 0,
  W_KEY = 1 << 0,
  A_KEY = 1 << 1,
  S_KEY = 1 << 2,
  D_KEY = 1 << 3,
  MOUSE_LEFT_KEY = 1 << 4,
  MOUSE_RIGHT_KEY = 1 << 5
};
int key_state;
unsigned long long globalTime = 0;
GLfloat globalDepth = 1;
unsigned globalSize = 5;

int  xold = 0;
int  yold = 0;

GLdouble rotation = 0;
GLfloat width, height;
GLfloat scale = 0.002;

CCamera Camera;
int rotate_x = 0;
int rotate_y = 0;

Element *root;

#include "ast.h"

void DrawLetter(char letter)
{
  glutStrokeCharacter(GLUT_STROKE_ROMAN, letter);
}

void DrawRotatingLetter(char letter)
{
  int width = glutStrokeWidth(GLUT_STROKE_ROMAN, letter);
  glTranslatef(width/2.0f, 0, 0);
  glRotatef(globalTime, 0,1,0);
  glTranslatef(-width/2.0f, 0, 0);

  DrawLetter(letter);
}

void DrawRectangle(int width, int height, GLfloat depth)
{
  glTranslatef(0, 0, -depth);
  glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(width*SCALE, 0, 0);
    glVertex3f(width*SCALE, height*SCALE, 0);
    glVertex3f(0, height*SCALE, 0);
  glEnd();
}

void DrawBox(int width, int height, GLfloat depth)
{
  glTranslatef(0, 0, -depth);

  glBegin(GL_QUADS);
    // Top wall
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, depth);
    glVertex3f(width*SCALE, 0, depth);
    glVertex3f(width*SCALE, 0, 0);

    // Bottom wall
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0, height*SCALE, 0);
    glVertex3f(0, height*SCALE, depth);
    glVertex3f(width*SCALE, height*SCALE, depth);
    glVertex3f(width*SCALE, height*SCALE, 0);

    // Front wall
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0,0,0);
    glVertex3f(width*SCALE, 0, 0);
    glVertex3f(width*SCALE, height*SCALE, 0);
    glVertex3f(0, height*SCALE, 0);

    // Back wall
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0,0,depth);
    glVertex3f(width*SCALE, 0, depth);
    glVertex3f(width*SCALE, height*SCALE, depth);
    glVertex3f(0, height*SCALE, depth);

    // Left wall
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, depth);
    glVertex3f(0, height*SCALE, depth);
    glVertex3f(0, height*SCALE, 0);

    // Right wall
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width*SCALE, 0, 0);
    glVertex3f(width*SCALE, 0, depth);
    glVertex3f(width*SCALE, height*SCALE, depth);
    glVertex3f(width*SCALE, height*SCALE, 0);
    
  glEnd();
}

void DisplayFunc(void)
{
  globalTime++;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  Camera.Render();

  glTranslatef(-root->getWidth()*SCALE*0.5f, root->getHeight()*SCALE*0.5f,-100);

  glTranslatef(root->getWidth()*SCALE*0.5f, -root->getHeight()*SCALE*0.5f,0);
  glRotatef(rotate_x, 1, 0, 0);
  glRotatef(rotate_y, 0, 1, 0);
  glTranslatef(-root->getWidth()*SCALE*0.5f, root->getHeight()*SCALE*0.5f,0);

  root->draw();
  
  glutSwapBuffers();
}

/*
** Function called when the window is created or resized
*/
void ReshapeFunc(int width, int height)
{
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(45, width / (float) height, 0.1, 1000000);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay(); 
}

void UpdateFunc(int value)
{

  if ( key_state & W_KEY) Camera.MoveForwards (1);
  if ( key_state & S_KEY) Camera.MoveBackwards(1);
  if ( key_state & A_KEY) Camera.StrafeLeft   (1);
  if ( key_state & D_KEY) Camera.StrafeRight  (1);

  glutPostRedisplay();
  glutTimerFunc (1000/120, UpdateFunc, value);
}

/*
** Function called when a key is hit
*/
void KeyboardFunc(unsigned char key, int x, int y)
{
  if (key == 'q' || key == 'Q') exit(0);
  if (key == 'w' || key == 'W') key_state |= W_KEY;
  if (key == 's' || key == 'S') key_state |= S_KEY;
  if (key == 'a' || key == 'A') key_state |= A_KEY;
  if (key == 'd' || key == 'D') key_state |= D_KEY;

  if (key == '+') globalSize++;
  if (key == '-' && globalSize > 0) globalSize--;
}

/*
** Function called when a key is released
*/
void KeyboardUpFunc(unsigned char key, int x, int y)
{
  if (key == 'w' || key == 'W') key_state ^= W_KEY;
  if (key == 's' || key == 'S') key_state ^= S_KEY;
  if (key == 'a' || key == 'A') key_state ^= A_KEY;
  if (key == 'd' || key == 'D') key_state ^= D_KEY;
}

/*
** Function called when a mouse button is hit
*/
void MouseFunc(int button, int state, int x, int y)
{
  long long mask = NO_KEY;
  if (GLUT_LEFT_BUTTON == button) mask = MOUSE_LEFT_KEY;
  if (GLUT_RIGHT_BUTTON == button) mask = MOUSE_RIGHT_KEY;
  if (state == GLUT_DOWN) key_state |= mask;
  else key_state ^= mask;

  xold = x;
  yold = y;
}

/*
** Function called when the mouse is moved
*/
void MotionFunc(int x, int y)
{
  if (key_state & MOUSE_LEFT_KEY) {
    Camera.RotateX((yold-y)*0.2f);
    Camera.RotateY((xold-x)*0.2f);
    glutPostRedisplay();
  }

  if (key_state & MOUSE_RIGHT_KEY) {
    rotate_x += (y-yold)*0.1f;
    rotate_y += (x-xold)*0.1f;
    glutPostRedisplay();
  }
  xold = x;
  yold = y;
}

void WheelFunc(int wheel, int direction, int x, int y)
{
  if (direction > 0) globalDepth += 0.2f;
  else if (globalDepth > 0.3f) globalDepth -= 0.2f;
}

int main(int argc, char **argv)
{
  std::cout << "Welcome to text visualisation!\n";
  std::cout << "\tPress + to increse layers\n"
            << "\tPress - to decrease layers\n"
            << "\tUse mouse wheel do increase space between layers\n"
            << "\tUse W, A, S, D keys to move in scene\n"
            << "\tHold left mouse button to change FPS view\n"
            << "\tHold right mouse button to rotate object\n";

  /* Creation of the window */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WIN_SIZE_X, WIN_SIZE_Y);
  glutCreateWindow("Text visualisation");

  /* OpenGL settings */
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(3);

#ifdef BOX_3D
  glShadeModel(GL_SMOOTH);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  /* Lightining settins */
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);

  float LightPos[] = { 0.0f, 15.0f, 10.0f, 1.0f};   // Light Position
  float LightAmb[] = { 0, 0, 0, 1 };   // Ambient Light Values
  float LightDif[] = { 1, 1, 1, 1 };   // Diffuse Light Values
  float LightSpc[] = { 1, 1, 1, 1 };   // Specular Light Values
  
  glLightfv(GL_LIGHT0, GL_POSITION, LightPos);  // Set Light1 Position
  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);   // Set Light1 Ambience
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);   // Set Light1 Diffuse
  glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc);  // Set Light1 Specular

  glEnable (GL_LIGHT0);
#endif

  /* Declaration of the callbacks */
  glutDisplayFunc(&DisplayFunc);
  glutReshapeFunc(&ReshapeFunc);
  glutKeyboardFunc(&KeyboardFunc);
  glutKeyboardUpFunc(&KeyboardUpFunc);
  glutMouseFunc(&MouseFunc);
  glutMotionFunc(&MotionFunc);
  glutMouseWheelFunc(&WheelFunc);

  /* Initializations */
  key_state = NO_KEY;
  UpdateFunc(0);
  globalSize = 6;

  /* Create AST */
  ast1();
  // ast2();
  // ast3();

  return 0;
}
