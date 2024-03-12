//
//  main.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 04/01/2024.
//
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>

#include "Game.hpp"


Game* game = nullptr;

int main() {
    printf("%s\n", SDL_GetBasePath());
    game = new Game();
    game->init("King Donkey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);
    game->run();
    

    // Cleanup
    game->clean();

    return 0;
}
