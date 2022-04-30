/*
    ==================================================
    Treasure Hunt Game
    ==================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "treasureHunt.h"

int main() 
{
    struct PlayerInfo playerone;
    struct GameInfo gameone;
    printf("================================\n");
    printf("         Treasure Hunt!         ");
    printf("\n================================\n\n");
    printf("PLAYER Configuration\n");
    printf("--------------------\n");
    printf("Enter a single character to represent the player: ");
    scanf("%c", &playerone.player_symbol);

    do
    {
        printf("Set the number of lives: ");
        scanf("%d", &playerone.num_lives);
        if (playerone.num_lives < MIN_LIVES || playerone.num_lives > MAX_LIVES)
        {
            printf("     Must be between 1 and 10!\n");

        }

    } while (playerone.num_lives < MIN_LIVES || playerone.num_lives > MAX_LIVES);

    printf("Player configuration set-up is complete\n\n");
    printf("GAME Configuration\n");
    printf("------------------\n");

    do
    {
        printf("Set the path length (a multiple of 5 between 10-70): ");
        scanf("%d", &gameone.path_length);
        if (gameone.path_length < MIN_PATH || gameone.path_length > MAX_PATH || gameone.path_length % PATH_WIDTH != 0)
        {
            printf("     Must be a multiple of 5 and between 10-70!!!\n");
        }

    } while (gameone.path_length < MIN_PATH || gameone.path_length > MAX_PATH || gameone.path_length % PATH_WIDTH != 0);

    int maxMoves = gameone.path_length * 0.75;

    do
    {
        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &gameone.maxNumMove);

        if (gameone.maxNumMove < 3 || gameone.maxNumMove > maxMoves)
        {

            printf("    Value must be between 3 and %d\n", maxMoves);
        }

    } while (gameone.maxNumMove < 3 || gameone.maxNumMove > maxMoves);

    printf("\nBOMB Placement\n");
    printf("--------------\n");
    printf("Enter the bomb positions in sets of 5 where a value\n");
    printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gameone.path_length);

    int i, j;

    for (i = 0; i < gameone.path_length; i += 5)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + 5);

        for (j = i; j < i + 5; j++)
        {
            scanf("%d", &gameone.bombs[j]);
        }
    }

    printf("BOMB placement set\n");
    printf("\nTREASURE Placement\n");
    printf("------------------\n");
    printf("Enter the treasure placements in sets of 5 where a value\n");
    printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gameone.path_length);

    for (i = 0; i < gameone.path_length; i += 5)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
        for (j = i; j < i + 5; j++)
        {
            scanf("%d", &gameone.treasure[j]);
        }
    }

    printf("TREASURE placement set\n");
    printf("\nGAME configuration set-up is complete...\n");
    printf("\n------------------------------------\n");
    printf("TREASURE HUNT Configuration Settings\n");
    printf("------------------------------------\n");
    printf("Player:\n");
    printf("   Symbol     : %c\n", playerone.player_symbol);
    printf("   Lives      : %d\n", playerone.num_lives);
    printf("   Treasure   : [ready for gameplay]\n");
    printf("   History    : [ready for gameplay]\n");
    printf("\nGame:\n");
    printf("   Path Length: %d\n", gameone.path_length);
    printf("   Bombs      : ");

    for (i = 0; i < gameone.path_length; i++)
    {
        printf("%d", gameone.bombs[i]);
    }

    printf("\n   Treasure   : ");

    for (i = 0; i < gameone.path_length; i++)
    {
        printf("%d", gameone.treasure[i]);
    }
    printf("\n\n====================================");
    printf("\n~ Get ready to play TREASURE HUNT! ~\n");
    printf("====================================\n");

    for (i = 0; i < gameone.path_length; i++)
    {
        playerone.history[i] = '-';
    }
    playerone.position = 0;
    playerone.numTreasure = 0;

    do
    {
        if (playerone.position != 0) 
        {
            printf("\n  ");
            for (i = 1; i <= gameone.path_length; i++)
            {
                if (i == playerone.position) 
                {
                    printf("%c", playerone.player_symbol);
                }
                else 
                {
                    printf(" ");
                }
            }
        }
        printf("\n  ");
        for (i = 0; i < gameone.path_length; i++)
        {
            printf("%c", playerone.history[i]);
        }
        printf("\n  ");
        for (i = 1; i < (gameone.path_length + 1); i++)
        {
            if (i % 10 == 0) 
            {
                printf("%d", i / 10);
            }
            else 
            {
                printf("|");
            }
        }
        printf("\n  ");

        for (i = 1; i < (gameone.path_length + 1); i++)
        {
            if (i % 10 == 0) 
            {
                printf("0");
            }
            else if (i < 10) 
            {
                printf("%d", i);
            }
            else if (i > 10) 
            {
                printf("%d", i % 10);
            }
        }
        printf("\n+---------------------------------------------------+");
        printf("\n  Lives:%3d  | Treasures:%3d  |  Moves Remaining:%3d", playerone.num_lives, playerone.numTreasure, gameone.maxNumMove);
        printf("\n+---------------------------------------------------+");

        do
        {
            printf("\nNext Move [1-%d]: ", gameone.path_length);
            scanf("%d", &playerone.position);
            if (playerone.position < 1 || playerone.position>gameone.path_length)
            {
                printf("  Out of Range!!!");
            }

        } while (playerone.position < 1 || playerone.position>gameone.path_length);

        if (gameone.bombs[playerone.position - 1] == 1 && gameone.treasure[playerone.position - 1] == 0 && playerone.history[playerone.position - 1] == '-') 
        {
            printf("\n===============> [!] !!! BOOOOOM !!! [!]\n");
            playerone.num_lives--;
            gameone.maxNumMove--;
            playerone.history[playerone.position - 1] = '!';
        }
        else if (gameone.treasure[playerone.position - 1] == 1 && gameone.bombs[playerone.position - 1] == 0 && playerone.history[playerone.position - 1] == '-') 
        {
            printf("\n===============> [$] $$$ Found Treasure! $$$ [$]\n");
            gameone.maxNumMove--;
            playerone.history[playerone.position - 1] = '$';
            playerone.numTreasure++;

        }
        else if (gameone.treasure[playerone.position - 1] == 1 && gameone.bombs[playerone.position - 1] == 1 && playerone.history[playerone.position - 1] == '-') 
        {
            printf("\n===============> [&] !!! BOOOOOM !!! [&]\n");
            printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n");
            gameone.maxNumMove--;
            playerone.num_lives--;
            playerone.history[playerone.position - 1] = '&';
            playerone.numTreasure++;
        }
        else if (gameone.treasure[playerone.position - 1] == 0 && gameone.bombs[playerone.position - 1] == 0 && playerone.history[playerone.position - 1] == '-') 
        {
            printf("\n===============> [.] ...Nothing found here... [.]\n");
            gameone.maxNumMove--;
            playerone.history[playerone.position - 1] = '.';
        }
        else if (playerone.history[playerone.position - 1] != '-') 
        {
            printf("\n===============> Dope! You've been here before!\n");
        }
    } while (playerone.num_lives > 0 && gameone.maxNumMove > 0);

    printf("\nNo more LIVES remaining!\n");

    if (playerone.position != 0) 
    {
        printf("\n  ");
        for (i = 1; i <= gameone.path_length; i++)
        {
            if (i == playerone.position)
            {
                printf("%c", playerone.player_symbol);
            }
            else 
            {
                printf(" ");
            }
        }
    }

    printf("\n  ");

    for (i = 0; i < gameone.path_length; i++)
    {
        printf("%c", playerone.history[i]);
    }

    printf("\n  ");

    for (i = 1; i < (gameone.path_length + 1); i++)
    {
        if (i % 10 == 0)
        {
            printf("%d", i / 10);
        }
        else
        {
            printf("|");
        }
    }

    printf("\n  ");

    for (i = 1; i < (gameone.path_length + 1); i++)
    {
        if (i % 10 == 0) 
        {
            printf("0");
        }
        else if (i < 10) 
        {
            printf("%d", i);
        }
        else if (i > 10) 
        {
            printf("%d", i % 10);
        }
    }

    printf("\n+---------------------------------------------------+");
    printf("\n  Lives:%3d  | Treasures:%3d  |  Moves Remaining:%3d", playerone.num_lives, playerone.numTreasure, gameone.maxNumMove);
    printf("\n+---------------------------------------------------+");
    printf("\n\n##################");
    printf("\n#   Game over!   #");
    printf("\n##################");
    printf("\n\nYou should play again and try to beat your score!");

    return 0;
}
