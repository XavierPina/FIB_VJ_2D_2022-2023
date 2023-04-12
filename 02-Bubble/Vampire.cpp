#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include <cstdlib>
#include "Vampire.h"
#include "Game.h"

#define FALL_STEP 4

enum VampireAnims
{
	MOVE_LEFT, MOVE_RIGHT, FLY_UP_LEFT, FLY_UP_RIGHT, FLY_DOWN_LEFT, FLY_DOWN_RIGHT
};


void Vampire::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	srand(time(0));
	isBat = false;
	spritesheet.loadFromFile("images/enemigosDef.png", TEXTURE_PIXEL_FORMAT_RGBA);
	vamp = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.125, 0.25), &spritesheet, &shaderProgram);

	vamp->setNumberAnimations(6);
	vamp->setAnimationSpeed(MOVE_LEFT, 3);
	vamp->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	vamp->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
	vamp->setAnimationSpeed(MOVE_RIGHT, 3);
	vamp->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.25f));
	vamp->addKeyframe(MOVE_RIGHT, glm::vec2(0.375f, 0.25f));
	vamp->setAnimationSpeed(FLY_UP_LEFT, 3);
	vamp->addKeyframe(FLY_UP_LEFT, glm::vec2(0.5f, 0.0f));
	vamp->addKeyframe(FLY_UP_LEFT, glm::vec2(0.5f, 0.25f));
	vamp->setAnimationSpeed(FLY_UP_RIGHT, 3);
	vamp->addKeyframe(FLY_UP_RIGHT, glm::vec2(0.5f, 0.5f));
	vamp->addKeyframe(FLY_UP_RIGHT, glm::vec2(0.5f, 0.75f));
	vamp->setAnimationSpeed(FLY_DOWN_LEFT, 3);
	vamp->addKeyframe(FLY_DOWN_LEFT, glm::vec2(0.5f, 0.0f));
	vamp->addKeyframe(FLY_DOWN_LEFT, glm::vec2(0.5f, 0.25f));
	vamp->setAnimationSpeed(FLY_DOWN_RIGHT, 3);
	vamp->addKeyframe(FLY_DOWN_RIGHT, glm::vec2(0.5f, 0.5f));
	vamp->addKeyframe(FLY_DOWN_RIGHT, glm::vec2(0.5f, 0.75f));


	vamp->changeAnimation(0);

	tileMapDispl = tileMapPos;
	vamp->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Vampire::update(int deltaTime)
{
	vamp->update(deltaTime);
	tiempo += deltaTime;
	if (tiempo > 3000) {
		tiempo = tiempo % 3000;
		if ((rand() % 3) == 0) {
			isBat = !isBat;
			if (vamp->animation() == (MOVE_LEFT)) vamp->changeAnimation(FLY_UP_LEFT);
			else if (vamp->animation() == (MOVE_RIGHT)) vamp->changeAnimation(FLY_UP_RIGHT);
		}
	}
	if (!isBat) {
		if (vamp->animation() == (MOVE_LEFT)) {
			posEnemy.x -= 1;
			if (map->collisionMoveLeft(posEnemy, glm::ivec2(16, 32)))
			{
				posEnemy.x += 1;
				vamp->changeAnimation(MOVE_RIGHT);
			}
			posAux = posEnemy;
			posAux.y += 1;
			posAux.x -= 16;
			if (!map->collisionMoveDown(posAux, glm::ivec2(16, 32), &posAux.y)) {
				posEnemy.x += 1;
				vamp->changeAnimation(MOVE_RIGHT);
			}
		}
		else if (vamp->animation() == (MOVE_RIGHT)) {
			posEnemy.x += 1;
			if (map->collisionMoveRight(posEnemy, glm::ivec2(16, 32)))
			{
				posEnemy.x -= 1;
				vamp->changeAnimation(MOVE_LEFT);

			}
			posAux = posEnemy;
			posAux.y += 1;
			posAux.x += 16;
			if (!map->collisionMoveDown(posAux, glm::ivec2(16, 32), &posAux.y)) {
				posEnemy.x -= 1;
				vamp->changeAnimation(MOVE_LEFT);
			}
		}
		posEnemy.y += FALL_STEP;

		if (map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			if (vamp->animation() == (FLY_UP_RIGHT) || vamp->animation() == (FLY_DOWN_RIGHT)) {
				vamp->changeAnimation(MOVE_RIGHT);
			}
			if (vamp->animation() == (FLY_UP_LEFT) || vamp->animation() == (FLY_DOWN_LEFT)) {
				vamp->changeAnimation(MOVE_LEFT);
			}

		}
	}
	else {
		if (vamp->animation() == (FLY_UP_RIGHT)) {
			posEnemy.x += 1;
			posEnemy.y -= 1;
			if (map->collisionMoveRight(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.x -= 1;
				vamp->changeAnimation(FLY_UP_LEFT);
			}
			else if (map->collisionMoveUp(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.y += 1;
				vamp->changeAnimation(FLY_DOWN_RIGHT);
			}
		}
		else if (vamp->animation() == (FLY_UP_LEFT)) {
			posEnemy.x -= 1;
			posEnemy.y -= 1;
			if (map->collisionMoveLeft(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.x += 1;
				vamp->changeAnimation(FLY_UP_RIGHT);
			}
			else if (map->collisionMoveUp(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.y += 1;
				vamp->changeAnimation(FLY_DOWN_LEFT);
			}
		}
		else if (vamp->animation() == (FLY_DOWN_RIGHT)) {
			posEnemy.x += 1;
			posEnemy.y += 1;
			if (map->collisionMoveRight(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.x -= 1;
				vamp->changeAnimation(FLY_DOWN_LEFT);
			}
			else if (map->collisionMoveDown(posEnemy, glm::ivec2(16, 32), &posEnemy.y)) {
				posEnemy.y -= 1;
				vamp->changeAnimation(FLY_UP_RIGHT);
			}
		}
		else if (vamp->animation() == (FLY_DOWN_LEFT)) {
			posEnemy.x -= 1;
			posEnemy.y += 1;
			if (map->collisionMoveLeft(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.x += 1;
				vamp->changeAnimation(FLY_DOWN_RIGHT);
			}
			else if (map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
				posEnemy.y -= 1;
				vamp->changeAnimation(FLY_UP_LEFT);
			}
		}

	}


	vamp->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Vampire::render()
{
	vamp->render();
}

void Vampire::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Vampire::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	vamp->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

bool Vampire::collisionPlayer(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x0, y0, oX, oY;
	
	x0 = pos.x;
	y0 = pos.y;
	oX = posEnemy.x;
	oY = posEnemy.y;
	if (oY == y0 && oX == x0 || oY == y0 && oX == x0 + 1
		|| oY == y0 - 1 && oX == x0 || oY == y0 - 1 && oX == x0 + 1
		|| oY == y0 + 1 && oX == x0 || oY == y0 + 1 && oX == x0 + 1) 
		return true;
	else return false;
}
