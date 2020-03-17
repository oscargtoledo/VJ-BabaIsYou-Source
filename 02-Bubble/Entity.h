#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE


enum EntityType { User = 0, MoveBlock = 1 };

#include "Sprite.h"
#include <string>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <vector>



using std::string;



class Entity
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& spriteSize);


	void move(glm::ivec2 increment);
	void update(int deltaTime);
	bool hasCollision();
	bool canStop();
	bool isMoving();
	void setCollision(bool collision);
	void setStop(bool stop);
	glm::ivec2 getGridPos();
	void setGridPos(glm::ivec2 pos);
	void setPosition(const glm::vec2& pos, int tileSize);
	glm::vec2 getPosition();
	string getInfo();
	void render();
	EntityType getEntityType();
	void setEntityType(EntityType type);




	string spriteFile = "images/bub.png";
	glm::vec2 spriteTCoords = glm::vec2(.25f, .25f);
	bool isStop = false;
	float fMoveSpeed = 0.005f;
	float fMoveFraction;
	glm::ivec2 moveDestination;
	glm::ivec2 tileMapDispl, posPlayer;
	glm::ivec2 spriteSize;
	glm::ivec2 gridPos;
	Texture spritesheet;
	Sprite* sprite;
	bool bJumping = false;
	bool bMoving = false;
	EntityType entityType;


private:
	bool test;






};


#endif

