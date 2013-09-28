/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include "main.h"
#include "element.h"

////////////////////////////////////////////////////////
// TextE class
//
TextE::TextE(int width, const std::string &text) :
  _text(text)
{
  TEXT_BG_COLOR(_order)

  _padding = 50;
  _height = 0;
  _width = width;
  int w = 0;
  for (std::string::iterator it = _text.begin(); it != _text.end(); it++) {
    w += glutStrokeWidth(GLUT_STROKE_ROMAN, *it);
    if (w > width - 2*_padding) {
      w = 0;
      _height += glutStrokeHeight(GLUT_STROKE_ROMAN) + 2*_padding;
    }
  }
  if (w != 0) _height += glutStrokeHeight(GLUT_STROKE_ROMAN) + 2*_padding;
}

void TextE::draw()
{
  int w = 0;
  glTranslatef(0, -glutStrokeHeight(GLUT_STROKE_ROMAN)*SCALE, 0);
  glPushMatrix();
  for (std::string::iterator it = _text.begin(); it != _text.end(); it++) {

    #ifndef DRAW_TEXT
    // Draw big bounding box
    glPushMatrix();
      glTranslatef(0,0,-globalDepth*SCALE + 0.1);
      glColor4f(color[0], color[1], color[2], color[3]);
      glTranslatef(_padding*SCALE, -_padding*SCALE, 0);
      DrawRectangle(_width-2*_padding, glutStrokeHeight(GLUT_STROKE_ROMAN), globalDepth);
    glPopMatrix();
    #endif
    
    // Draw text
    glPushMatrix();
      #ifdef DRAW_TEXT
        //glColor4f(1,1,1,1);
        glColor4f(0,0,0,1);
        
        glTranslatef(_padding*SCALE, -_padding*SCALE/2.f, -globalDepth + 0.2);

        // Draw letter
        glTranslatef(w*SCALE, 0, 0);
        glScalef(SCALE, SCALE, SCALE);

        DrawLetter(*it);
        // DrawRotatingLetter(*it);
      #endif

      // Next line handling
      w += glutStrokeWidth(GLUT_STROKE_ROMAN, *it);
      if (w > _width - 2*_padding) { w = 0; newLine(); }
    glPopMatrix();
  }
  if (w != 0)  newLine();
  glPopMatrix();
}

void TextE::newLine()
{
  glPopMatrix();
  glTranslatef(0, - SCALE*(glutStrokeHeight(GLUT_STROKE_ROMAN) + 2*_padding), 0);
  glPushMatrix();
}
