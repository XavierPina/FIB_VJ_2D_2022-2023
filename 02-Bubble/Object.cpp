#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Object.h"
#include "Game.h"

enum ObjAnims
{
	APPEAR, KEY, GEM, WATCH, SAND
};


void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int id)
{
	oId = id;

	spritesheet.loadFromFile("images/enemigosDef.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(APPEAR, 2);
	sprite->addKeyframe(APPEAR, glm::vec2(0.625f, 0.f));
	sprite->addKeyframe(APPEAR, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(KEY, 2);
	sprite->addKeyframe(KEY, glm::vec2(0.625f, 0.125f));
	sprite->addKeyframe(KEY, glm::vec2(0.625f, 0.25f));

	sprite->setAnimationSpeed(GEM, 2);
	sprite->addKeyframe(GEM, glm::vec2(0.75f, 0.125f));
	sprite->addKeyframe(GEM, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(WATCH, 2);
	sprite->addKeyframe(WATCH, glm::vec2(0.75f, 0.375f));
	sprite->addKeyframe(WATCH, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(SAND, 2);
	sprite->addKeyframe(SAND, glm::vec2(0.625f, 0.375f));
	sprite->addKeyframe(SAND, glm::vec2(0.625f, 0.5f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y)));

}

void Object::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (sprite->animation() == APPEAR && oId == 1) sprite->changeAnimation(KEY);
	else if (sprite->animation() == APPEAR && oId == 2) sprite->changeAnimation(GEM);
	else if (sprite->animation() == APPEAR && oId == 3) sprite->changeAnimation(WATCH);
	else if (sprite->animation() == APPEAR && oId == 4) sprite->changeAnimation(SAND);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y)));
}

void Object::render()
{
	sprite->render();
}

void Object::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Object::setPosition(const glm::vec2& pos)
{
	posObj = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y)));
}

bool Object::collisionPlayer(const glm::ivec2& pos, const glm::ivec2& size, int* posY)
{
	int x0, y0, y1, x1, oX, oY, tSize;
	tSize = map->getTileSize();
	x0 = pos.x / tSize;
	y0 = pos.y / tSize;
	x1 = (pos.x + size.x - 1) / tSize;
	/*y1 = (pos.y + size.y - 1) / tSize;*/
	oX = posObj.x / tSize;
	oY = posObj.y / tSize;
	/*bool ytrue = false;
	bool xtrue = false;*/
	//if (y0 >= oY && y1 <= oY && x0 >= oX && x1 <= oX) return true;
	if (oY == y0 && oX == x0 - 4 || oY == y0 && oX == x0 - 3 
		|| oY == y0 + 1 && oX == x0 - 4 || oY == y0 + 1 && oX == x0 - 3 
		|| oY == y0 && oX == x1 - 4 || oY == y0 && oX == x1 - 3
		|| oY == y0 + 1 && oX == x1 - 4 || oY == y0 + 1 && oX == x1 - 3) return true;
	/*if ((oY == y0 || oY == y0 + 1) && (oX == x0 - 2 || oX == x0 - 1 || oX == x1 - 2 || oX == x1 - 1)) return true;*/
	/*for (int y = y0; y <= y1; y++)
	{
		if (y0 + (1/tSize) == oY) ytrue = true;
		
	}
	for (int x = x0; x <= x1; x++)
	{
		if (x0 == oX) xtrue = true;
	}
	if (ytrue && xtrue) return true;*/
	else return false;
}