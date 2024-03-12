//
//  Game.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//

#include "Game.hpp"
#include "MainMenu.hpp"
#include "SaveScore.hpp"
#include "Highscores.hpp"

Enemy* enemy;
Player* player;

SDL_Texture* playerTexture;
SDL_Texture* player2Texture;
SDL_Texture* playerClimbingTexture;
SDL_Texture* playerClimbing2Texture;
SDL_Texture* playerJumpTexture;
SDL_Texture* heartTexture;
SDL_Texture* enemyTexture;
SDL_Texture* enemy2Texture;
SDL_Texture* backgroundTexture;
SDL_Texture* background2Texture;
SDL_Texture* background3Texture;
SDL_Texture* stoneTexture;
SDL_Texture* netherrackTexture;
SDL_Texture* endstoneTexture;
SDL_Texture* ladderTexture;
SDL_Texture* tntTexture;
SDL_Texture* tnt2Texture;
SDL_Texture* tnt3Texture;
SDL_Texture* tnt4Texture;
SDL_Texture* explosionTexture;
SDL_Texture* villagerTexture;
SDL_Texture* diamondTexture;

Game::Game() 
{
    window = nullptr;
    renderer = nullptr;
    isRunning = false;
}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error: Unable to initialize SDL. %s\n", SDL_GetError());
        return;
    }
    printf("SDL initialized successfully!\n");
    
    // Create a window
    window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
    if (window == nullptr) {
        printf("Error: Unable to create SDL window. %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }
    printf("SDL window created successfully!\n");
    
    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        printf("Error: Unable to create SDL renderer. %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    printf("SDL renderer created successfully!\n");
    
    isRunning = true;
    mainMenu = new MainMenu(renderer, this);
    saveScore = new SaveScore(renderer, this);
    highScores = new Highscores(renderer, this, saveScore);
    currentState = MAIN_MENU;
    
    SDL_ShowCursor(SDL_DISABLE);
    
    
    // init textures
    fontTexture = TextureManager::LoadTexture("assets/cs8x8.bmp", renderer);
    SDL_SetTextureColorMod(fontTexture, 0, 0, 0);
    playerTexture = TextureManager::LoadTexture("assets/player.bmp", renderer);
    player2Texture = TextureManager::LoadTexture("assets/player2.bmp", renderer);
    playerClimbingTexture = TextureManager::LoadTexture("assets/playerclimbing.bmp", renderer);
    playerClimbing2Texture = TextureManager::LoadTexture("assets/playerclimbing2.bmp", renderer);
    playerJumpTexture = TextureManager::LoadTexture("assets/playerjump.bmp", renderer);
    heartTexture = TextureManager::LoadTexture("assets/heart.bmp", renderer);
    enemyTexture = TextureManager::LoadTexture("assets/enemy.bmp", renderer);
    enemy2Texture = TextureManager::LoadTexture("assets/enemy2.bmp", renderer);
    backgroundTexture = TextureManager::LoadTexture("assets/bgmc.bmp", renderer);
    background2Texture = TextureManager::LoadTexture("assets/bgmc2.bmp", renderer);
    background3Texture = TextureManager::LoadTexture("assets/bgmc3.bmp", renderer);
    stoneTexture = TextureManager::LoadTexture("assets/stone.bmp", renderer);
    netherrackTexture = TextureManager::LoadTexture("assets/netherrack.bmp", renderer);
    endstoneTexture = TextureManager::LoadTexture("assets/endstone.bmp", renderer);
    ladderTexture = TextureManager::LoadTexture("assets/ladder.bmp", renderer);
    tntTexture = TextureManager::LoadTexture("assets/tnt1.bmp", renderer);
    tnt2Texture = TextureManager::LoadTexture("assets/tnt2.bmp", renderer);
    tnt3Texture = TextureManager::LoadTexture("assets/tnt3.bmp", renderer);
    tnt4Texture = TextureManager::LoadTexture("assets/tnt4.bmp", renderer);
    explosionTexture = TextureManager::LoadTexture("assets/explosion.bmp", renderer);
    villagerTexture = TextureManager::LoadTexture("assets/villager.bmp", renderer);
    diamondTexture = TextureManager::LoadTexture("assets/diamond.bmp", renderer);
    
    map = new Map();
    map->initMap(currentMap, 7, 6);
    
    enemy = new Enemy(map, enemyInitXL, enemyInitY, true);
    enemy->init(enemyTexture, enemy2Texture, tntTexture, tnt2Texture, tnt3Texture, tnt4Texture);
    player = new Player(map, playerInitXL, playerInitY,1,0.1,0.9,10.0);
    player->init(playerTexture, player2Texture, playerClimbingTexture, playerClimbing2Texture, playerJumpTexture, villagerTexture);
    player->setVillagerRect({96, 16, 32, 32});
    
    
    // tests
//    map->printMap();
}

void Game::run()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    int frame = 0;
    
    // Main loop
    while (running()) {
        frameStart = SDL_GetTicks();
        
        handleEvents();
        update();
        render();
        
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        frame++;
        if(frame == 60)
        {
            timeRunning++;
            frame = 0;
        }
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        switch (currentState) {
            case MAIN_MENU:
                mainMenu->handleInput(event);
                break;
            case GAME_PLAY:
                player->handlePlayerMovement(event);
                break;
            case SAVE_SCORE:
                saveScore->handleInput(event);
                break;
            case HIGH_SCORES:
                highScores->handleInput(event);
                break;
            case GAME_QUIT:
                isRunning = false;
                
            default:
                break;
        }
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(waitForContinue)
                {
                    if(event.key.keysym.sym == SDLK_SPACE)
                    {
                        waitForContinue = false;
                    }
                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        waitForContinue = false;
                        player->setHealth(3);
                        currentMap = 0;
                        saveScore->setPoints(points);
                        changeState(SAVE_SCORE);
                    }
                    break;
                }
                if(currentState == GAME_PLAY)
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            isRunning = false;
                            break;
                        case SDLK_n:
                            restartGame();
                            player->setHealth(3);
                            break;
                        case SDLK_1:
                            map->initMap(0, 7, 6);
                            currentMap = 0;
                            restartGame();
                            player->setHealth(3);
                            player->setVillagerRect({96, 16, 32, 32});
                            break;
                        case SDLK_2:
                            map->initMap(1, 7, 6);
                            currentMap = 1;
                            restartGame();
                            player->setHealth(3);
                            player->setVillagerRect({800-96, 16, 32, 32});
                            break;
                        case SDLK_3:
                            map->initMap(2, 7, 6);
                            currentMap = 2;
                            restartGame();
                            player->setHealth(3);
                            player->setVillagerRect({128, 16, 32, 32});
                            break;
                            
                        default:
                            break;
                    }
                }
                break;
                
            default:
                break;
        }
    }
}

void Game::update()
{
    switch (currentState) {
        case GAME_PLAY:
            if(!waitForContinue)
            {
                player->updatePlayer(enemy);
                enemy->update();
                if(player->getJumpedOverBarrel())
                {
                    points += 100;
                    player->setJumpedOverBarrel(false);
                    tempPoints = 100;
                    displayTempPoints = true;
                    tX = player->getX();
                    tY = player->getY();
                    lastTDisplay = SDL_GetTicks();
                }
                if(player->getGotDiamond())
                {
                    points += 300;
                    player->setGotDiamond(false);
                    tempPoints = 300;
                    displayTempPoints = true;
                    tX = player->getX();
                    tY = player->getY();
                    lastTDisplay = SDL_GetTicks();
                }
                if(player->getHealth() == 0)
                {
                    currentMap = 0;
                    player->setHealth(3);
                    player->setVillagerRect({128, 16, 32, 32});
                    restartGame();
                    endOfGame = true;
                    saveScore->setPoints(points);
                    currentState = SAVE_SCORE;
                }
                if(player->getNextLevel())
                {
                    player->setNextLevel(false);
                    points += 5000;
                    switch (currentMap) {
                        case 0:
                            map->initMap(1, 7, 6);
                            currentMap = 1;
                            restartGame();
                            player->setHealth(3);
                            player->setVillagerRect({800-96, 16, 32, 32});
                            break;
                        case 1:
                            map->initMap(2, 7, 6);
                            currentMap = 2;
                            restartGame();
                            player->setHealth(3);
                            player->setVillagerRect({128, 16, 32, 32});
                            break;
                        case 2:
                            currentMap = 0;
                            player->setHealth(3);
                            player->setVillagerRect({128, 16, 32, 32});
                            restartGame();
                            endOfGame = true;
                            saveScore->setPoints(points);
                            currentState = SAVE_SCORE;
                            break;
                            
                        default:
                            break;
                    }
                }
                if(SDL_GetTicks() - lastTDisplay > 1000)
                {
                    displayTempPoints = false;
                }
            }
            break;
            
        default:
            break;
    }
}

void Game::render()
{
    // Rendering
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // render background
    switch (currentMap) {
        case 0:
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            break;
        case 1:
            SDL_RenderCopy(renderer, background2Texture, NULL, NULL);
            break;
        case 2:
            SDL_RenderCopy(renderer, background3Texture, NULL, NULL);
            break;
            
        default:
            break;
    }
    
    switch (currentState) {
        case MAIN_MENU:
            mainMenu->render();
            break;
        case SAVE_SCORE:
            saveScore->render();
            break;
        case HIGH_SCORES:
            highScores->render();
            break;
        case GAME_PLAY:
            // render map
            switch (currentMap) {
                case 0:
                    map->renderMap(renderer, stoneTexture, ladderTexture, diamondTexture);
                    break;
                case 1:
                    map->renderMap(renderer, netherrackTexture, ladderTexture, diamondTexture);
                    break;
                case 2:
                    map->renderMap(renderer, endstoneTexture, ladderTexture, diamondTexture);
                    break;
                default:
                    break;
            }
            
            if(waitForContinue)
            {
                const char* lostHeartTitle = "YOU LOST A HEART";
                const char* continueTitle = "PRESS SPACE TO CONTINUE";
                const char* backTitle = "PRESS ENTER TO GO BACK TO MENU";
                if(currentMap == 1 || currentMap == 2) SDL_SetTextureColorMod(fontTexture, 255, 255, 255);
                renderText(fontTexture, lostHeartTitle, 800/2-(static_cast<int>(strlen(lostHeartTitle))/2*16), 640/2-40, 8, 8);
                renderText(fontTexture, continueTitle, 800/2-(static_cast<int>(strlen(continueTitle))/2*16), 640/2, 8, 8);
                renderText(fontTexture, backTitle, 800/2-(static_cast<int>(strlen(backTitle))/2*16), 640/2+40, 8, 8);
                SDL_SetTextureColorMod(fontTexture, 0, 0, 0);
            }
            
            // render enemy
            enemy->render(renderer);
            
            // render player
            player->renderPlayer(renderer);
            
            // render time, points and info
            if(currentMap == 1 || currentMap == 2) SDL_SetTextureColorMod(fontTexture, 255, 255, 255);
            renderText(fontTexture, intToCharPointer(timeRunning), 10, 16, 8, 8);
            renderText(fontTexture, intToCharPointer(points), 10, 48, 8, 8);
            renderText(fontTexture, "DODATKOWE: A,B,C,D,E,F,G", 60, 10, 8, 8);
            if(displayTempPoints)
                renderText(fontTexture, intToCharPointer(tempPoints), tX, tY, 8, 8);
            SDL_SetTextureColorMod(fontTexture, 0, 0, 0);
            
            
            // render health
            for(int i = 0; i < player->getHealth(); i++)
            {
                SDL_Rect heartRect = {10 + i*20, 32, 16, 16};
                SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect);
            }
            if(player->getHealthLost())
            {
                SDL_RenderCopy(renderer, explosionTexture, NULL, player->getRect());
                waitForContinue = true;
            }
            
            break;
            
        default:
            break;
    }

    SDL_RenderPresent(renderer);
    if(player->getHealthLost())
    {
        player->setHealthLost(false);
        player->stop();
        restartGame();
    }
}

void Game::clean()
{
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(player2Texture);
    SDL_DestroyTexture(playerClimbingTexture);
    SDL_DestroyTexture(playerClimbing2Texture);
    SDL_DestroyTexture(playerJumpTexture);
    SDL_DestroyTexture(heartTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(enemy2Texture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(background2Texture);
    SDL_DestroyTexture(background3Texture);
    SDL_DestroyTexture(stoneTexture);
    SDL_DestroyTexture(netherrackTexture);
    SDL_DestroyTexture(endstoneTexture);
    SDL_DestroyTexture(ladderTexture);
    SDL_DestroyTexture(tntTexture);
    SDL_DestroyTexture(tnt2Texture);
    SDL_DestroyTexture(tnt3Texture);
    SDL_DestroyTexture(tnt4Texture);
    SDL_DestroyTexture(fontTexture);
    SDL_DestroyTexture(explosionTexture);
    SDL_DestroyTexture(villagerTexture);
    SDL_DestroyTexture(diamondTexture);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::restartGame()
{
    switch (currentMap) {
        case 0:
            player->setX(playerInitXL);
            enemy->setX(enemyInitXL);
            enemy->changeLeft(true);
            break;
        case 1:
            player->setX(playerInitXR);
            enemy->setX(enemyInitXR);
            enemy->changeLeft(false);
            break;
        case 2:
            player->setX(playerInitXL);
            enemy->setX(enemyInitXL);
            enemy->changeLeft(true);
            break;
            
        default:
            break;
    }
    player->setY(playerInitY);
    enemy->restartBarrels();
}

void Game::renderText(SDL_Texture* fontTexture, const char* text, int x, int y, int charWidth, int charHeight) {
    int len = static_cast<int>(strlen(text));

    for (int i = 0; i < len; ++i) {
        int row=0, col=0;

        if (text[i] >= 'A' && text[i] <= 'O') {
            row = 5;
            col = 2 + (text[i] - 'A');
        }
        else if(text[i] > 'O' && text[i] <= 'Z')
        {
            row = 6;
            col = 1 + text[i] - 'P';
        }
        else if (text[i] >= 'a' && text[i] <= 'o') {
            row = 7;
            col = 2 + (text[i] - 'a');
        }
        else if(text[i] > 'o' && text[i] <= 'z')
        {
            row = 8;
            col = 1 + text[i] - 'p';
        }
        else if(text[i] >= '0' && text[i] <= '9')
        {
            row = 4;
            col = 1 + (text[i] - '0');
        }
        else if(text[i] == '/')
        {
            row = 3;
            col = 16;
        }

        row-=1;col-=1;
        SDL_Rect srcRect = { col * charWidth, row * charHeight, charWidth, charHeight };
        SDL_Rect destRect = { x + i * (charWidth*2), y, charWidth*2, charHeight*2 };

        SDL_RenderCopy(renderer, fontTexture, &srcRect, &destRect);
    }
}

char* Game::intToCharPointer(int number)
{
    int numDigits = 1;
    int temp = number;
    while (temp /= 10) {
        ++numDigits;
    }

    char* result = new char[numDigits + 1];

    int index = numDigits - 1;
    while (index >= 0) {
        result[index] = '0' + number % 10;
        number /= 10;
        --index;
    }

    result[numDigits] = '\0';

    return result;
}
