#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    // Set Default Board Size
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    cmd = 0;
    delayConst = 5000;
    playerCount = 0;

    // Allocate 2D gameboard on the Heap - distributed method
    gameBoard = new char*[boardSizeY];
    for(int i = 0; i < boardSizeY; i++)
    {
        gameBoard[i] = new char[boardSizeX];
    }

    playerList = new Player*[4];  // up to 4 players only

    // Set up the initiali game board boarders
    setInitBoard();  
}

GameMechs::~GameMechs()
{
    // Deallocate the rows first
    for(int i = 0; i < boardSizeY; i++)
    {
        delete[] gameBoard[i];
    }

    // Then deallocate the row lookup table.
    delete[] gameBoard;

    delete playerList;
}

void GameMechs::setInitBoard()  // private helper function
{
    for(int i = 0; i < boardSizeY; i++)
    {
        for(int j = 0; j < boardSizeX; j++)
        {
            if(i == 0 || i == (boardSizeY - 1) || j == 0 || j == (boardSizeX - 1))
                gameBoard[i][j] = '#';
            else
                gameBoard[i][j] = ' ';
        }
    }  
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

bool GameMechs::getExitFlag() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlag() const
{
    return loseFlag;
}

char GameMechs::getCMD() const
{
    return cmd;
}

char** GameMechs::getBoardRef() const
{
    return gameBoard;
}

Player** GameMechs::getPlayerListRef() const
{
    return playerList;
}

int GameMechs::getPlayerCount() const
{
    return playerCount;
}

int GameMechs::getWinScore() const
{
    return WIN_SCORE;
}

int GameMechs::getSpecialThreshold() const
{
    return WIN_SPECIAL_THRES;
}


void GameMechs::setExitFlag()  // private helper method
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()  // private helper method
{
    loseFlag = true;
}

bool GameMechs::checkInput()  // private
{
    while(MacUILib_hasChar())
    {        
        cmd = MacUILib_getChar();
        for(int i = 0; i < playerCount; i++)
        {
            if(playerList[i]->isMyControl(cmd))
            {
                playerList[i]->receiveCommand(cmd);
                return true;
            }
        }
    }

    return false;
}

void GameMechs::processInput()
{
    checkInput();
    
    switch(cmd)
    {
        case 27:
            setExitFlag();
            break;

        default:
            break;
    }
}

void GameMechs::applyDelay()
{
    MacUILib_Delay(delayConst);
}

void GameMechs::addPlayer(Player* pl)
{
    playerList[playerCount] = pl;
    playerCount++;
}

void GameMechs::setGameLost()
{
    setExitFlag();
    setLoseFlag();
}

/// New Performance Measurement Features
void GameMechs::startMeasurement()
{
    start = chrono::steady_clock::now();
}

void GameMechs::endMeasurementAndRecord()
{    
    elapsedTime = chrono::steady_clock::now() - start;
    totalTime += elapsedTime.count();
    iterCount++;    
}

double GameMechs::getAverageTime()
{
    if(iterCount == 0) return 0.0;
    return totalTime / iterCount;
}
