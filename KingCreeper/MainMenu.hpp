//
//  MainMenu.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 07/01/2024.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <stdio.h>
#include <SDL.h>

class Game;

class MainMenu
{
public:
    MainMenu(SDL_Renderer* renderer, Game* game) : renderer(renderer), game(game) {}
    
    void handleInput(SDL_Event &event);
    void render();
    
private:
    SDL_Renderer* renderer;
    Game* game;
    int chosenOption = 0;
};

#endif /* MainMenu_hpp */
