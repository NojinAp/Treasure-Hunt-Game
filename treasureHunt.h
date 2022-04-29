/*
    ==================================================
    Treasure Hunt Game
    ==================================================
    Name   : Nozhin Azarpanah
    Date   : October 8, 2021
*/

#define MAX_LIVES 10
#define MIN_LIVES 1
#define MAX_PATH 70
#define MIN_PATH 10
#define PATH_WIDTH 5

struct PlayerInfo
{
    int num_lives;
    char player_symbol;
    int numTreasure;
    int position;
    char history[MAX_PATH];
    int visited[MAX_PATH];
};

struct GameInfo
{
    int maxNumMove;
    int path_length;
    int bombs[MAX_PATH];
    int treasure[MAX_PATH];
};