//
//  Map.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//

#include "Map.hpp"

Map::Map()
{
}
Map::~Map() {}

void Map::initMap(int chosenMapP, int tNum, int lNum)
{
    chosenMap = chosenMapP;
    tilesNum = tNum;
    ladderNum = lNum;
    tiles = new SDL_Rect[tilesNum];
    ladders = new SDL_Rect[ladderNum];
    switch (chosenMap) {
        case 0:
            tiles[0] = {0,640-tileSize,800,tileSize};
            tiles[1] = {tileSize*4, 640-7*tileSize, 800-8*tileSize, tileSize};
            tiles[2] = {tileSize*8, 640-13*tileSize, 800-11*tileSize, tileSize};
            tiles[3] = {tileSize*4, 640-19*tileSize, 800-12*tileSize, tileSize};
            tiles[4] = {tileSize*8, 640-25*tileSize, 800-10*tileSize, tileSize};
            tiles[5] = {0, 640-31*tileSize, 800-10*tileSize, tileSize};
            tiles[6] = {tileSize*4, 640-37*tileSize, 12*tileSize, tileSize};
            
            ladders[0] = {800-tileSize*7, 640-7*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[1] = {tileSize*10, 640-13*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[2] = {800-tileSize*11, 640-19*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[3] = {tileSize*10, 640-25*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[4] = {800-tileSize*14, 640-31*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[5] = {tileSize*14, 640-37*tileSize-5, tileSize*2, tileSize*6+5};
            
            diamond1 = {14*tileSize, 640-9*tileSize, 2*tileSize, 2*tileSize};
            diamond2 = {20*tileSize, 640-27*tileSize, 2*tileSize, 2*tileSize};
            break;
        case 1:
            tiles[0] = {0,640-tileSize,800,tileSize};
            tiles[1] = {tileSize*8, 640-7*tileSize, 800-8*tileSize, tileSize};
            tiles[2] = {tileSize*4, 640-13*tileSize, 800-11*tileSize, tileSize};
            tiles[3] = {tileSize*8, 640-19*tileSize, 800-12*tileSize, tileSize};
            tiles[4] = {tileSize*4, 640-25*tileSize, 800-10*tileSize, tileSize};
            tiles[5] = {10*tileSize, 640-31*tileSize, 800-10*tileSize, tileSize};
            tiles[6] = {800-tileSize*14, 640-37*tileSize, 12*tileSize, tileSize};
            
            ladders[0] = {tileSize*9, 640-7*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[1] = {800-tileSize*10, 640-13*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[2] = {tileSize*10, 640-19*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[3] = {800-tileSize*10, 640-25*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[4] = {tileSize*13, 640-31*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[5] = {800-tileSize*13, 640-37*tileSize-5, tileSize*2, tileSize*6+5};
            
            diamond1 = {14*tileSize, 640-15*tileSize, 2*tileSize, 2*tileSize};
            diamond2 = {20*tileSize, 640-27*tileSize, 2*tileSize, 2*tileSize};
            break;
        case 2:
            tiles[0] = {0,640-tileSize,800,tileSize};
            tiles[1] = {tileSize*2, 640-7*tileSize, 800-14*tileSize, tileSize};
            tiles[2] = {tileSize*5, 640-13*tileSize, 800-8*tileSize, tileSize};
            tiles[3] = {tileSize*10, 640-19*tileSize, 800-18*tileSize, tileSize};
            tiles[4] = {tileSize*12, 640-25*tileSize, 800-17*tileSize, tileSize};
            tiles[5] = {tileSize, 640-31*tileSize, 800-12*tileSize, tileSize};
            tiles[6] = {tileSize*6, 640-37*tileSize, 12*tileSize, tileSize};
            
            ladders[0] = {800-tileSize*15, 640-7*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[1] = {tileSize*7, 640-13*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[2] = {800-tileSize*11, 640-19*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[3] = {tileSize*14, 640-25*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[4] = {800-tileSize*14, 640-31*tileSize-5, tileSize*2, tileSize*6+5};
            ladders[5] = {tileSize*15, 640-37*tileSize-5, tileSize*2, tileSize*6+5};
            
            diamond1 = {14*tileSize, 640-9*tileSize, 2*tileSize, 2*tileSize};
            diamond2 = {20*tileSize, 640-27*tileSize, 2*tileSize, 2*tileSize};
            break;
            
        default:
            break;
    }
}

void Map::renderMap(SDL_Renderer* renderer, SDL_Texture* stoneTexture, SDL_Texture* ladderTexture, SDL_Texture* diamondTexture)
{
    // render stone
    for(int i = 0; i < tilesNum; i++)
    {
        SDL_RenderCopy(renderer, stoneTexture, nullptr, &tiles[i]);
    }
    
    // render ladders
    for(int i = 0; i < ladderNum; i++)
    {
        SDL_RenderCopy(renderer, ladderTexture, nullptr, &ladders[i]);
    }
    
    SDL_RenderCopy(renderer, diamondTexture, nullptr, &diamond1);
    SDL_RenderCopy(renderer, diamondTexture, nullptr, &diamond2);
}
