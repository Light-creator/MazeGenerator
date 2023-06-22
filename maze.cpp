#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <string>

#include "menu.hpp"
#include "structures.hpp"
#include "maze.hpp"

using namespace std;

void Maze::initializeMaze()
{
    // !
    for (int i = 0; i < mazeW; i++)
    {
        for (int j = 0; j < mazeH; j++)
        {
            maze[i][j].visited = false;
            maze[i][j].top_wall = true;
            maze[i][j].right_wall = true;
            maze[i][j].bottom_wall = true;
            maze[i][j].left_wall = true;
            maze[i][j].y = j;
            maze[i][j].x = i;
        }
    }
}

void Maze::shuffleDirections(int directions[])
{
    for (int i = 3; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = directions[i];
        directions[i] = directions[j];
        directions[j] = temp;
    }
}

// Function to check if a cell is valid
bool Maze::isValidCell(int x, int y)
{
    return (x >= 0 && x < mazeW && y >= 0 && y < mazeH && !maze[x][y].visited);
}

// Function to perform Recursive Backtracking algorithm
void Maze::recursiveBacktracking(int x, int y)
{
    if (count == mazeH * mazeW || x > mazeW || y > mazeH)
        return;
    //cout << x << " " << y << " => ";
    //cout << count << endl;
    int f = 0;
    int dx[] = {0, 1, 0, -1}; // Directions: up, right, down, left
    int dy[] = {-1, 0, 1, 0};

    maze[x][y].visited = true;
    // Randomly shuffle the directions
    int directions[] = {0, 1, 2, 3};
    shuffleDirections(directions);

    for (int i = 0; i < 4; i++)
    {
        int nextX = x + dx[directions[i]];
        int nextY = y + dy[directions[i]];

        if (isValidCell(nextX, nextY))
        {
            // Remove the wall between the current cell and the next cell
            if (directions[i] == 0)
            { // Up
                maze[x][y].top_wall = false;
                maze[nextX][nextY].bottom_wall = false;
            }
            else if (directions[i] == 1)
            { // Right
                maze[x][y].right_wall = false;
                maze[nextX][nextY].left_wall = false;
            }
            else if (directions[i] == 2)
            { // Down
                maze[x][y].bottom_wall = false;
                maze[nextX][nextY].top_wall = false;
            }
            else if (directions[i] == 3)
            { // Left
                maze[x][y].left_wall = false;
                maze[nextX][nextY].right_wall = false;
            }
            f = 1;
            count++;
            Cell *cell = &maze[x][y];
            stack->push(cell);
            recursiveBacktracking(nextX, nextY);
            break;
        }
    }

    if (!f)
    {
        stack->pop();
        if (stack->isEmpty() || x > mazeW || y > mazeH)
            return;

        Cell *currCell = stack->getCurrCell();
        recursiveBacktracking(currCell->x, currCell->y);
    }
}

// Function to draw the maze
void Maze::drawMaze(Menu *menu)
{
    menu->drawBack();
    glPushMatrix();
    //glTranslatef(0.0f, 0.0f, 0.0f);
    glTranslatef((W-mazeW * cellSize) / 2.0f, (H-mazeH * cellSize) / 2.0f, 0.0f);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    // !
    int i, j;
    for (i = 0; i < mazeW; i++)
    {
        for (j = 0; j < mazeH; j++)
        {
            glBegin(GL_LINES);
            if (maze[i][j].top_wall)
            {
                glVertex2f(i * cellSize, j * cellSize);
                glVertex2f(i * cellSize + cellSize, j * cellSize);
            }
            if (maze[i][j].left_wall)
            {
                glVertex2f(i * cellSize, j * cellSize);
                glVertex2f(i * cellSize, j * cellSize + cellSize);
            }
            glEnd();
        }
    }
    glBegin(GL_LINES);
    glVertex2f(i * cellSize, 0);
    glVertex2f(i * cellSize, j * cellSize);
    glVertex2f(0, j * cellSize);
    glVertex2f(i * cellSize, j * cellSize);
    glEnd();

    glPopMatrix();
}