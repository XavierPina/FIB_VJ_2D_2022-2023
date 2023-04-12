#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include "Hud.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	void setMenuBool(bool m, bool win); 
	bool getSpecialKey(int key) const;

private:
	bool bPlay; // Continue to play game?;
	Scene* scene;
	Menu* menuScreen;
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	bool menuUP;
	

};


#endif // _GAME_INCLUDE


