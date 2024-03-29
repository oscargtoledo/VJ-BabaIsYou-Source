#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, const glm::ivec2& spriteSize)
{
	test = false;
	bJumping = false;
	bMoving = false;
	fMoveSpeed = 0.01f;
	fMoveFraction = 0.f;
	moveDestination = glm::ivec2(NULL, NULL);

	this->spriteSize = spriteSize;
	//spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.loadFromFile(spriteFile, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(this->spriteSize, spriteTCoords, &spritesheet, &shaderProgram);
	/*sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));
		
	sprite->changeAnimation(0);*/
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::changeSprite(string file, glm::vec2 coords)
{
	spriteFile = file;
	spriteTCoords = coords;
}

void Player::update(int deltaTime)
{
	//glm::ivec2 spriteSize = glm::ivec2(32, 32);
	sprite->update(deltaTime);

	/*string msg = "Pos X"+to_string(posPlayer.x) + "Pos Y" + to_string(posPlayer.y)+"\n";
	OutputDebugStringA(msg.c_str());/
	msg = "Pos X" + to_string((posPlayer.x)/map->getTileSize()) + "Pos Y" + to_string((posPlayer.y) / map->getTileSize()) + "\n";
	OutputDebugStringA(msg.c_str());*/
	if (bMoving) {
		if (fMoveFraction < 1)
		{
			fMoveFraction += deltaTime * fMoveSpeed;

			posPlayer = glm::mix(posPlayer, moveDestination, fMoveFraction);
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		}
		else {
			fMoveFraction = 0.f;
			moveDestination = glm::ivec2(NULL, NULL);
			bMoving = false;
		}
	}
	else
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			
			/*if(sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if(map->collisionMoveLeft(posPlayer, spriteSize))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}*/
			/*glm::ivec2 mapPos = glm::ivec2((posPlayer.x) / map->getTileSize(), (posPlayer.y) / map->getTileSize());
			MapEntity* foundEntity = posMap->getEntity(mapPos.x - 1, mapPos.y);
			if (foundEntity->type == Property)
			{
				OutputDebugString(L"Property Found");
				foundEntity->entity->setPosition(glm::ivec2(0, 0));
				posMap->moveEntity(glm::ivec2(mapPos.x - 1, mapPos.y), glm::ivec2(mapPos.x - 2, mapPos.y));
			}*/
			moveDestination = posPlayer;
			moveDestination.x -= map->getTileSize();
			sprite->changeAnimation(STAND_LEFT);
			bMoving = true;


		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			/*if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, spriteSize))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}*/

			/*glm::ivec2 mapPos = glm::ivec2((posPlayer.x) / map->getTileSize(), (posPlayer.y) / map->getTileSize());
			if (posMap->getEntity(mapPos.x + 1, mapPos.y)->type == Property)
			{
				OutputDebugString(L"Property Found");
				posMap->getEntity(mapPos.x + 1, mapPos.y)->entity->setPosition(glm::ivec2(0, 0));

			}*/
			moveDestination = posPlayer;
			moveDestination.x += map->getTileSize();
			sprite->changeAnimation(STAND_RIGHT);
			bMoving = true;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			moveDestination = posPlayer;
			moveDestination.y -= map->getTileSize();
			sprite->changeAnimation(STAND_RIGHT);
			bMoving = true;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			moveDestination = posPlayer;
			moveDestination.y += map->getTileSize();
			sprite->changeAnimation(STAND_RIGHT);
			bMoving = true;
		}
		else if (Game::instance().getKey(32))
		{
			test = !test;
		}
		/*else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}

		if (bJumping)
		{
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else
			{
				posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
				if (!map->collisionMoveUp(posPlayer, spriteSize, &posPlayer.y)) {
					if (jumpAngle > 90)
						bJumping = !map->collisionMoveDown(posPlayer, spriteSize, &posPlayer.y);
				}
				else {
					bJumping = false;
				}

			}
		}
		else
		{
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, spriteSize, &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}*/

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}

}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




