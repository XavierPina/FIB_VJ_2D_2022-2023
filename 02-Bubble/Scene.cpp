#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

int initPlayerXTiles = 10;
int initPlayerYTiles = 10;

Scene::Scene()
{
	map = NULL;
	player = NULL;
	skeleton1 = NULL;
	skeleton2 = NULL;
	skeleton3 = NULL;
	vampire1 = NULL;
	vampire2 = NULL;
	key = NULL;
	gem = NULL;
	watch = NULL;
	sand = NULL;
	vidas = 5;
	puntuacion = 0;
	currentLvl = "0";
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	segundos = 0;
	hud = new Hud();
	hud->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	hud->setLife(vidas);
	hud->setPoints(puntuacion);
	hud->setLvl(currentLvl);
	player = new Player();
	skeleton1 = new Skeleton();
	skeleton2 = new Skeleton();
	skeleton3 = new Skeleton();
	vampire1 = new Vampire();
	vampire2 = new Vampire();
	key = new Object();
	gem = new Object();
	watch = new Object();
	sand = new Object();
	stop = 0;
	initLvl(currentLvl);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= 3000) pausa = false;
	if (Game::instance().getKey(49)) {
		currentLvl = "0";
		vidas = 5;
		initLvl(currentLvl);
	}
	if (Game::instance().getKey(50)) {
		currentLvl = "1";
		vidas = 5;
		initLvl(currentLvl);
	}
	if (Game::instance().getKey(51)) {
		currentLvl = "2";
		vidas = 5;
		initLvl(currentLvl);
	}
	if (!pausa) {
		if (Game::instance().getKey(75) || Game::instance().getKey(107)) map->visKey = true;
		if (Game::instance().getKey(71) || Game::instance().getKey(103)) player->godMode = true;

		if (stop == 0) segundos += deltaTime;
		if (segundos > 1000) {
			int s = segundos / 1000;
			tiempo -= s;
			segundos = segundos % 1000;
			hud->setTime(tiempo);
		}
		else if (stop != 0) --stop;
		if (finnish) {
			segundos2 += deltaTime;
			if (segundos2 > 100 && tiempo > 0) {
				int s = segundos2 / 100;
				tiempo -= s;
				segundos2 = segundos2 % 100;
				hud->setTime(tiempo);
				puntuacion += 100;
				hud->setPoints(puntuacion);
			}
		}

		if (tiempo == 0 && !finnish) {
			--vidas;
			if (vidas == 0) gameOver(false);
			else initLvl(currentLvl);
		}
		if (map->paint == true) {
			puntuacion += 100;
			hud->setPoints(puntuacion);
			map->paint = false;
		}

		if (!finnish) player->update(deltaTime);
		if (tiempo == 0 && finnish) {
			if (currentLvl == "0") {
				currentLvl = "1";
			}
			else if (currentLvl == "1") {
				currentLvl = "2";
			}
			else {
				currentLvl = "0";
				gameOver(true);
			}
			initLvl(currentLvl);
		}
		if (player->checkDoor()) finnish = true;
		if ((player->inSpikes || player->checkDamageS(skeleton1) || player->checkDamageS(skeleton2) || player->checkDamageS(skeleton3) || player->checkDamageV(vampire1) || player->checkDamageV(vampire2)) && player->godMode == false) {
			--vidas;
			if (vidas == 0) gameOver(false);
			else initLvl(currentLvl);
		}

		key->update(deltaTime);
		if (map->visKey && player->checkCollision(key)) {
			map->visKey = false;
			map->picKey = true;
			render();
			map->paintDoor(p1, p2, p3, p4);
		}
		gem->update(deltaTime);
		if (visGem && player->checkCollision(gem)) {
			visGem = false;
			render();
			puntuacion += 500;
			hud->setPoints(puntuacion);
		}
		watch->update(deltaTime);
		if (visWatch && player->checkCollision(watch)) {
			visWatch = false;
			render();
			tiempo = 60;
			hud->setTime(tiempo);
		}
		sand->update(deltaTime);
		if (viSand && player->checkCollision(sand)) {
			viSand = false;
			render();
			stop = 1000;
		}
 
		if (stop == 0 && !finnish) {
			skeleton1->update(deltaTime);
			skeleton2->update(deltaTime);
			if (currentLvl == "2") {
				vampire1->update(deltaTime);
				vampire2->update(deltaTime);
			}
			else skeleton3->update(deltaTime);
		}
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	bground->render(*screen);
	map->render();
	hudBackground->render(*hudScreen);

	player->render();

	skeleton1->render();
	skeleton2->render();
	if (currentLvl == "2") {
		vampire1->render();
		vampire2->render();
	}
	else skeleton3->render();
	
	hud->render();
	if (map->visKey) key->render();
	if (visGem) gem->render();
	if (visWatch) watch->render();
	if (viSand) sand->render();
}

void Scene::initLvl(string lvl) {

	glm::vec2 geom[2] = { glm::vec2(60.f, 80.f), glm::vec2(535.f, 440.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, ShaderProgramManager::instance().getShaderProgram());
	screen = new Texture();
	screen ->loadFromFile("images/Background0"+lvl+".png", TEXTURE_PIXEL_FORMAT_RGBA);

	glm::vec2 geom2[2] = { glm::vec2(0.f, 0.f), glm::vec2(576.f, 96.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	hudBackground = TexturedQuad::createTexturedQuad(geom2, texCoords2, ShaderProgramManager::instance().getShaderProgram());
	hudScreen = new Texture();
	hudScreen->loadFromFile("images/Hud.png", TEXTURE_PIXEL_FORMAT_RGBA);

	map = TileMap::createTileMap("levels/level0" + lvl + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	visGem = true;
	visWatch = true;
	viSand = true;
	pausa = true;
	stop = 0;
	finnish = false;
	segundos2 = 0;

	hud->setLvl(currentLvl);
	tiempo = 60;
	hud->setTime(tiempo);
	hud->setLife(vidas);

	if (currentLvl == "0") {
		map->maxTiles = 61;
		p1 = 606;
		p2 = 607;
		p3 = 642;
		p4 = 643;
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		initPlayerXTiles = 10;
		initPlayerYTiles = 14;
		player->setPosition(glm::vec2(initPlayerXTiles * map->getTileSize(), initPlayerYTiles * map->getTileSize()));
		player->setTileMap(map);

		skeleton1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton1->setPosition(glm::vec2(23 * map->getTileSize(), 8 * map->getTileSize()));
		skeleton1->setTileMap(map);
		skeleton2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton2->setPosition(glm::vec2(9 * map->getTileSize(), 21 * map->getTileSize()));
		skeleton2->setTileMap(map);
		skeleton3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton3->setPosition(glm::vec2(23 * map->getTileSize(), 23 * map->getTileSize()));
		skeleton3->setTileMap(map);

		key->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
		key->setPosition(glm::vec2(20 * map->getTileSize(), 24 * map->getTileSize()));
		key->setTileMap(map);
		gem->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2);
		gem->setPosition(glm::vec2(14 * map->getTileSize(), 25 * map->getTileSize()));
		gem->setTileMap(map);
		watch->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3);
		watch->setPosition(glm::vec2(16 * map->getTileSize(), 9 * map->getTileSize()));
		watch->setTileMap(map);
		sand->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 4);
		sand->setPosition(glm::vec2(6 * map->getTileSize(), 12 * map->getTileSize()));
		sand->setTileMap(map);
	}
	else if (currentLvl == "1") {
		map->maxTiles = 108;
		p1 = 458;
		p2 = 459;
		p3 = 494;
		p4 = 495;
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		initPlayerXTiles = 17;
		initPlayerYTiles = 24;
		player->setPosition(glm::vec2(initPlayerXTiles * map->getTileSize(), initPlayerYTiles * map->getTileSize()));
		player->setTileMap(map);

		skeleton1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton1->setPosition(glm::vec2(15 * map->getTileSize(), 12 * map->getTileSize()));
		skeleton1->setTileMap(map);
		skeleton2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton2->setPosition(glm::vec2(20 * map->getTileSize(), 12 * map->getTileSize()));
		skeleton2->setTileMap(map);
		skeleton3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton3->setPosition(glm::vec2(15 * map->getTileSize(), 15 * map->getTileSize()));
		skeleton3->setTileMap(map);

		key->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
		key->setPosition(glm::vec2(12 * map->getTileSize(), 16 * map->getTileSize()));
		key->setTileMap(map);
		gem->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2);
		gem->setPosition(glm::vec2(20 * map->getTileSize(), 22 * map->getTileSize()));
		gem->setTileMap(map);
		watch->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3);
		watch->setPosition(glm::vec2(20 * map->getTileSize(), 10 * map->getTileSize()));
		watch->setTileMap(map);
		sand->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 4);
		sand->setPosition(glm::vec2(8 * map->getTileSize(), 13 * map->getTileSize()));
		sand->setTileMap(map);

	}
	else if (currentLvl == "2") {
		map->maxTiles = 84;
		p1 = 346;
		p2 = 347;
		p3 = 382;
		p4 = 383;
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		initPlayerXTiles = 6;
		initPlayerYTiles = 21;
		player->setPosition(glm::vec2(initPlayerXTiles * map->getTileSize(), initPlayerYTiles * map->getTileSize()));
		player->setTileMap(map);

		vampire1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		vampire1->setPosition(glm::vec2(22 * map->getTileSize(), 12 * map->getTileSize()));
		vampire1->setTileMap(map);
		vampire2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		vampire2->setPosition(glm::vec2(13 * map->getTileSize(), 12 * map->getTileSize()));
		vampire2->setTileMap(map);
		skeleton1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton1->setPosition(glm::vec2(22 * map->getTileSize(), 24 * map->getTileSize()));
		skeleton1->setTileMap(map);
		skeleton2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		skeleton2->setPosition(glm::vec2(13 * map->getTileSize(), 24 * map->getTileSize()));
		skeleton2->setTileMap(map);

		key->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
		key->setPosition(glm::vec2(10 * map->getTileSize(), 10 * map->getTileSize()));
		key->setTileMap(map);
		gem->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2);
		gem->setPosition(glm::vec2(24 * map->getTileSize(), 25 * map->getTileSize()));
		gem->setTileMap(map);
		watch->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3);
		watch->setPosition(glm::vec2(20 * map->getTileSize(), 16 * map->getTileSize()));
		watch->setTileMap(map);
		sand->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 4);
		sand->setPosition(glm::vec2(12 * map->getTileSize(), 13 * map->getTileSize()));
		sand->setTileMap(map);

	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::gameOver(bool win) {
	Game::instance().setMenuBool(true, win);
}



