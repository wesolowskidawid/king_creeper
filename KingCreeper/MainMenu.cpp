//
//  MainMenu.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 07/01/2024.
//

#include "MainMenu.hpp"
#include "Game.hpp"

void MainMenu::handleInput(SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                if(chosenOption == 0)
                    game->changeState(GameState::GAME_PLAY);
                else if(chosenOption == 1)
                    game->changeState(GameState::HIGH_SCORES);
                else if(chosenOption == 2)
                    game->stopGame();
                break;
            case SDLK_UP:
                if(chosenOption > 0)
                    chosenOption--;
                break;
            case SDLK_DOWN:
                if(chosenOption < 2)
                    chosenOption++;
                break;
            default:
                break;
        }
    }
}

void MainMenu::render() 
{
    SDL_Texture* fontTexture = game->getFontTexture();
    const char* title = "KING CREEPER";
    game->renderText(fontTexture, title, 800/2-strlen(title)/2*16, 100, 8, 8);
    
    const char* option1 = "PLAY";
    const char* option2 = "HIGHSCORES";
    const char* option3 = "QUIT";
    
    switch (chosenOption) {
        case 0:
            SDL_SetTextureColorMod(fontTexture, 255, 0, 0);
            game->renderText(fontTexture, option1, 800/2-static_cast<int>(strlen(option1))/2*16, 300, 8, 8);
            SDL_SetTextureColorMod(fontTexture, 0, 0, 0);
            game->renderText(fontTexture, option2, 800/2-static_cast<int>(strlen(option2))/2*16, 350, 8, 8);
            game->renderText(fontTexture, option3, 800/2-static_cast<int>(strlen(option3))/2*16, 400, 8, 8);
            break;
        case 1:
            game->renderText(fontTexture, option1, 800/2-static_cast<int>(strlen(option1))/2*16, 300, 8, 8);
            SDL_SetTextureColorMod(fontTexture, 255, 0, 0);
            game->renderText(fontTexture, option2, 800/2-static_cast<int>(strlen(option2))/2*16, 350, 8, 8);
            SDL_SetTextureColorMod(fontTexture, 0, 0, 0);
            game->renderText(fontTexture, option3, 800/2-static_cast<int>(strlen(option3))/2*16, 400, 8, 8);
            break;
        case 2:
            game->renderText(fontTexture, option1, 800/2-static_cast<int>(strlen(option1))/2*16, 300, 8, 8);
            game->renderText(fontTexture, option2, 800/2-static_cast<int>(strlen(option2))/2*16, 350, 8, 8);
            SDL_SetTextureColorMod(fontTexture, 255, 0, 0);
            game->renderText(fontTexture, option3, 800/2-static_cast<int>(strlen(option3))/2*16, 400, 8, 8);
            SDL_SetTextureColorMod(fontTexture, 0, 0, 0);
            break;
        default:
            break;
    }
}
