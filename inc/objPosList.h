// Abstract Class - Interface
#ifndef OBJPOSLIST_H
#define OBJPOSLIST_H

#include "objPos.h"

class objPos;  // forward declaration

class objPosList
{
    public:        
        virtual ~objPosList(){}

        virtual int getSize() = 0;
        virtual int isEmpty() = 0;

        virtual void insertHead(const objPos &thisPos) = 0;
        virtual void insertTail(const objPos &thisPos) = 0;
        virtual void insert(const objPos &thisPos, int index) = 0;
        
        virtual objPos getHead() const = 0;
        virtual objPos getTail() const = 0;
        virtual objPos get(int index) const = 0;
        virtual objPos getNext() = 0;
        virtual void resetReadPos() = 0;
        virtual void set(const objPos &thisPos, int index) = 0;

        virtual objPos removeHead() = 0;
        virtual objPos removeTail() = 0;
        virtual objPos remove(int index) = 0;

        virtual void printList() const = 0;
};

#endif