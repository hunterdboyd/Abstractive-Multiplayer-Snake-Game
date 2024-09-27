#ifndef OBJPOS_QUADRATIC_HASHING_H
#define OBJPOS_QUADRATIC_HASHING_H

#include "objPosHash.h"
#include "objPos.h"

class objPos;

class objPosQuadHashing : public objPosHashTable
{
    private:
        objPos* myHashTable;
        int calculateHashing(int prefix, int number) const;  // hashing function

    public:
        objPosQuadHashing();
        objPosQuadHashing(int);
        virtual ~objPosQuadHashing();

        bool insert(const objPos &thisPos);
        bool remove(const objPos &thisPos);  // lazy delete 
        bool isInTable(const objPos &thisPos) const;
        double getLambda() const;
        void printMe() const;
};

#endif