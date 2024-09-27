#ifndef ITEMBIN_H
#define ITEMBIN_H

#include "objPos.h"
#include "objPosList.h"
#include "GameMechs.h"
#include "Player.h"
//#include "objPosStack.h"
#include "objPosDLinkedList.h"

#define LIST_SIZE 25

class GameMechs;
class Player;
//class objPosStack;
class objPosDLinkedList;

class ItemBin
{
    private:
        // Lab 3 - Stack
        // Generate 100 items, with pre-determined ranges of PF's and Nums
        //  So we can prep random food collections beforehand

        // objPosStack *myStack;   Removed to support unsorted random item list
        objPos myDrawItem;
        objPosList *myList;
                
        //objPos* myItem;     
                            
        GameMechs* gmRef;
        char** boardRef;

        void undrawItem();
        void DigitToChar(char result[]); // pass by ref

        void populateRandomItems();  // new method to populate random item list

    public:
        ItemBin(GameMechs* gm);
        ~ItemBin();

        void drawItem();
        void generateItem();
        objPos getItem();
        
        // pass by array!
        void pickItems(objPos list[], int size);
};

#endif