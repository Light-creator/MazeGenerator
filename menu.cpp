#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <string>

#include "menu.hpp"

using namespace std;

void Menu::add(int _x, int _y, int _w, int _h, types _type, string _label)
{
    el[len].x = _x;
    el[len].y = _y;
    el[len].w = _w;
    el[len].h = _h;
    el[len].type = _type;
    el[len].text = "";
    el[len].label = _label;
    el[len].isActive = false;
    len++;
}

void Menu::drawElements()
{
    for (int i = 0; i < len; i++)
    {
        if (el[i].type == _BUTTON && el[i].label != "<-")
        {
            drawButton(el[i]);
        }
        else if (el[i].type == _INPUT)
        {
            drawInput(el[i]);
        }
    }
}

void drawHeading(string t) {
    void *font = GLUT_BITMAP_HELVETICA_18;
    for (char c : t)
    {
        glutBitmapCharacter(font, c);
    }
}

void drawText(string t) {
    void *font = GLUT_BITMAP_HELVETICA_12;
    for (char c : t)
    {
        glutBitmapCharacter(font, c);
    }
}

void Menu::drawInput(Entity el)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2i(el.x, el.y);
    glVertex2i(el.x + el.w, el.y);
    glVertex2i(el.x + el.w, el.y + el.h);
    glVertex2i(el.x, el.y + el.h);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glRasterPos2i(el.x, el.y-7);
    drawText(el.label);


    // Position the text at the center of the input field
    int textX = el.x + 5;
    int textY = el.y + el.h / 2 - 5;

    // Draw the input text
    glRasterPos2i(textX, textY);
    void *font = GLUT_BITMAP_HELVETICA_12;
    for (char c : el.text)
    {
        glutBitmapCharacter(font, c);
    }

    // Draw the cursor if the input field is active
    if (el.isActive)
    {
        int cursorX = textX + glutBitmapWidth(font, '|');
        glRasterPos2i(cursorX, textY);
        glutBitmapCharacter(font, '|');
    }
}

void Menu::drawButton(Entity el)
{

    if (el.isActive)
        glColor3f(0.5f, 0.5f, 0.5f); // Dark gray when pressed
    else
        glColor3f(0.8f, 0.8f, 0.8f); // Light gray otherwise

    // Draw the button rectangle
    glBegin(GL_QUADS);
    glVertex2i(el.x, el.y);
    glVertex2i(el.x + el.w, el.y);
    glVertex2i(el.x + el.w, el.y + el.h);
    glVertex2i(el.x, el.y + el.h);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glRasterPos2i(el.x+el.w*0.4, el.y+el.h*0.6);
    drawText(el.label);
    glColor3f(0.8f, 0.8f, 0.8f);
}

void Menu::addText(unsigned char key)
{
    for (int i = 0; i < len; i++)
    {
        if (el[i].isActive && el[i].type == _INPUT)
        {
            if (key == 13) // ASCII value for Enter key
            {
                cout << "Input: " << el[i].text << endl;
                el[i].isActive = false;
            }
            else if (key == 8) // ASCII value for Backspace key
            {
                if (!el[i].text.empty())
                    el[i].text.pop_back();
            }
            else
            {
                el[i].text += key;
            }

            glutPostRedisplay(); // Trigger a redraw
        }
    }
}

bool Menu::checkCoordinates(int x, int y)
{
    bool f = false;
    for (int i = 0; i < len; i++)
    {
        if (x >= el[i].x && x <= el[i].x + el[i].w && y >= el[i].y && y <= el[i].y + el[i].h)
        {
            el[i].isActive = true;
            if (el[i].type == _BUTTON && el[i].label == "Create")
            {
                isTr = true;
                f = true;
            } else if(el[i].type == _BUTTON && el[i].label == "i") {
                isTrInfo = true;
            } else if(el[i].type == _BUTTON && el[i].label == "<-") {
                isTrInfo = false;
                isTr = false;
            }
        }
        else
        {
            el[i].isActive = false;
        }
    }
    return f;
}

int Menu::getWidthorHeight(string label) {
    for(int i=0; i<len; i++) {
        if(el[i].label == label) {
            int n = stoi(el[i].text);
            if(n<3 || n>1100)
                return 10;
            else 
                return n;
        }
    }
    return 10;
}

bool Menu::isTransitioning()
{
    return isTr;
}

bool Menu::isTransitioningInfo()
{
    return isTrInfo;
}

void Menu::drawBack() {
    for (int i = 0; i < len; i++)
    {
        if (el[i].type == _BUTTON && el[i].label == "<-")
        {
            drawButton(el[i]);
        }
    } 
}

void Menu::drawInfo()
{
    int padX, padY;
    padX = 30;
    padY = 40;

    drawBack(); 

    glColor3f(0.8f, 0.8f, 0.8f); // Light gray
    string h1 = "About";
    string s1 = "The work was performed by: Ivan Ibadullaev and Klimenty Zobov";
    string s2 = "Group: 4851003/20001";

    string h2 = "Info";
    string s3 = "This program is for generating various mazes.";
    string s4 = "To create a maze, enter the width and height in the main menu and then click create.";

    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glRasterPos2i(padX, padY);
    drawHeading(h1);

    glRasterPos2i(padX, padY+40);
    drawText(s1);

    glRasterPos2i(padX, padY+65);
    drawText(s2);

    glRasterPos2i(padX, padY+115);
    drawHeading(h2);

    glRasterPos2i(padX, padY+155);
    drawText(s3);

    glRasterPos2i(padX, padY+180);
    drawText(s4);

    // Swap the buffers to display the rendered image
    glutSwapBuffers();
}

void Menu::drawMenu()
{
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray

    drawElements();
    
    // Swap the buffers to display the rendered image
    glutSwapBuffers();
}


