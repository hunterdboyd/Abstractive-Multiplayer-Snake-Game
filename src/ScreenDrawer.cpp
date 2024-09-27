#include "ScreenDrawer.h"
#include "MacUILib.h"

ScreenDrawer::ScreenDrawer(GameMechs* gm, ItemBin* bin)
{
    gmRef = gm;
    playerRef = gmRef->getPlayerListRef();
    playerCount = gmRef->getPlayerCount();
    binRef = bin;
}

ScreenDrawer::~ScreenDrawer()
{
    // No heap member, nothing to delete here
}

void ScreenDrawer::Draw() const
{
    // Clear the Screen
    MacUILib_clearScreen();

    // redraw all items;    
    binRef->drawItem();
    for(int i = 0; i < playerCount; i++)
        playerRef[i]->drawPlayer();

    // Get the Game Board 2D array
    char** drawTarget = gmRef->getBoardRef();
    objPos target = binRef->getItem();
    
    // Lab 1 - Compute Screen Drawing Complexity

    // Draw it on the screen
    for(int i = 0; i < gmRef->getBoardSizeY(); i++)
    {
        for(int j = 0; j < gmRef->getBoardSizeX(); j++)
        {
            MacUILib_printf("%c", drawTarget[i][j]);
        }

        MacUILib_printf("\t");  

        switch(i)
        {
            case 0:             
                MacUILib_printf("Player 1 Score: %d.  Character To Be Collected to Win:", playerRef[0]->getScore());  // Player 1   
                break;
            case 1:
                playerRef[0]->printHTableContents();
                break;
            case 2:
                break;

            case 4:
                if(playerCount >= 2)    
                    MacUILib_printf("Player 2 Score: %d.  Character To Be Collected to Win:", playerRef[1]->getScore());  // Player 2  
                break;
            case 5:
                if(playerCount >= 2)    
                    playerRef[1]->printHTableContents();
                break;
            case 6:
                break;

            case 8:
                if(playerCount >= 3)    
                    MacUILib_printf("Player 3 Score: %d.  Character To Be Collected to Win:", playerRef[2]->getScore());  // Player 3                   break;
                break;
            case 9:
                if(playerCount >= 3)    
                    playerRef[2]->printHTableContents();
                break;
            case 10:
                break;

            case 12:
                if(playerCount >= 4)    
                    MacUILib_printf("Player 4 Score: %d.  Character To Be Collected to Win:", playerRef[3]->getScore());  // Player 4                   break;
                break;
            case 13:
                if(playerCount >= 4)    
                    playerRef[3]->printHTableContents();
                break;
            case 14:  

            default:
                break;  
        }

        MacUILib_printf("\n");
    }

    // Append any required debugging message below
    //for(int i = 0; i < playerCount; i++)
    //    MacUILib_printf("Player%d Score: %d\n", i+1, playerRef[i]->getScore());

    // MacUILib_printf("Object: <%d, %d>, ID=%c%d\n", target.getX(), target.getY(), target.getPF(), target.getNum());    
}

void ScreenDrawer::DrawEndGame() const
{
    if(gmRef->getLoseFlag())
        MacUILib_printf("You have Lost!\n");
    else
        MacUILib_printf("Game Shuts Down\n");
}

void ScreenDrawer::DrawAverageComputationTime(double data) const
{
    MacUILib_printf("Average Computation Time: %.10f ms\n", data);
}