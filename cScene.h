#pragma once
#include "cRectangle.h"
#include "cCircle.h"
#include "cFigure.h"
#include "blok.h"
#include <vector>

void resize_binding(int width, int height);
void idle_binding();
void display_binding();
void key_binding(unsigned char key, int x, int y);
//void mouse_binding(int button, int state, int x, int y);
void mouse_move_binding(int x, int y);
void timer_binding(int i);

class cScene {
	std::vector<cFigure*> figures;
	int active_id_;
	int points_;
	cRectangle* pilka_;
	cRectangle* paletka_;
public:
	cScene();
	~cScene();
	void resize(int width, int height);
	void timer();
	void idle();
	void display();
	void init(int argc, char **argv, const char* window_name);
	void set_callbacks();
	void key(unsigned char key, int x, int y);
	//void mouse(int button, int state, int x, int y);
	void mouse_move(int x, int y);
};