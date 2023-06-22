#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <string>

using namespace std;

enum types{
    _BUTTON, _INPUT
};

struct Entity{
   int x;
   int y;
   int w;
   int h;
   types type;
   string label;
   string text;
   bool isActive;
};

class Menu{
private:
    Entity *el;
    int len;
    int W;
    int H;
    bool isTr;
    bool isTrInfo;
public:
    Menu() {
        el = new Entity[10];
        len = 0;
        H = 800;
        W = 800;
        isTr = false;
    }

    ~Menu() {
        delete[] el;
    }

    void add(int _x, int _y, int _w, int _h, types _type, string _label);

    void drawElements();
    void drawInput(Entity el);
    void drawButton(Entity el);
    void drawMenu();
    void drawInfo();
    void drawBack();

    int getWidthorHeight(string label);

    void addText(unsigned char key);
    bool checkCoordinates(int x, int y);
    bool isTransitioning();
    bool isTransitioningInfo();

};

#endif 