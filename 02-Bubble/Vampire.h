#ifndef _VAMP_INCLUDE
#define _VAMP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Vampire
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	bool collisionPlayer(const glm::ivec2& pos, const glm::ivec2& size);

private:
	bool fly, up, down, isBat;
	int tiempo;
	glm::ivec2 tileMapDispl, posEnemy, posAux;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* vamp;
	Sprite* bat;
	Sprite* enemy;
	TileMap* map;

};


#endif
