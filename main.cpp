#include <iostream>
#include <cmath>
#include <sstream>

#include <SFML/Graphics.hpp>

#define N 19 //numbers os quads
#define X 40 //lenght of side

int score = 0;
int fail = 3;
int dis = 0;
int scoreMax;

#include "game.h"

int main()
{
    Game game(5);
    game.game_process();
    return 0;
}

