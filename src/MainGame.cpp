#include "MacUILib.h"
#include "GameMechs.h"
#include "ScreenDrawer.h"
#include "Player.h"
#include "ItemBin.h"

#include <chrono>
#include <iostream>


using namespace std;

// Global References


int main(int argc, char* argv[])
{
    // DECLARATION (LOCAL, on Stack)
    //////////////////////////////

    #define MAX_PLAYER_COUNT 3

    GameMechs *myGM;
    ScreenDrawer *myDrawer;
    Player *player[MAX_PLAYER_COUNT];
    ItemBin* myBin;
    int iterCount = 0;


    // INITIALIZATION
    //////////////////////////////
    MacUILib_init();                            // Initialilze MacUI Library

    myGM = new GameMechs();                     // Create GM instance on the heap        
    myBin = new ItemBin(myGM);                  // Create the item bin on the heap
    myBin->generateItem();          

    player[0] = new Player(3, 3, '@', myGM, myBin, "wsad");      // Create first Player on the heap
    player[1] = new Player(12, 12, '&', myGM, myBin, "ikjl");      // Create second Player on the heap
    
    myDrawer = new ScreenDrawer(myGM, myBin); // Create Screen Drawer Module on the heap
    
    
    

    //////////////////////////////
    // PROGRAM LOOP
    //////////////////////////////
    while(myGM->getExitFlag() == false)
    {
        // I. GET INPUT
        myGM->processInput();
               
        if(iterCount % 10 == 0)
        {
            // II. RUN LOGIC 
            for(int i = 0; i < myGM->getPlayerCount(); i++)
                player[i]->movePlayer();        
         
            // III. DRAW SCREEN  
            myDrawer->Draw();    
        }           

        // IV. LOOP DELAY
        myGM->applyDelay();
        iterCount++; 
    }



    // CLEANUP
    //////////////////////////////
    myDrawer->DrawEndGame();

    MacUILib_uninit();
    for(int i = 0; i < myGM->getPlayerCount(); i++)
        delete player[i];
    delete myGM;            // Remove GM instance on the heap
    delete myDrawer;    
    delete myBin;

    return 0;
}