//
//  Game.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//
#pragma once
#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL.h>
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "MainMenu.hpp"
#include "SaveScore.hpp"
#include "Highscores.hpp"

enum GameState
{
    MAIN_MENU,
    GAME_PLAY,
    SAVE_SCORE,
    HIGH_SCORES,
    GAME_QUIT
};

class Game 
{
public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height);
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }
    void stopGame() { isRunning = false; }
    void restartGame();
    SDL_Renderer* getRenderer() { return renderer; }
    
    SDL_Texture* getFontTexture() { return fontTexture; }
    void renderText(SDL_Texture* fontTexture, const char* text, int x, int y, int charWidth, int charHeight);
    char* intToCharPointer(int number);
    
    void changeState(GameState newState) { currentState = newState; }
private:
    bool isRunning;
    bool waitForContinue = false;
    bool endOfGame = false;
    int timeRunning = 0;
    int points = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    SDL_Texture* fontTexture;
    
    int playerInitXL = 64, playerInitY = 640-64, playerInitXR = 800-64;
    int enemyInitXL = 32, enemyInitY = 80, enemyInitXR = 800-96;
    
    GameState currentState;
    MainMenu* mainMenu;
    SaveScore* saveScore;
    Highscores* highScores;
    int currentMap;
    Map* map;
    
    bool displayTempPoints = false;
    int tempPoints = 0;
    int tX=0, tY=0;
    Uint32 lastTDisplay;
};

#endif /* Game_hpp */
