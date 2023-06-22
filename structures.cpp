#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <random>
#include <string>

#include "structures.hpp"

using namespace std;

void Stack::push(Cell *cell)
{
    Node *node = new Node(cell);
    if (header == nullptr)
    {
        end = node;
        header = node;
    }
    else
    {
        end->next = node;
        node->prev = end;
        end = node;
    }
    length++;
}

void Stack::pop()
{
    if (end == nullptr)
    {
        return;
    }
    if (length == 1)
    {
        end = nullptr;
        header = nullptr;
    }
    else
    {
        Node *popped = end;
        Node *prev = end->prev;
        prev->next = nullptr;
        popped->prev = nullptr;
        end = prev;
        delete popped;
    }
    length--;
}

Cell* Stack::getCurrCell()
{
    return end->cell;
}

int Stack::isEmpty()
{
    return header == nullptr;
}