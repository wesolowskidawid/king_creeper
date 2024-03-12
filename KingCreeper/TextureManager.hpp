//
//  TextureManager.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//
#pragma once
#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <stdio.h>
#include <SDL.h>

#include "Game.hpp"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
    static void Draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect srcRect, SDL_Rect dstRect);
private:
    SDL_Surface* surface;
    SDL_Texture* texture;
};

#endif /* TextureManager_hpp */
