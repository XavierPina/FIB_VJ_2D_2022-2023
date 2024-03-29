#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 60
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP_LEFT, MOVE_UP_RIGHT, MOVE_LEFT_COL, MOVE_RIGHT_COL, FALL_DOWN_RIGHT, FALL_DOWN_LEFT, DANCE
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	inSpikes = false;
	godMode = false;
	spritesheet.loadFromFile("images/kne.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_UP_LEFT, 8);
	sprite->addKeyframe(MOVE_UP_LEFT, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(MOVE_UP_RIGHT, 8);
	sprite->addKeyframe(MOVE_UP_RIGHT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT_COL, 8);
	sprite->addKeyframe(MOVE_LEFT_COL, glm::vec2(0.75f, 0.75f));


	sprite->setAnimationSpeed(MOVE_RIGHT_COL, 8);
	sprite->addKeyframe(MOVE_RIGHT_COL, glm::vec2(0.5f, 0.75f));


	sprite->setAnimationSpeed(FALL_DOWN_RIGHT, 4);
	sprite->addKeyframe(FALL_DOWN_RIGHT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(FALL_DOWN_LEFT, 4);
	sprite->addKeyframe(FALL_DOWN_LEFT, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(DANCE, 4);
	sprite->addKeyframe(DANCE, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(DANCE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(DANCE, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(DANCE, glm::vec2(0.f, 0.75f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	
	if (map->visKey == true) sprite->changeAnimation(DANCE);
	
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != (MOVE_LEFT)) {
			if (sprite->animation() == (MOVE_UP_RIGHT))
				sprite->changeAnimation(MOVE_UP_LEFT);
			else if (sprite->animation() != (MOVE_UP_LEFT)) 
				sprite->changeAnimation(MOVE_LEFT);
		}

		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(MOVE_LEFT_COL);

		}
		map->painTile(posPlayer, glm::ivec2(32, 32));
		if (map->spikes(posPlayer, glm::ivec2(32, 32))) {
			inSpikes = true;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != (MOVE_RIGHT)) {
			if (sprite->animation() == (MOVE_UP_LEFT))
				sprite->changeAnimation(MOVE_UP_RIGHT);
			else if (sprite->animation() != (MOVE_UP_RIGHT))
				sprite->changeAnimation(MOVE_RIGHT);
		}
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(MOVE_RIGHT_COL);
		}
		map->painTile(posPlayer, glm::ivec2(32, 32));
		if (map->spikes(posPlayer, glm::ivec2(32, 32))) {
			inSpikes = true;
		}
	}
	else
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
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
				if (sprite->animation() == MOVE_UP_LEFT)
					sprite->changeAnimation(FALL_DOWN_LEFT);
				else if (sprite->animation() == MOVE_UP_RIGHT)
					sprite->changeAnimation(FALL_DOWN_RIGHT);
			}
		}

		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_LEFT_COL) {
			sprite->changeAnimation(MOVE_UP_LEFT);
		}
		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT || sprite->animation() == MOVE_RIGHT_COL) {
			sprite->changeAnimation(MOVE_UP_RIGHT);
		}
			
	}
	else
	{
		posPlayer.y += FALL_STEP;

		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{

			if (sprite->animation() == FALL_DOWN_LEFT || sprite->animation() == MOVE_UP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == FALL_DOWN_RIGHT || sprite->animation() == MOVE_UP_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			map->painTile(posPlayer, glm::ivec2(32, 32));
			

			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
		else {
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_LEFT_COL)
				sprite->changeAnimation(FALL_DOWN_LEFT);
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == MOVE_RIGHT_COL)
				sprite->changeAnimation(FALL_DOWN_RIGHT);
			
		}
		if (map->spikes(posPlayer, glm::ivec2(32, 32))) {
			inSpikes = true;
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

bool Player::checkCollision(Object *object) {
	return object->collisionPlayer(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
}

bool Player::checkDamageS(Skeleton* skeleton) {
	return skeleton->collisionPlayer(posPlayer, glm::ivec2(32, 32));
}

bool Player::checkDamageV(Vampire* vampire) {
	return vampire->collisionPlayer(posPlayer, glm::ivec2(32, 32));
}

bool Player::checkDoor() {
	return (map->doorMoveLeft(posPlayer, glm::ivec2(32, 32)) || map->doorMoveRight(posPlayer, glm::ivec2(32, 32)) /*|| map->doorMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)*/);
}







