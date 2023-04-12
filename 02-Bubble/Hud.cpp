#include "Hud.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum SkeletonAnims
{
	n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, DANCE
};

Hud::Hud() {
	currentTime = 0.0f;
}

Hud::~Hud() {
	if (spriteV != NULL) delete spriteV;
	if (tex != NULL) delete tex;
}

void Hud::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

	
	spritesheet.loadFromFile("images/numeros.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteV = Sprite::createSprite(glm::ivec2(16,16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteT1 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteT2 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteP1 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteP2 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteP3 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteP4 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteP5 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteP6 = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	spriteL = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);

	spriteV->setNumberAnimations(10);
	spriteV->setAnimationSpeed(n0, 1);
	spriteV->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteV->setAnimationSpeed(n1, 1);
	spriteV->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteV->setAnimationSpeed(n2, 1);
	spriteV->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteV->setAnimationSpeed(n3, 1);
	spriteV->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteV->setAnimationSpeed(n4, 1);
	spriteV->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteV->setAnimationSpeed(n5, 1);
	spriteV->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteV->setAnimationSpeed(n6, 1);
	spriteV->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteV->setAnimationSpeed(n7, 1);
	spriteV->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteV->setAnimationSpeed(n8, 1);
	spriteV->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteV->setAnimationSpeed(n9, 1);
	spriteV->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteV->changeAnimation(0);

	spriteT1->setNumberAnimations(10);
	spriteT1->setAnimationSpeed(n0, 1);
	spriteT1->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteT1->setAnimationSpeed(n1, 1);
	spriteT1->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteT1->setAnimationSpeed(n2, 1);
	spriteT1->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteT1->setAnimationSpeed(n3, 1);
	spriteT1->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteT1->setAnimationSpeed(n4, 1);
	spriteT1->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteT1->setAnimationSpeed(n5, 1);
	spriteT1->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteT1->setAnimationSpeed(n6, 1);
	spriteT1->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteT1->setAnimationSpeed(n7, 1);
	spriteT1->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteT1->setAnimationSpeed(n8, 1);
	spriteT1->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteT1->setAnimationSpeed(n9, 1);
	spriteT1->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteT1->changeAnimation(0);

	spriteT2->setNumberAnimations(10);
	spriteT2->setAnimationSpeed(n0, 1);
	spriteT2->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteT2->setAnimationSpeed(n1, 1);
	spriteT2->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteT2->setAnimationSpeed(n2, 1);
	spriteT2->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteT2->setAnimationSpeed(n3, 1);
	spriteT2->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteT2->setAnimationSpeed(n4, 1);
	spriteT2->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteT2->setAnimationSpeed(n5, 1);
	spriteT2->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteT2->setAnimationSpeed(n6, 1);
	spriteT2->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteT2->setAnimationSpeed(n7, 1);
	spriteT2->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteT2->setAnimationSpeed(n8, 1);
	spriteT2->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteT2->setAnimationSpeed(n9, 1);
	spriteT2->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteT2->changeAnimation(0);

	spriteP1->setNumberAnimations(10);
	spriteP1->setAnimationSpeed(n0, 1);
	spriteP1->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteP1->setAnimationSpeed(n1, 1);
	spriteP1->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteP1->setAnimationSpeed(n2, 1);
	spriteP1->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteP1->setAnimationSpeed(n3, 1);
	spriteP1->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteP1->setAnimationSpeed(n4, 1);
	spriteP1->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteP1->setAnimationSpeed(n5, 1);
	spriteP1->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteP1->setAnimationSpeed(n6, 1);
	spriteP1->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteP1->setAnimationSpeed(n7, 1);
	spriteP1->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteP1->setAnimationSpeed(n8, 1);
	spriteP1->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteP1->setAnimationSpeed(n9, 1);
	spriteP1->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteP1->changeAnimation(0);

	spriteP2->setNumberAnimations(10);
	spriteP2->setAnimationSpeed(n0, 1);
	spriteP2->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteP2->setAnimationSpeed(n1, 1);
	spriteP2->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteP2->setAnimationSpeed(n2, 1);
	spriteP2->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteP2->setAnimationSpeed(n3, 1);
	spriteP2->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteP2->setAnimationSpeed(n4, 1);
	spriteP2->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteP2->setAnimationSpeed(n5, 1);
	spriteP2->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteP2->setAnimationSpeed(n6, 1);
	spriteP2->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteP2->setAnimationSpeed(n7, 1);
	spriteP2->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteP2->setAnimationSpeed(n8, 1);
	spriteP2->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteP2->setAnimationSpeed(n9, 1);
	spriteP2->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteP2->changeAnimation(0);

	spriteP3->setNumberAnimations(10);
	spriteP3->setAnimationSpeed(n0, 1);
	spriteP3->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteP3->setAnimationSpeed(n1, 1);
	spriteP3->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteP3->setAnimationSpeed(n2, 1);
	spriteP3->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteP3->setAnimationSpeed(n3, 1);
	spriteP3->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteP3->setAnimationSpeed(n4, 1);
	spriteP3->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteP3->setAnimationSpeed(n5, 1);
	spriteP3->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteP3->setAnimationSpeed(n6, 1);
	spriteP3->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteP3->setAnimationSpeed(n7, 1);
	spriteP3->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteP3->setAnimationSpeed(n8, 1);
	spriteP3->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteP3->setAnimationSpeed(n9, 1);
	spriteP3->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteP3->changeAnimation(0);

	spriteP4->setNumberAnimations(10);
	spriteP4->setAnimationSpeed(n0, 1);
	spriteP4->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteP4->setAnimationSpeed(n1, 1);
	spriteP4->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteP4->setAnimationSpeed(n2, 1);
	spriteP4->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteP4->setAnimationSpeed(n3, 1);
	spriteP4->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteP4->setAnimationSpeed(n4, 1);
	spriteP4->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteP4->setAnimationSpeed(n5, 1);
	spriteP4->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteP4->setAnimationSpeed(n6, 1);
	spriteP4->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteP4->setAnimationSpeed(n7, 1);
	spriteP4->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteP4->setAnimationSpeed(n8, 1);
	spriteP4->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteP4->setAnimationSpeed(n9, 1);
	spriteP4->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteP4->changeAnimation(0);

	spriteP5->setNumberAnimations(10);
	spriteP5->setAnimationSpeed(n0, 1);
	spriteP5->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteP5->setAnimationSpeed(n1, 1);
	spriteP5->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteP5->setAnimationSpeed(n2, 1);
	spriteP5->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteP5->setAnimationSpeed(n3, 1);
	spriteP5->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteP5->setAnimationSpeed(n4, 1);
	spriteP5->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteP5->setAnimationSpeed(n5, 1);
	spriteP5->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteP5->setAnimationSpeed(n6, 1);
	spriteP5->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteP5->setAnimationSpeed(n7, 1);
	spriteP5->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteP5->setAnimationSpeed(n8, 1);
	spriteP5->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteP5->setAnimationSpeed(n9, 1);
	spriteP5->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteP5->changeAnimation(0);

	spriteP6->setNumberAnimations(10);
	spriteP6->setAnimationSpeed(n0, 1);
	spriteP6->addKeyframe(n0, glm::vec2(0.f, 0.0f));
	spriteP6->setAnimationSpeed(n1, 1);
	spriteP6->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteP6->setAnimationSpeed(n2, 1);
	spriteP6->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteP6->setAnimationSpeed(n3, 1);
	spriteP6->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteP6->setAnimationSpeed(n4, 1);
	spriteP6->addKeyframe(n4, glm::vec2(0.25f, 0.25f));
	spriteP6->setAnimationSpeed(n5, 1);
	spriteP6->addKeyframe(n5, glm::vec2(0.5f, 0.25f));
	spriteP6->setAnimationSpeed(n6, 1);
	spriteP6->addKeyframe(n6, glm::vec2(0.f, 0.5f));
	spriteP6->setAnimationSpeed(n7, 1);
	spriteP6->addKeyframe(n7, glm::vec2(0.25f, 0.5f));
	spriteP6->setAnimationSpeed(n8, 1);
	spriteP6->addKeyframe(n8, glm::vec2(0.5f, 0.5f));
	spriteP6->setAnimationSpeed(n9, 1);
	spriteP6->addKeyframe(n9, glm::vec2(0.f, 0.75f));
	spriteP6->changeAnimation(0);

	spriteL->setNumberAnimations(4);
	spriteL->setAnimationSpeed(n1, 1);
	spriteL->addKeyframe(n1, glm::vec2(0.25f, 0.f));
	spriteL->setAnimationSpeed(n2, 1);
	spriteL->addKeyframe(n2, glm::vec2(0.5f, 0.f));
	spriteL->setAnimationSpeed(n3, 1);
	spriteL->addKeyframe(n3, glm::vec2(0.0f, 0.25f));
	spriteL->changeAnimation(1);

	tileMapDispl = tileMapPos;
	spriteV->setPosition(glm::vec2(float(tileMapDispl.x+400), float(tileMapDispl.y + 39)));
	spriteT1->setPosition(glm::vec2(float(tileMapDispl.x + 166), float(tileMapDispl.y + 53)));
	spriteT2->setPosition(glm::vec2(float(tileMapDispl.x + 150), float(tileMapDispl.y + 53)));
	spriteP1->setPosition(glm::vec2(float(tileMapDispl.x + 230), float(tileMapDispl.y + 26)));
	spriteP2->setPosition(glm::vec2(float(tileMapDispl.x + 214), float(tileMapDispl.y + 26)));
	spriteP3->setPosition(glm::vec2(float(tileMapDispl.x + 198), float(tileMapDispl.y + 26)));
	spriteP4->setPosition(glm::vec2(float(tileMapDispl.x + 182), float(tileMapDispl.y + 26)));
	spriteP5->setPosition(glm::vec2(float(tileMapDispl.x + 166), float(tileMapDispl.y + 26)));
	spriteP6->setPosition(glm::vec2(float(tileMapDispl.x + 150), float(tileMapDispl.y + 26)));
	spriteL->setPosition(glm::vec2(float(tileMapDispl.x + 316), float(tileMapDispl.y + 53)));
}

void Hud::update(int deltaTime) {
	currentTime += deltaTime;
}

void Hud::render() {
	ShaderProgramManager::instance().useShaderProgram();
	spriteV->render();
	spriteT1->render();
	spriteT2->render();
	spriteP1->render();
	spriteP2->render();
	spriteP3->render();
	spriteP4->render();
	spriteP5->render();
	spriteP6->render();
	spriteL->render();
}

void Hud::setTime(int seconds){
	if (seconds >= 0) {
		int s = seconds % 10;
		spriteT1->changeAnimation(s);
		seconds = seconds / 10;
		s = seconds % 10;
		spriteT2->changeAnimation(s);
	}
}

void Hud::setLvl(string lvl) {
	if (lvl == "0") spriteL->changeAnimation(1);
	else if (lvl == "1") spriteL->changeAnimation(2);
	else if (lvl == "2") spriteL->changeAnimation(3);
}

void Hud::setPoints(int points) {
	int p = points%10;
	spriteP1->changeAnimation(p);
	points =points/10;
	p = points%10;
	spriteP2->changeAnimation(p);
	points = points / 10;
	p = points % 10;
	spriteP3->changeAnimation(p);
	points = points / 10;
	p = points % 10;
	spriteP4->changeAnimation(p);
	points = points / 10;
	p = points % 10;
	spriteP5->changeAnimation(p);
	points = points / 10;
	p = points % 10;
	spriteP6->changeAnimation(p);
}

void Hud::setLife(int life) {
	spriteV->changeAnimation(life);
}

