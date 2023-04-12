#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE

#include "ShaderProgramManager.h"
#include <vector>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"
#include "TileMap.h"


class Hud {
public:
	Hud();
	~Hud();

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void render();
	void setTime(int seconds);
	void setLvl(string lvl);
	void setPoints(int points);
	void setLife(int life);
	void update(int deltaTime);

private:
	string lvl;
	Sprite* spriteV;
	Sprite* spriteT1;
	Sprite* spriteT2;
	Sprite* spriteP1;
	Sprite* spriteP2;
	Sprite* spriteP3;
	Sprite* spriteP4;
	Sprite* spriteP5;
	Sprite* spriteP6;
	Sprite* spriteL;
	float currentTime;
	Texture spritesheet;
	TexturedQuad* tex;
	Texture* hud;
	glm::ivec2 tileMapDispl;
};

#endif // _MENU_INCLUDE
