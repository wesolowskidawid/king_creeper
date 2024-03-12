//
//  Enemy.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 06/01/2024.
//

#include "Enemy.hpp"

void Enemy::init(SDL_Texture* initEnemyTex, SDL_Texture*  initEnemy2Tex, SDL_Texture* initBarrelTex1, SDL_Texture* initBarrelTex2, SDL_Texture* initBarrelTex3, SDL_Texture* initBarrelTex4)
{
    enemyTexture = initEnemyTex;
    enemy2Texture = initEnemy2Tex;
    barrelTexture1 = initBarrelTex1;
    barrelTexture2 = initBarrelTex2;
    barrelTexture3 = initBarrelTex3;
    barrelTexture4 = initBarrelTex4;
    rect = {x, y, 64, 64};
}

void Enemy::update()
{
    currentTime = SDL_GetTicks();
    
    if(currentTime - lastDropTime >= dropInterval)
    {
        dropBarrel();
        lastDropTime = currentTime;
    }
    
    // move barrels
    for(int i = 0; i < barrelCount; i++)
    {
        if(!barrels[i]->isOffScreen())
            barrels[i]->update(map);
    }
}

void Enemy::render(SDL_Renderer* renderer)
{
    if(currentTime-lastDropTime-(dropInterval/2) < dropInterval/2)
    {
        SDL_RenderCopy(renderer, enemy2Texture, nullptr, &rect);
    }
    else
    {
        SDL_RenderCopy(renderer, enemyTexture, nullptr, &rect);
    }
    for(int i = 0; i < barrelCount; i++)
    {
        if(!barrels[i]->isOffScreen())
            barrels[i]->render(renderer, barrelTexture1, barrelTexture2, barrelTexture3, barrelTexture4);
    }
}

void Enemy::dropBarrel()
{
    if(barrelCount < maxBarrelNum)
    {
        barrels[barrelCount] = new Barrel(x, y+32, left);
        barrelCount++;
    }
}

void Enemy::restartBarrels()
{
    for(int i = 0; i < barrelCount; i++)
    {
        if(barrels[i] != nullptr)
        {
            delete barrels[i];
            barrels[i] = nullptr;
        }
    }
    barrelCount = 0;
    lastDropTime = SDL_GetTicks();
}
