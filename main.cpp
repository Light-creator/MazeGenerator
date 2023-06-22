#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <string>
#include <ctime>

#include "menu.hpp"
#include "structures.hpp"
#include "maze.hpp"

using namespace std;

const int W = 800;
const int H = 800;

float transitionAlpha = 2.0f;


Menu *menu = new Menu;
Maze *maze;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, H, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (menu->isTransitioning())
    {
        maze->drawMaze(menu); 
    }
    else if(menu->isTransitioningInfo()) {
        menu->drawInfo();
    }
    else
    {
        menu->drawMenu();
    }

    glFlush();
}

void createMenu()
{
    menu->add(W/2-100, H/2-100, 200, 30, _INPUT, "Width");
    menu->add(W/2-100, H/2-40, 200, 30, _INPUT, "Height");
    menu->add(W/2-75, H/2, 150, 30, _BUTTON, "Create");
    menu->add(W-75, H-40, 30, 30, _BUTTON, "i");
    menu->add(W-75, 40, 30, 30, _BUTTON, "<-");
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    menu->addText(key);
}

void initMaze() {
    int w = menu->getWidthorHeight("Width");
    int h = menu->getWidthorHeight("Height");
    cout << w << " " << h << endl;
    float start = clock();
    maze = new Maze(h, w);
    maze->recursiveBacktracking(0, 0);
    float end = clock();
    float t = (end - start) / CLOCKS_PER_SEC;
    cout << "Time: " << t << endl;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        bool f = menu->checkCoordinates(x, y);
        if(f) initMaze();

        glutPostRedisplay(); // Trigger a redraw
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutCreateWindow("2D Maze");

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    createMenu();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}