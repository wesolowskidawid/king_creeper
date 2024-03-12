//
//  Barrel.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//

#include "Barrel.hpp"

void Barrel::update(Map* map)
{
    if(movingRight && !falling)
    {
        x += barrelSpeed;
    }
    else if(!movingRight && !falling)
    {
        x -= barrelSpeed;
    }
    if(falling)
    {
        y += barrelSpeed;
    }
    bRect.x = x;
    bRect.y = y;
    
    // check if nothing underneath
    // if nothing underneath, start falling
    for(int i = 0; i < map->getTilesNum(); i++)
    {
        SDL_Rect tempRect = {x, y+4, 32, 32};
        if(!SDL_HasIntersection(&tempRect, &map->getTiles()[i]))
        {
            falling = true;
        }
        else
        {
            falling = false;
            break;
        }
    }
    
    if(falling) changedDir = true;
    if(changedDir && !falling)
    {
        changedDir = false;
        changeDirection();
    }
    
    if(x < 0 || x > 800 || y < 0 || y > 640)
    {
        offScreen = true;
    }
}

void Barrel::render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture *texture2, SDL_Texture *texture3, SDL_Texture* texture4)
{
    if(textureTick < 5)
        SDL_RenderCopy(renderer, texture, nullptr, &bRect);
    else if(textureTick < 10)
        SDL_RenderCopy(renderer, texture2, nullptr, &bRect);
    else if(textureTick < 15)
        SDL_RenderCopy(renderer, texture3, nullptr, &bRect);
    else
        SDL_RenderCopy(renderer, texture4, nullptr, &bRect);
    
    textureTick++;
    if(textureTick > 20) textureTick = 0;
}
