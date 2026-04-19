#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "Tilemap.h"
#include <windows.h>

/*
    Game game;
    game.run();
*/


//a mettre pour le build
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Game game;
    game.run();

    return 0;
}

//a mettre pour le playmode
/*
int main()
{

    Game game;
    game.run();
    


    return 0;
}*/