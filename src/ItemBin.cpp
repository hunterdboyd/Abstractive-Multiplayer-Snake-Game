#include "ItemBin.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

ItemBin::ItemBin(GameMechs* gm)
{
    srand(time(NULL));    
    
    gmRef = gm;
    boardRef = gmRef->getBoardRef();  
    //myItem = new objPos(12, 12, 32, 'A', '*');  
    //myStack = new objPosStack();
    //myStack->populateRandomElements(STACK_SIZE);
    
    myList = new objPosDLinkedList();
    populateRandomItems();

    myDrawItem = myList->getNext();
    // myDrawItem.printObjPos();    
}

ItemBin::~ItemBin()
{
    delete myList;
}

void ItemBin::drawItem()
{   
    int x = myDrawItem.getX();
    int y = myDrawItem.getY();
    char num[2];  // convert number to displayable chars
    DigitToChar(num);

    boardRef[y][x] = myDrawItem.getSym();
    boardRef[y-1][x-1] = myDrawItem.getPF();
    boardRef[y-1][x] = num[0];
    boardRef[y-1][x+1] = num[1];
}

void ItemBin::populateRandomItems()
{
    objPos temp(0,0,0,0,0);  
    int randCandidate;

    for(int i = 0; i < LIST_SIZE; i++)
    {
        // Generate Prefix
        randCandidate = rand() % 26 + 'A';  // generaate 26 upper case alphabets
        //if(rand() % 2) randCandidate += 32;  // randomly lowercase the candidate - No longer used for simplicity
        temp.setPF((char)randCandidate);

        // Generate Number [0, 99]
        temp.setNum(rand() % 100);

        // Symbol should be fixed to *
        temp.setSym('*');

        // Push every randomly generately objPos into the Stack.
        myList->insertHead(temp);
    }
}

void ItemBin::undrawItem()
{
    int x = myDrawItem.getX();
    int y = myDrawItem.getY();

    if(x == 0 || y == 0) return;

    boardRef[y][x] = ' ';
    boardRef[y-1][x-1] = ' ';
    boardRef[y-1][x] = ' ';
    boardRef[y-1][x+1] = ' ';
}

void ItemBin::DigitToChar(char result[])
{
    int number = myDrawItem.getNum();
    result[0] = (number / 10) + '0';
    result[1] = (number % 10) + '0';
}

// TARGET    
void ItemBin::generateItem()
{
    // Step 1: Get Player Ref from GameMech for Player pos
    Player** plList = gmRef->getPlayerListRef();
    int playerCount = gmRef->getPlayerCount();
    
    // to prevent stack overflow
    int xsize = gmRef->getBoardSizeX();
    int ysize = gmRef->getBoardSizeY();
    int** bitVec = new int*[xsize];
    for(int i = 0; i < xsize; i++)
    {
        bitVec[i] = new int[ysize];
        for(int j = 0; j < ysize; j++)
            bitVec[i][j] = 0;
    } 

    objPosList *playerPos;    
    int playerLength;
    objPos target;    

    for(int j = 0; j < playerCount; j++)
    {
        playerPos = plList[j]->getPlayerPos();
        playerLength = playerPos->getSize();
        playerPos->resetReadPos();

        for(int i = 0; i < playerLength; i++)
        {
            target = playerPos->getNext();
            bitVec[target.getX()][target.getY()] = 1;        
        }    
    }    


    int randCandidateX = 0;
    int randCandidateY = 0;

    // Lab 3 - pre-generated items follow your own generation trend without
    //  spending time in runtime calculation.
        do
        {
            randCandidateX = rand() % (gmRef->getBoardSizeX() - 4) + 2;
            randCandidateY = rand() % (gmRef->getBoardSizeY() - 4) + 2;
        } while(bitVec[randCandidateX][randCandidateY] != 0);
    
    undrawItem();  
    
    myDrawItem = myList->getNext();
    if(myDrawItem.getX() == -99) // end of stack items
    {
        gmRef->setExitFlag();
        return;
    }

    myDrawItem.setX(randCandidateX);
    myDrawItem.setY(randCandidateY);

    drawItem();   

    for(int i = 0; i < xsize; i++)// Theta(m)
        delete[] bitVec[i];// Theta(1)
    delete[] bitVec;// Theta(1) 
}

objPos ItemBin::getItem()
{
    return myDrawItem;
}

void ItemBin::pickItems(objPos list[], int size)
{
    int bitVec[LIST_SIZE] = {0};
    int count = 0;
    int candidate = 0;

    while(count < size)
    {
        candidate = rand() % LIST_SIZE;
        if(bitVec[candidate] == 0)
        {
            bitVec[candidate] = 1;
            list[count] = myList->get(candidate);
            count++;
        }
    }
}


