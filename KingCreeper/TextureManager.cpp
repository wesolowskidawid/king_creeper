//
//  TextureManager.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//

#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
    SDL_Surface* surface = SDL_LoadBMP(fileName);
    if(!surface)
    {
        printf("Error: Couldn't load texture at: %s. (%s)\n", fileName, SDL_GetError());
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture)
    {
        printf("Error: Couldn't create texture. (%s)\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect srcRect, SDL_Rect dstRect)
{
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
