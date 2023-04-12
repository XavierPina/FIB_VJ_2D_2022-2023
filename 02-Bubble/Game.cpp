#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	ShaderProgramManager::instance().init();
	bPlay = true;
	menuUP = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	menuScreen = new Menu();
	menuScreen->init(ShaderProgramManager::instance().getShaderProgram());

	scene = new Scene();
	scene->init();
}

bool Game::update(int deltaTime)
{

	if (menuUP) menuScreen->update(deltaTime);
	else {
		scene->update(deltaTime);
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (menuUP) menuScreen->render();
	else {
		scene->render(); 	
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

void Game::setMenuBool(bool m, bool win) {
	menuUP = m;
	if (m == true) {
		if (!win) menuScreen->setPosIndex(4);
		else menuScreen->setPosIndex(5);
	}
	else {
		scene->init();
	}
		
}


bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





