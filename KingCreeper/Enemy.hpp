//
//  Enemy.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 06/01/2024.
//
#pragma once
#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <SDL.h>
#include <thread>
#include <chrono>

#include "Barrel.hpp"

class Enemy
{
public:
    Enemy() {};
    Enemy(Map* mapP, int startX, int startY, bool leftP) : map(mapP), x(startX), y(startY), left(leftP) {};
    void init(SDL_Texture* initEnemyTex, SDL_Texture*  initEnemy2Tex, SDL_Texture* initBarrelTex1, SDL_Texture* initBarrelTex2, SDL_Texture* initBarrelTex3, SDL_Texture* initBarrelTex4);
    void update();
    void render(SDL_Renderer* renderer);
    
    void setX(int initX) { x = initX; rect.x = initX; }
    void setY(int initY) { y = initY; rect.y = initY; }
    void changeLeft(bool leftP) { left = leftP; }
    
    void dropBarrel();
    
    int getBarrelAmount() { return barrelCount; }
    Barrel** getBarrels() { return barrels; }
    void restartBarrels();
private:
    int x, y;
    SDL_Texture* enemyTexture;
    SDL_Texture* enemy2Texture;
    SDL_Texture* barrelTexture1;
    SDL_Texture* barrelTexture2;
    SDL_Texture* barrelTexture3;
    SDL_Texture* barrelTexture4;
    SDL_Rect rect;
    bool left = false;
    
    const int maxBarrelNum = 2500;
    Barrel* barrels[2500];
    int barrelCount = 0;
    const Uint32 dropInterval = 2000;
    Uint32 currentTime;
    Uint32 lastDropTime = SDL_GetTicks();
    
    Map* map;
};

#endif /* Enemy_hpp */
