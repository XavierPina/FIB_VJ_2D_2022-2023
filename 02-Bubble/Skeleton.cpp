#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Skeleton.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum SkeletonAnims
{
	MOVE_LEFT, MOVE_RIGHT, MOVE_UP_LEFT
};


void Skeleton::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/enemigosDef.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.125, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.375f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Skeleton::update(int deltaTime)
{
	sprite->update(deltaTime);
	
	
	if (sprite->animation() == (MOVE_LEFT)) {
		posEnemy.x -= 1;
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(16, 32)))
		{
			posEnemy.x += 1;
			sprite->changeAnimation(MOVE_RIGHT);
		}
		posAux = posEnemy;
		posAux.y += 1;
		posAux.x -= 16;
		if (!map->collisionMoveDown(posAux, glm::ivec2(16, 32), &posAux.y)) {
			posEnemy.x += 1;
			sprite->changeAnimation(MOVE_RIGHT);
		}
	}

	else if (sprite->animation() == (MOVE_RIGHT)) {
		posEnemy.x += 1;
		if (map->collisionMoveRight(posEnemy, glm::ivec2(16, 32)))
		{
			posEnemy.x -= 1;
			sprite->changeAnimation(MOVE_LEFT);

		}
		posAux = posEnemy;
		posAux.y += 1;
		posAux.x += 16;
		if (!map->collisionMoveDown(posAux, glm::ivec2(16, 32), &posAux.y)) {
			posEnemy.x -= 1;
			sprite->changeAnimation(MOVE_LEFT);
		}
	}
	

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Skeleton::render()
{
	sprite->render();
}

void Skeleton::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Skeleton::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

bool Skeleton::collisionPlayer(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x0, y0, oX, oY, tSize;
	tSize = map->getTileSize();
	x0 = pos.x / tSize;
	y0 = pos.y / tSize;
	oX = posEnemy.x / tSize;
	oY = posEnemy.y / tSize;
	if (oY == y0 && oX == x0 || oY == y0 && oX == x0 + 1
		|| oY == y0 - 1 && oX == x0 || oY == y0 - 1 && oX == x0 + 1
		|| oY == y0 + 1 && oX == x0 || oY == y0 + 1 && oX == x0 + 1) return true;
	else return false;
}
