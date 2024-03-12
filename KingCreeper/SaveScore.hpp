//
//  SaveScore.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 08/01/2024.
//
#pragma once
#ifndef SaveScore_hpp
#define SaveScore_hpp

#include <stdio.h>
#include <SDL.h>

class Game;

struct Score
{
    char username[26];
    int points;
};

class SaveScore
{
public:
    SaveScore(SDL_Renderer* rendererP, Game* gameP) : renderer(rendererP), game(gameP) {}
    void setPoints(int p) { points = p; }
    void handleInput(SDL_Event &event);
    void render();
    void saveToFile();
    Score* getScores(int &numScores);
private:
    SDL_Renderer* renderer;
    Game* game;
    int points = 0;
    const int maxNameLength = 25;
    char name[26];
    int nameLength = 0;
};

#endif /* SaveScore_hpp */
