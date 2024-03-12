//
//  Barrel.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//
#pragma once
#ifndef Barrel_hpp
#define Barrel_hpp

#include <stdio.h>
#include <SDL.h>

#include "Map.hpp"

class Barrel
{
public:
    Barrel() {}
    Barrel(int startX, int startY, int initMovingRight) : x(startX), y(startY), startX(startX), startY(startY), movingRight(initMovingRight), falling(false), bRect({0,0,32,32}) {}
    void update(Map* map);
    void render(SDL_Renderer* renderer, SDL_Texture* texture1, SDL_Texture *texture2, SDL_Texture *texture3, SDL_Texture* texture4);
    void changeDirection() { movingRight = !movingRight; }
    void changeFalling() { falling = !falling; }
    
    bool isOffScreen() { return offScreen; }
    
    int getX() { return x; }
    int getY() { return y; }
    SDL_Rect getRect() { return bRect; }
private:
    int x, y;
    int startX, startY;
    int barrelSpeed = 4;
    bool movingRight;
    bool falling;
    bool changedDir = false;
    
    bool offScreen = false;
    
    int textureTick = 0;
    
    SDL_Rect bRect;
};

#endif /* Barrel_hpp */
