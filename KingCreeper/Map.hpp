//
//  Map.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//
#pragma once
#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <SDL.h>

class Map
{
public:
    Map();
    ~Map();
    
    void initMap(int chosenMapP, int tNum, int lNum);
    void renderMap(SDL_Renderer* renderer, SDL_Texture* stoneTexture, SDL_Texture* ladderTexture, SDL_Texture* diamondTexture);
    SDL_Rect* getTiles() { return tiles; }
    int getTilesNum() { return tilesNum; }
    SDL_Rect* getLadders() { return ladders; }
    int getLaddersNum() { return ladderNum; }
    SDL_Rect& getDiamond1Rect() { return diamond1; }
    SDL_Rect& getDiamond2Rect() { return diamond2; }
    void removeDiamond1() { diamond1 = {0,0,0,0}; }
    void removeDiamond2() { diamond2 = {0,0,0,0}; }
    
private:
    const int tileSize = 16;
    int tilesNum = 5;
    int ladderNum = 4;
    SDL_Rect* tiles;
    SDL_Rect* ladders;
    int chosenMap = 0;
    SDL_Rect diamond1;
    SDL_Rect diamond2;
};

#endif /* Map_hpp */
