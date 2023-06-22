#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <string>

#include "structures.hpp"
#include "menu.hpp"

using namespace std;

class Maze
{
private:
    int mazeW;
    int mazeH;
    int count;
    Cell **maze;
    float cellSize;
    Stack *stack;
    int W;
    int H;

public:
    Maze(int _mazeH, int _mazeW)
    {
        W = 800;
        H = 800;
        count = 0;
        mazeH = _mazeH;
        mazeW = _mazeW;
        if (mazeH > mazeW)
        {
            cellSize = (float)H / (float)mazeH;
        }
        else
        {
            cellSize = (float)W / (float)mazeW;
        }
        cellSize *= 0.95f;

        maze = new Cell *[mazeW];
        for (int i = 0; i < mazeW; i++)
            maze[i] = new Cell[mazeH];
        initializeMaze();

        stack = new Stack();
    }

    ~Maze()
    {
        delete stack;
        for (int i = 0; i < mazeW; i++)
            delete[] maze[i];
        delete[] maze;
    }

    void initializeMaze();
    void shuffleDirections(int directions[]);
    bool isValidCell(int x, int y);
    void recursiveBacktracking(int x, int y);
    void drawMaze(Menu *menu);
};

#endif