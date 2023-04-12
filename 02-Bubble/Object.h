#ifndef _OBJ_INCLUDE
#define _OBJ_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Object
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int id);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool collisionPlayer(const glm::ivec2& pos, const glm::ivec2& size, int* posY);

private:
	bool fly, up, down;
	glm::ivec2 tileMapDispl, posObj, posAux;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int oId;

};


#endif#pragma once
