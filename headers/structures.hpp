#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <string>

using namespace std;

struct Cell{
    bool visited;
    bool top_wall;
    bool right_wall;
    bool bottom_wall;
    bool left_wall;
    int x;
    int y;
};

struct Node{
    Cell *cell;
    Node *next;
    Node *prev;

    Node(Cell *_cell) {
        cell = _cell;
        next = nullptr;
        prev = nullptr;
    }
};

class Stack {
private:
    Node *header;
    Node *end;
    int length;

public:
    Stack() {
        header = nullptr;
        end = nullptr;
        length = 0;
    }

    Stack(Cell *cell) {
        Node *node = new Node(cell);
        header = node;
        end = node;
        length = 1;
    }

    void push(Cell *cell);
    void pop();
    Cell *getCurrCell();
    int isEmpty();
};

#endif // STRUCTURES_H_INCLUDED