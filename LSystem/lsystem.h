/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#ifndef LSYSTEM_H
#define LSYSTEM_H

#include "main.h"

class LSystem
{
    public:
        LSystem(std::string title, std::string rule,
                float angle, float length, float shrink);
        void addRule(char variable, std::string rule);
        void draw();

        int addDepth();
        int decDepth();
        void setDepth(int newDepth);

        std::string getTitle();

    protected:
        void drawLine();
        void readRule(std::string rule, int depth);

        std::string title;
        std::string initRule;
        std::vector<std::string> rules;
        std::string variables;

        float angle;
        float length;
        float shrink;

        double colorInc;
        float red;
        float green;
        float blue;

        int depth;
};

extern std::vector<LSystem> systems;
extern std::vector<LSystem>::iterator L;

void initSystems();

#endif // LSYSTEM_H
