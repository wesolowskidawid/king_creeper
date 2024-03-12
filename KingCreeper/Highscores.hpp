//
//  Highscores.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 08/01/2024.
//
#pragma once
#ifndef Highscores_hpp
#define Highscores_hpp

#include <stdio.h>
#include <SDL.h>

#include "SaveScore.hpp"

class Game;

class Highscores
{
public:
    Highscores(SDL_Renderer* renderer, Game* game, SaveScore* saveScore) : renderer(renderer), game(game), saveScore(saveScore) {}
    void render();
    void handleInput(SDL_Event& event);
    
    void swapScores(Score& a, Score& b);
    void bubbleSortScores(Score* scores, int numScores);
private:
    SDL_Renderer* renderer;
    Game* game;
    SaveScore* saveScore;
    int numScores;
    
    int page = 0;
    int pageAmount = 0;
    const int elementsPerPage = 20;
};

#endif /* Highscores_hpp */
