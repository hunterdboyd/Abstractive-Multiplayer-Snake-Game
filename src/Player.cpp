#include "Player.h"
#include "objPosDLinkedList.h"
#include "objPosDoubleHashing.h"
#include "objPosQuadHashing.h"

#include <iostream>
using namespace std;

Player::Player(int x, int y, char symbol, GameMechs* gm, ItemBin* bin, const char* control)
{
    //myPos = new objPos(x, y, -1, 0, symbol);  // TARGET
    myPos = new objPosDLinkedList();

    // Lab 2 validation method
    //for(int i = 0; i < 10000; i++)
        myPos->insertHead(objPos(x, y, -1, 0, symbol));

    ctrlKeys[0] = control[0];
    ctrlKeys[1] = control[1];
    ctrlKeys[2] = control[2];
    ctrlKeys[3] = control[3];

    gmRef = gm;
    boardRef = gmRef->getBoardRef();
    binRef = bin;

    myDir = STOP;
    myScore = 0;

    gmRef->addPlayer(this);

    myCmdQueue = new cmdQueue();

    // To be modified Lab 5
    // To be modified Lab 5
    // To be modified Lab 5
    //myBin = new objPosBST();

    myHTable = new objPosQuadHashing();
    //myHTable = new objPosDoubleHashing();
    getMyElements();
}

Player::~Player()
{
    delete myPos;
    delete myCmdQueue;
    delete myHTable;
}

void Player::getMyElements()
{
    objPos selectedList[BINGO_ELEMENT_COUNT];
    binRef->pickItems(selectedList, BINGO_ELEMENT_COUNT);

    for(int i = 0; i < BINGO_ELEMENT_COUNT; i++)
    {
        myHTable->insert(selectedList[i]);
    }
}


void Player::updatePlayerFSM()  // private
{
    //char cmd = gmRef->getCMD();    
    char cmd = myCmdQueue->dequeue();
    if(cmd == 0) return;  // i.e. no chars

    if(cmd == ctrlKeys[0] && myDir != DOWN) myDir = UP;
    else if(cmd == ctrlKeys[1] && myDir != UP) myDir = DOWN;
    else if(cmd == ctrlKeys[2] && myDir != RIGHT) myDir = LEFT;
    else if(cmd == ctrlKeys[3] && myDir != LEFT) myDir = RIGHT;    
}

void Player::movePlayer()
{    
    updatePlayerFSM();
    if(myDir == STOP) return;
    
    undrawPlayer();
    
    objPos currHeadPos = myPos->getHead();
    int inX = currHeadPos.getX();
    int inY = currHeadPos.getY();
    // TARGET    
    
    switch(myDir)
    {
        case UP:            
            if(--inY < 1) 
                inY = gmRef->getBoardSizeY() - 2;
            break;

        case DOWN:
            if(++inY > (gmRef->getBoardSizeY() - 2))
                inY = 1;
            break;

        case LEFT:
            if(--inX < 1) 
                inX = gmRef->getBoardSizeX() - 2;
            break;

        case RIGHT:
            if(++inX > (gmRef->getBoardSizeX() - 2))
                inX = 1;
            break;

        default:
            break;
    }

    currHeadPos.setX(inX);
    currHeadPos.setY(inY);// TARGET
    
    myPos->insertHead(currHeadPos);  // insert new head    
    
    if(!checkCollision())            // check collision.  If collision never happened,
        myPos->removeTail();         // removeTail.  Otherwise, generate new item.

    if(checkSelfCollision())
        gmRef->setGameLost();       // If colliding with itself, end game.
    
}

// TARGET
    
bool Player::checkCollision()  // private
{    
    // 1. Check Item Bin for Item ObjPos
    objPos target = binRef->getItem();
    bool collided = myPos->getHead().isOverlap(&target);

    // 2. check whether objPos are equal
    if(collided)
    {
        // 3. If yes, collision takes place
        // Generate New Item(s)
        binRef->generateItem();

        // Increase Score by Number
        myScore += target.getNum();
        if(myScore >= gmRef->getWinScore())
        {
            gmRef->setExitFlag();
            // or, set win flag with player identification
        }           

        // New in Lab 5
        // New in Lab 5
        // New in Lab 5
        if(myHTable->isInTable(target))
        {
            myHTable->remove(target);
            if(myHTable->getLambda() <= 0.001) // take into account float approx range
            {
                gmRef->setExitFlag();
            }
        }

    }

    return collided;
}

bool Player::checkSelfCollision()  // private
{    
    // Make sure snake is long enough to kill itself
    int length = myPos->getSize();
    if(length < 4) return false;

    // Then check for self collision
    myPos->resetReadPos();
    objPos tempPos;
    objPos headPos = myPos->getNext();

    for(int i = 1; i < length; i++)
    {
        tempPos = myPos->getNext();
        if(headPos.isOverlap(&tempPos))
        {
            // set game end.
            return true;
        }
    }

    return false;
}



void Player::drawPlayer() 
{
    objPos targetPos;
    int scanSize = myPos->getSize();  // get the list size

    myPos->resetReadPos();
    for(int i = 0; i < scanSize; i++)
    {
        targetPos = myPos->getNext();
        boardRef[targetPos.getY()][targetPos.getX()] = targetPos.getSym();
    }    
    
}// TARGET
    

void Player::undrawPlayer()  // private helper function
{
    objPos targetPos;
    int scanSize = myPos->getSize();  // get the list size
 
    myPos->resetReadPos();
    for(int i = 0; i < scanSize; i++)
    {
        targetPos = myPos->getNext();
        boardRef[targetPos.getY()][targetPos.getX()] = ' ';
    }
}// TARGET
    


void Player::increaseScore()
{
    myScore++;
}

int Player::getScore() const
{
    return myScore;
    //return myPos->getSize();
}

objPosList* Player::getPlayerPos() const
{
    return myPos;
}// TARGET

// Removed for Lab 5
/*void Player::printBinContents() const
{
    myBin->printTree();
}
*/

void Player::printHTableContents() const
{
    myHTable->printMe();
}


bool Player::isMyControl(char thisChar) const
{
    for(int i = 0; i < 4; i++)
    {
        if(thisChar == ctrlKeys[i])
            return true;
    }

    return false;
}

void Player::receiveCommand(char thisCmd)
{
    myCmdQueue->enqueue(thisCmd);
}

