#ifndef _SKEL_INCLUDE
#define _SKEL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Skeleton
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool collisionPlayer(const glm::ivec2& pos, const glm::ivec2& size);

private:
	bool fly, up, down;
	glm::ivec2 tileMapDispl, posEnemy, posAux;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif


