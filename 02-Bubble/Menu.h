#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "ShaderProgramManager.h"
#include <vector>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"


class Menu {
public:
	static Menu& instance()
	{
		static Menu M;

		return M;
	}

	Menu();
	~Menu();

	void init(ShaderProgram& shaderProgram);
	void render();
	void update(int deltaTime);
	void setPosIndex(int pos);

private:
	int id, index;
	bool pressed;
	Sprite* sprite;
	float currentTime;
	Texture spritesheet;
	TexturedQuad* bground;
	glm::mat4 projection;
	Sprite* box;
	Texture* screen;
	Texture* screen1;
	Texture* screen2;
	Texture* screen3;
	Texture* screen4;
	Texture* screen5;
};

#endif // _MENU_INCLUDE