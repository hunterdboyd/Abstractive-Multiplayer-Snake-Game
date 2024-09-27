#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosList.h"
#include "ItemBin.h"
#include "cmdQueue.h"
//#include "objPosTree.h"  removed for lab 5

#include "objPosHash.h"

#define BINGO_ELEMENT_COUNT 5

// Forward Declaration
class GameMechs;
class ItemBin;
class objPosList;
class cmdQueue;
//class objPosBST;


class Player
{
    private:
        GameMechs* gmRef;

        // TARGET    
        objPosList* myPos;  // Lab 1/2 - Linked List / Array List
                            //  Discuss why Linked List performs better here

        //objPosBST* myBin;   // Lab 4 - collecting items and sort using BST    
        // Removed for lab 5

        objPosHashTable* myHTable;

        char** boardRef;
        ItemBin* binRef;

        char ctrlKeys[4];

        cmdQueue *myCmdQueue;

        int myScore;

        enum Direction {STOP, UP, DOWN, LEFT, RIGHT};
        enum Direction myDir;
        
        void undrawPlayer();  // used to erase the player position on the board before calculating the new position
        bool checkCollision();
        bool checkSelfCollision();

        void getMyElements();

        void updatePlayerFSM();        

    public:
        Player(int x, int y, char symbol, GameMechs* gm, ItemBin* bin, const char* control);
        ~Player();
        
        void drawPlayer();
        void movePlayer();        
        void increaseScore();

        int getScore() const;
        //void printBinContents() const;  //removed for lab 5
        void printHTableContents() const; // added for lab 5

        objPosList* getPlayerPos() const;
        // TARGET
    
        bool isMyControl(char thisChar) const;
        void receiveCommand(char thisCmd);
};

#endif