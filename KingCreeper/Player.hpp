//
//  Player.hpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//
#pragma once
#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SDL.h>

#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Player
{
public:
    Player(Map* mapP, double initX, double initY, double initSpeed, double initAcceleration, double initFriction, double initJumpVelocity);
    ~Player();
    
    void init(SDL_Texture* playerTexture, SDL_Texture* player2Texture, SDL_Texture* playerClimbingTexture, SDL_Texture* playerClimbing2Texture,
              SDL_Texture* playerJumpTexture, SDL_Texture* villagerTexture);
    void renderPlayer(SDL_Renderer* renderer);
    void updatePlayer(Enemy* enemy);
    void handlePlayerMovement(SDL_Event& e);
    
    void startMovingRight();
    void stopMovingRight();
    void startMovingLeft();
    void stopMovingLeft();
    void startMovingUp();
    void stopMovinUp();
    void startMovingDown();
    void stopMovingDown();
    void jump();
    void stop();
    
    bool isColliding(SDL_Rect& r);
    SDL_Rect* getRect() { return &rect; }
    
    double getX() { return static_cast<int>(x); }
    double getY() { return static_cast<int>(y); }
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    
    int getHealth() { return health; }
    void setHealth(int newHealth) { health = newHealth; }
    bool getHealthLost() { return healthLost; }
    void setHealthLost(bool newHL) { healthLost = newHL; }
    void setVillagerRect(SDL_Rect newRect) { villagerRect = newRect; }
    bool getNextLevel() { return nextLevel; }
    void setNextLevel(bool newNextLevel) { nextLevel = newNextLevel; }
    bool getJumpedOverBarrel() { return jumpedOverBarrel; }
    void setJumpedOverBarrel(bool newJOB) { jumpedOverBarrel = newJOB; }
    bool getGotDiamond() { return gotDiamond; }
    void setGotDiamond(bool newGotDiamond) { gotDiamond = newGotDiamond; }
    
    int min(int a, int b) {
        return (a < b) ? a : b;
    }
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
private:
    double x,y;
    double speed;
    double vx, vy; // velocity
    double acceleration;
    double accelerationStateX = 0.0;
    double accelerationStateY = 0.0;
    double friction; // gradually slow down player when no keys are pressed
    const double gravity = 0.5;
    double gravityState;
    
    int health = 3;
    bool healthLost = false;
    
    bool canClimb;
    SDL_Rect usedLadder;
    bool goingDown;
    
    bool onGround;
    bool jumped = false;
    double jumpVelocity;
    
    bool isMovingRight;
    bool isMovingLeft;
    bool isMovingUp;
    bool isMovingDown;
    
    Map* map;
    
    int textureTick = 0;
    SDL_Texture* playerTex;
    SDL_Texture* playerTex2;
    SDL_Texture* playerClimbingTex;
    SDL_Texture* playerClimbingTex2;
    SDL_Texture* playerJumpTex;
    SDL_Texture* villagerTex;
    
    SDL_Rect rect;
    SDL_Rect villagerRect;
    
    bool jumpedOverBarrel = false;
    bool gotDiamond = false;
    bool nextLevel = false;
};

#endif /* Player_hpp */
