//
//  Player.cpp
//  kingdonkey
//
//  Created by Dawid Wesołowski on 05/01/2024.
//

#include "Player.hpp"

Player::Player(Map* mapP, double initX, double initY, double initSpeed, double initAcceleration, double initFriction, double initJumpVelocity)
{
    x = initX;
    y = initY;
    speed = initSpeed;
    vx = 0;
    vy = 0;
    acceleration = initAcceleration;
    friction = initFriction;
    canClimb = false;
    goingDown = false;
    gravityState = gravity;
    onGround = true;
    jumpVelocity = initJumpVelocity;
    isMovingRight = false;
    isMovingLeft = false;
    
    map = mapP;
    
    rect = {static_cast<int>(x), static_cast<int>(y), 32, 32};
}
Player::~Player() {}

void Player::init(SDL_Texture* playerTexture, SDL_Texture* player2Texture, SDL_Texture* playerClimbingTexture, SDL_Texture* playerClimbing2Texture,
                  SDL_Texture* playerJumpTexture, SDL_Texture* villagerTexture)
{
    playerTex = playerTexture;
    playerTex2 = player2Texture;
    playerClimbingTex = playerClimbingTexture;
    playerClimbingTex2 = playerClimbing2Texture;
    playerJumpTex = playerJumpTexture;
    villagerTex = villagerTexture;
}

void Player::renderPlayer(SDL_Renderer *renderer)
{
    SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), 32, 32};
    if(!onGround && !canClimb)
    {
        SDL_RenderCopy(renderer, playerJumpTex, NULL, &rect);
    }
    else if(textureTick < 5)
    {
        if(!canClimb)
        {
            SDL_RenderCopy(renderer, playerTex, NULL, &rect);
        }
        else
        {
            SDL_RenderCopy(renderer, playerClimbingTex, NULL, &rect);
        }
    }
    else
    {
        if(!canClimb)
        {
            SDL_RenderCopy(renderer, playerTex2, NULL, &rect);
        }
        else
        {
            SDL_RenderCopy(renderer, playerClimbingTex2, NULL, &rect);
        }
    }
    SDL_RenderCopy(renderer, villagerTex, NULL, &villagerRect);
}

void Player::updatePlayer(Enemy* enemy)
{
    textureTick++;
    if(textureTick > 10)
    {
        textureTick = 0;
    }
    x += vx;
    y += vy;
    
    // add gravity
    vy += gravityState;
    
    vx *= friction;
    vy *= friction;
    
    vx += accelerationStateX;
    vy += accelerationStateY;
    
    // player cant go outside the screen
    if(x < 0)
    {
        x = 0;
    }
    if(x > 800 - rect.w)
    {
        x = 800 - rect.w;
    }
    
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    
    // remove gravity when player is on the ground
    if(map != nullptr)
    {
        for(int i = 0; i < map->getTilesNum(); i++)
        {
            SDL_Rect& tileRect = map->getTiles()[i];
            if(isColliding(tileRect))
            {
                if(!canClimb)
                {
    //                y = tileRect.y - rect.h;
    //                rect.y = tileRect.y - rect.h;
                    // collision from top
                    if(rect.y + rect.h > tileRect.y && rect.y < tileRect.y)
                    {
                        y = tileRect.y - rect.h;
                        rect.y = tileRect.y - rect.h;
                        vy = 0;
                    }
                    // collision from bottom
                    if(rect.y < tileRect.y + tileRect.h && rect.y > tileRect.y)
                    {
                        y = tileRect.y + tileRect.h;
                        rect.y = tileRect.y + tileRect.h;
                        vy = 0;
                        if(isMovingUp)
                        {
                            stopMovinUp();
                            accelerationStateY = 0;
                        }
                    }
                }
                else {
                    if(rect.y+rect.h > tileRect.y && !goingDown && !SDL_HasIntersection(&tileRect, &usedLadder))
                    {
                        y -= 1;
                        rect.y -= 1;
                        vy = 0;
                    }
                }
            }
        }
    }
    
    // check if can climb
    bool canclimbtemp = false;
    if(map != nullptr)
    {
        for(int i = 0; i < map->getLaddersNum(); i++)
        {
            SDL_Rect& ladderRect = map->getLadders()[i];
            if(isColliding(ladderRect))
            {
                canclimbtemp = true;
                usedLadder = ladderRect;
                if(goingDown && rect.y+rect.h > ladderRect.y+ladderRect.h)
                {
                    vy = 0;
                    gravityState = 0;
                }
            }
        }
    }
    if(canclimbtemp)
    {
        canClimb = true;
        onGround = false;
    }
    else canClimb = false;
    
    // turn off gravity when on ladder
    if(canClimb && (isMovingUp || isMovingDown)) gravityState = 0.0;
    else gravityState = gravity;
    
    // handle movement
    if(isMovingLeft)
    {
        if(accelerationStateX == 0) accelerationStateX = -speed/2;
        if(accelerationStateX > -speed)
            accelerationStateX -= acceleration;
    }
    if(isMovingRight)
    {
        if(accelerationStateX == 0) accelerationStateX = speed/2;
        if(accelerationStateX < speed)
            accelerationStateX += acceleration;
    }
    if(isMovingUp && canClimb)
    {
        if(accelerationStateY == 0) accelerationStateY = -speed/4;
        if(accelerationStateY > -speed)
            accelerationStateY -= acceleration/2;
    }
    else if(isMovingUp && !canClimb)
    {
        stopMovinUp();
        accelerationStateY = 0;
    }
    if(isMovingDown && canClimb)
    {
        if(accelerationStateY == 0) accelerationStateY = speed/4;
        if(accelerationStateY < speed)
            accelerationStateY += acceleration/2;
        goingDown = true;
    }
    else if(isMovingDown && !canClimb)
    {
        stopMovingDown();
        accelerationStateY = 0;
    }
    
    // jump
    if(!canClimb && vy == 0)
    {
        onGround = true;
    }
    
    // check for collision with barrels
    Barrel** enemyBarrels = enemy->getBarrels();
    int barrelAmount = enemy->getBarrelAmount();
    for(int i = 0; i < barrelAmount; i++)
    {
        Barrel* currentBarrel = enemyBarrels[i];
        if(!currentBarrel->isOffScreen())
        {
            SDL_Rect barrelRect = currentBarrel->getRect();
            SDL_Rect tempPlayerRect = {rect.x, rect.y + 48, rect.w, rect.h};
            if(SDL_HasIntersection(&rect, &barrelRect))
            {
                health--;
                healthLost = true;
            }
            // check if player jumped over a barrel
            else if(SDL_HasIntersection(&tempPlayerRect, &barrelRect) && jumped)
            {
                jumped = false;
                jumpedOverBarrel = true;
            }
        }
    }
    if(onGround) jumped = false;
    
    // check for collision with villager
    if(SDL_HasIntersection(&rect, &villagerRect))
    {
        nextLevel = true;
    }
    
    if(SDL_HasIntersection(&rect, &map->getDiamond1Rect()))
    {
        gotDiamond = true;
        map->removeDiamond1();
    }
    if(SDL_HasIntersection(&rect, &map->getDiamond2Rect()))
    {
        gotDiamond = true;
        map->removeDiamond2();
    }
    // tests
//    printf("AccelerationStateX: %f\n", accelerationStateX);
//    printf("AccelerationStateY: %f\n", accelerationStateY);
//    if(canClimb) printf("Can climb\n");
}

void Player::handlePlayerMovement(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                startMovingLeft();
                break;
            case SDLK_RIGHT:
                startMovingRight();
                break;
            // ladder
            case SDLK_UP:
                if(canClimb)
                {
                    startMovingUp();
                }
                break;
            case SDLK_DOWN:
                if(canClimb)
                {
                    startMovingDown();
                }
                break;
            case SDLK_SPACE:
                jump();
                break;
                
            default:
                break;
        }
    }
    else if(e.type == SDL_KEYUP)
    {
        accelerationStateX = 0.0;
        accelerationStateY = 0.0;
        goingDown = false;
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                stopMovingRight();
                break;
            case SDLK_LEFT:
                stopMovingLeft();
                break;
            case SDLK_UP:
                stopMovinUp();
                break;
            case SDLK_DOWN:
                stopMovingDown();
                break;
        }
    }
}

bool Player::isColliding(SDL_Rect &r)
{
    return SDL_HasIntersection(&rect, &r);
}

void Player::startMovingRight()
{
    isMovingRight = true;
}
void Player::stopMovingRight()
{
    isMovingRight = false;
}
void Player::startMovingLeft()
{
    isMovingLeft = true;
}
void Player::stopMovingLeft()
{
    isMovingLeft = false;
}
void Player::startMovingUp()
{
    isMovingUp = true;
}
void Player::stopMovinUp()
{
    isMovingUp = false;
}
void Player::startMovingDown()
{
    isMovingDown = true;
}
void Player::stopMovingDown()
{
    isMovingDown = false;
}

void Player::jump()
{
    if(onGround)
    {
        vy = -jumpVelocity;
        onGround = false;
        jumped = true;
    }
}

void Player::stop()
{
    vx = 0;
    vy = 0;
    accelerationStateX = 0;
    accelerationStateY = 0;
}
