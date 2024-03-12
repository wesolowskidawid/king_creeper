//
//  SaveScore.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 08/01/2024.
//

#include "SaveScore.hpp"
#include "Game.hpp"

void SaveScore::render()
{
    SDL_Texture* fontTexture = game->getFontTexture();
    const char* title = "SAVE SCORE";
    const char* title2 = "PRESS / TO GO BACK TO MAIN MENU";
    game->renderText(fontTexture, title, 800/2-static_cast<int>(strlen(title)/2*16), 100, 8, 8);
    game->renderText(fontTexture, title2, 800/2-static_cast<int>(strlen(title2)/2*16), 124, 8, 8);
    
    const char* score1 = "YOUR SCORE";
    const char* score2 = game->intToCharPointer(points);
    game->renderText(fontTexture, score1, 800/2-static_cast<int>(strlen(score1)/2*16), 160, 8, 8);
    game->renderText(fontTexture, score2, 800/2-static_cast<int>(strlen(score2)/2*16), 184, 8, 8);
    
    const char* name1 = "ENTER YOUR NAME";
    game->renderText(fontTexture, name1, 800/2-static_cast<int>(strlen(name1)/2*16), 220, 8, 8);
    game->renderText(fontTexture, name, 800/2-static_cast<int>(nameLength/2*16), 244, 8, 8);
    
    const char* name2 = "PRESS ENTER TO SAVE";
    game->renderText(fontTexture, name2, 800/2-static_cast<int>(strlen(name2)/2*16), 280, 8, 8);
}

void SaveScore::handleInput(SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_SLASH)
        {
            nameLength = 0;
            for (int i = 0; i < sizeof(name); ++i) {
                name[i] = '\0';
            }
            game->changeState(GameState::MAIN_MENU);
        }
        if(event.key.keysym.sym == SDLK_RETURN)
        {
            if(nameLength >= 0 && nameLength < 25)
                name[nameLength] = '\0';
            saveToFile();
            for (int i = 0; i < 25; ++i) {
                name[i] = '\0';
            }
            nameLength = 0;
            game->changeState(GameState::MAIN_MENU);
        }
        else if(event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0)
        {
            nameLength--;
            name[nameLength] = '\0';
        }
        else if(event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z && nameLength < maxNameLength)
        {
            name[nameLength] = static_cast<char>('a' + event.key.keysym.sym - SDLK_a);
            nameLength++;
            name[nameLength] = '\0';
        }
    }
}

void SaveScore::saveToFile()
{
    FILE* file;
    fopen_s(&file, "scores.txt", "r+");
    if(file != nullptr)
    {
        int numScores = 0;
        fscanf_s(file, "%d", &numScores);

        fseek(file, 0, SEEK_SET);

        numScores++;

        fprintf_s(file, "%d\n", numScores);

        fseek(file, 0, SEEK_END);

        fprintf_s(file, "%s %d\n", name, points);

        fclose(file);
    }
    else
    {
        printf("ERROR: cannot open file\n");
    }
}

Score* SaveScore::getScores(int &numScores)
{
    FILE* file;
    fopen_s(&file, "scores.txt", "r");
    
    if (file != nullptr) {
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            printf("File is empty\n");
            fclose(file);
            return nullptr;
        }
        fseek(file, 0, SEEK_SET);

        fscanf_s(file, "%d", &numScores);

        if (numScores < 0) {
            printf("Invalid numScores value\n");
            fclose(file);
            return nullptr;
        }

        fgetc(file);

        Score* scores = new Score[numScores];

        char tempUsername[26];
        int tempPoints;
        char tempLine[26];
        for (int i = 0; i < numScores; ++i) {
            if (fgets(tempLine, sizeof(tempLine), file) != nullptr) {
                if (sscanf_s(tempLine, "%24[^ \t\n] %d", tempUsername, (unsigned)_countof(tempUsername), &tempPoints) == 2) {
                    strncpy_s(scores[i].username, _countof(scores[i].username), tempUsername, _TRUNCATE);
                    scores[i].username[_countof(scores[i].username) - 1] = '\0';
                    scores[i].points = tempPoints;
                }
                else {
                    printf("ERROR: Failed to parse line: %s", tempLine);
                    fclose(file);
                    delete[] scores;
                    return nullptr;
                }
            }
            else {
                printf("ERROR: Failed to read line\n");
                fclose(file);
                delete[] scores;
                return nullptr;
            }
        }

        fclose(file);
        return scores;
    }
    else
    {
        return nullptr;
    }
}
