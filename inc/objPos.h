#ifndef OBJPOS_H
#define OBJPOS_H

// Advanced Object Position Class
//  If copied in 2SH4, it will CLEARLY show
// This is only used in 2SI3

class objPos
{
    private:
        int x;
        int y;
        int number;
        char prefix;
        char symbol;

    public:
        objPos();
        objPos(int xp, int yp, int num, char pref, char s);
        objPos(const objPos& thisPos); // copy constructor
        objPos& operator= (const objPos& thisPos); 
        // assignment operator overload - taking over how assignment should be done for this object

        int getX() const;
        int getY() const;
        int getNum() const;
        char getPF() const;
        char getSym() const;

        void setX(int xp);
        void setY(int yp);
        void setNum(int num);
        void setPF(char pref);
        void setSym(char sym);

        void copyObjPos(objPos &thisPos);

        bool isOverlap(const objPos* thisPos) const;

        void printObjPos() const;
};

#endif