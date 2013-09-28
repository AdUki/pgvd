/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include "lsystem.h"

std::vector<LSystem> systems;
std::vector<LSystem>::iterator L;
void initSystems()
{
    std::cout
        << "Controls:\n"
        << "Press [q] to quit\n"
        << "Press [4,2,6,8] to move viewport\n"
        << "Press [7,9] to change depth\n"
        << "Press [1,3] to change L-System\n";

    LSystem *system;
    system = new LSystem("Koch curve", "F", 60.0, 1, 3.0);
    system->addRule('F', "F-F++F-F");
    systems.push_back(*system);

    system = new LSystem("Sierpinski triangle", "A", 60.0, 1, 3.0);
    system->addRule('A', "B-A-B");
    system->addRule('B', "A+B+A");
    systems.push_back(*system);

    system = new LSystem("Tree", "---M", 30.0, 1, 3.0);
    system->addRule('M', "S[+M][-M]SM");
    system->addRule('S', "SS");
    systems.push_back(*system);

    system = new LSystem("Weed", "---X", 25.0, 1, 3.0);
    system->addRule('X', "F-[[X]+X]+F[+FX]-X");
    system->addRule('F', "FF");
    systems.push_back(*system);

    system = new LSystem("Gosper curve", "L", 60.0, 1, 3.0);
    system->addRule('L', "L+R++R-L--LL-R+");
    system->addRule('R', "-L+RR++R+L--L-R");
    systems.push_back(*system);

    system = new LSystem("Islands and Lakes", "F+F+F+F", 90.0, 0.8, 6.0);
    system->addRule('F', "F+f-FF+F+FF+Ff+FF-f+FF-F-FF-Ff-FFF");
    system->addRule('f', "ffffff");
    systems.push_back(*system);

    system = new LSystem("Dragon curve", "FX", 90.0, 1, 3.0);
    system->addRule('X', "X+YF");
    system->addRule('Y', "FX-Y");
    systems.push_back(*system);

    system = new LSystem("Bump box", "F", 90.0, 1, 3.0);
    system->addRule('F', "F-F+F+F-F");
    systems.push_back(*system);

    L = systems.begin();
}

LSystem::LSystem(std::string title, std::string rule,
                float angle, float length, float shrink)
{
    this->title =  title;
    this->angle = angle;
    this->length = length;
    this->shrink = shrink;
    initRule = rule;
    setDepth(1);
}

void LSystem::addRule(char variable, std::string rule)
{
    variables.push_back(variable);
    rules.push_back(rule);
}

std::string LSystem::getTitle() { return title; }

int LSystem::addDepth() { setDepth(depth+1); return depth; }
int LSystem::decDepth() { setDepth(depth-1); return depth; }

void LSystem::setDepth(int newDepth)
{
    depth = newDepth;
    if (depth < 0) depth = 0;

    // init color to red
    red   = 1.0f;
    green = 0.0f;
    blue  = 0.0f;
    colorInc = 0.1;
}

void LSystem::draw()
{
	glPushMatrix();
	readRule(initRule, depth);
	glPopMatrix();
}

void LSystem::readRule(std::string rule, int depth)
{
    // Read whole rule
    for (int i = 0; rule[i] != '\0'; i++) {
        // Rotate left
        if (rule[i] == '+') {
            glRotatef(- (GLfloat) (angle),  0.0, 0.0, 1.0);
        // Rotate right
        } else if (rule[i] == '-') {
            glRotatef( (GLfloat) (angle),  0.0, 0.0, 1.0);
        // Load previous state
        } else if (rule[i] == ']') {
            glPopMatrix();
        // Save current state
        } else if (rule[i] == '[') {
            glPushMatrix();
        // Depth 0, draw lines
        } else if (depth == 0) {
            // If capital draw line and translate
            if (rule[i] >= 'A' && rule[i] <= 'Z') drawLine();
            // If not just translate
            glTranslatef((GLfloat)(length)/(shrink*this->depth), 0.0, 0.0);
        // Apply other rules if depth is not zero
        } else for (int j = 0; variables[j] != '\0'; j++) {
            if (rule[i] == variables[j]) {
                readRule(rules[j], depth-1);
                break;
            }
        }
    }
}

void LSystem::drawLine()
{
    // Draw line
    glBegin(GL_LINE_STRIP);
    glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f((GLfloat)(length)/(shrink*this->depth), 0.0, 0.0);
    glEnd();

    // Change color
    if      (red == 1.0 && green <  1.0 && blue == 0.0) green += colorInc;
	else if (red >  0.0 && green == 1.0 && blue == 0.0) red   -= colorInc;
	else if (red == 0.0 && green == 1.0 && blue <  1.0) blue  += colorInc;
	else if (red == 0.0 && green >  0.0 && blue == 1.0) green -= colorInc;
	else if (red <  1.0 && green == 0.0 && blue == 1.0) red   += colorInc;
	else if (red == 1.0 && green == 0.0 && blue >  0.0) blue  -= colorInc;
	else if (red == 1.0 && green == 0.0 && blue >  0.0) blue  -= colorInc;

	if (red > 1.0)   red   = 1.0;
	if (red < 0.0)   red   = 0.0;
	if (green > 1.0) green = 1.0;
	if (green < 0.0) green = 0.0;
	if (blue > 1.0)  blue  = 1.0;
	if (blue < 0.0)  blue  = 0.0;
}

