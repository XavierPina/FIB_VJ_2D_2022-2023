#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Menu.h"



enum BoxAnims
{
	ICON
};

Menu::Menu() {
	currentTime = 0.0f;

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(527.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, ShaderProgramManager::instance().getShaderProgram());
	screen1 = new Texture();
	screen1->loadFromFile("images/Menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	screen3 = new Texture();
	screen3->loadFromFile("images/Creditos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	screen2 = new Texture();
	screen2->loadFromFile("images/Instrucciones.png", TEXTURE_PIXEL_FORMAT_RGBA);
	screen4 = new Texture();
	screen4->loadFromFile("images/gameover.png", TEXTURE_PIXEL_FORMAT_RGBA);
	screen5 = new Texture();
	screen5->loadFromFile("images/gamewon.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

Menu::~Menu() {
	if (sprite != NULL) delete sprite;
	if (bground != NULL) delete bground;
}

void Menu::init(ShaderProgram& shaderProgram) {
	id = 1;
	index = 1;
	screen = screen1;
	pressed = false;
	spritesheet.loadFromFile("images/icon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	box = Sprite::createSprite(glm::ivec2(20, 24), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);

	box->setNumberAnimations(1);
	box->setAnimationSpeed(ICON, 3);
	box->addKeyframe(ICON, glm::vec2(0.f, 0.f));

	box->changeAnimation(0);
	box->setPosition(glm::vec2(float(202), float(225)));

	screen->setWrapS(GL_CLAMP_TO_EDGE);
	screen->setWrapT(GL_CLAMP_TO_EDGE);
	screen->setMinFilter(GL_NEAREST);
	screen->setMagFilter(GL_NEAREST);
}

void Menu::update(int deltaTime) {
	currentTime += deltaTime;
	box->update(deltaTime);
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !pressed) {
			if (index == 3) setPosIndex(1);
			else setPosIndex(index + 1);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !pressed) {
			if (index == 1) setPosIndex(3);
			else setPosIndex(index - 1);
		}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		if (index == 2) screen = screen2;
		else if (index == 3) screen = screen3;
		else if (index == 1) Game::instance().setMenuBool(false, false);
		pressed = true;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			if (index != 1) {
				screen = screen1;
				pressed = false;
				index = 1;
			}
	}
}

void Menu::setPosIndex(int pos) {
	index = pos;
	if (pos <= 3) {
		int y = pos * 48 + 177;
		box->setPosition(glm::vec2(float(202), float(y)));
	}
	else {
		if (pos == 4) screen = screen4;
		if (pos == 5) screen = screen5;
	}
}

void Menu::render() {
	ShaderProgramManager::instance().useShaderProgram();
	bground->render(*screen);
	if (screen == screen1) box->render();
}