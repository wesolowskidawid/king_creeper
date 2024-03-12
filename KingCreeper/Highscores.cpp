//
//  Highscores.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 08/01/2024.
//

#include "Highscores.hpp"
#include "Game.hpp"

void Highscores::render()
{
    Score* scores = saveScore->getScores(numScores);
    if(scores != nullptr)
    {
        bubbleSortScores(scores, numScores);
        SDL_Texture* fontTexture = game->getFontTexture();
        const char* title = "HIGHSCORES";
        game->renderText(fontTexture, title, 800/2-static_cast<int>(strlen(title)/2*16), 60, 8, 8);
        int j = 0;
        for (int i = page*elementsPerPage-1; i < (page+1)*elementsPerPage; ++i) {
            if(i < 0 || i >= numScores) continue;
            scores[i].username[24] = '\0';
            game->renderText(fontTexture, scores[i].username, 100, 100+j*20, 8, 8);
            game->renderText(fontTexture, game->intToCharPointer(scores[i].points), 100 + static_cast<int>(strlen(scores[i].username))*16 + 50, 100+j*20, 8, 8);
            j++;
        }
        pageAmount = numScores / elementsPerPage + 1;
        delete[] scores;
    }
    else
    {
		const char* title = "NO SCORES";
		game->renderText(game->getFontTexture(), title, 800/2-static_cast<int>(strlen(title)/2*16), 60, 8, 8);
        const char* title2 = "PRESS ENTER TO GO BACK TO MAIN MENU";
        game->renderText(game->getFontTexture(), title2, 800/2-static_cast<int>(strlen(title2)/2*16), 100, 8, 8);
	}
}

void Highscores::handleInput(SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                game->changeState(GameState::MAIN_MENU);
                break;
            case SDLK_RIGHT:
                if(page+1 < pageAmount)
                {
                    page++;
                }
                break;
            case SDLK_LEFT:
                if(page > 0)
                {
                    page--;
                }
                
            default:
                break;
        }
    }
}

void Highscores::swapScores(Score& a, Score& b) {
    Score temp = a;
    a = b;
    b = temp;
}

void Highscores::bubbleSortScores(Score* scores, int numScores) {
    for (int i = 0; i < numScores - 1; ++i) {
        for (int j = 0; j < numScores - i - 1; ++j) {
            if (scores[j].points < scores[j + 1].points) {
                swapScores(scores[j], scores[j + 1]);
            }
        }
    }
}
