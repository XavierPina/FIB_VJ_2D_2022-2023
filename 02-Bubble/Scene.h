#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "ShaderProgramManager.h"
#include "TileMap.h"
#include "Player.h"
#include "TexturedQuad.h"
#include "Skeleton.h"
#include "Vampire.h"
#include "Hud.h"
#include "Object.h"
#include "Menu.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void initLvl(string lvl);
	void gameOver(bool win);

private:
	void initShaders();

private:
	int puntuacion, vidas, tiempo, segundos, p1, p2, p3, p4, stop, segundos2;
	TileMap *map;
	Texture* screen;
	Texture* hudScreen;
	TexturedQuad* bground;
	TexturedQuad* hudBackground;
	Hud* hud;
	Player *player;
	Skeleton* skeleton1;
	Skeleton* skeleton2;
	Skeleton* skeleton3;
	Vampire* vampire1;
	Vampire* vampire2;
	Object* key;
	Object* gem;
	Object* watch;
	Object* sand;
	ShaderProgram texProgram;
	string currentLvl;
	float currentTime;
	glm::mat4 projection;
	bool visGem, visWatch, viSand, pausa, finnish;
	

};


#endif // _SCENE_INCLUDE

