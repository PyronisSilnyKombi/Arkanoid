#pragma once
#include <GL/freeglut.h>
#include "cFizyka.h"

class cFigure : public cFizyka {
protected:
	/*double x_, y_;*/
	double v_x_, v_y_;
	float rgb_[3];
public:
	cFigure(double x = 0.0, double y = 0.0, double v_x=0.0, double v_y = 0.0);
	virtual void draw() = 0;
	void move(double dx, double dy);
	void rotate_clockwise();
	virtual  void update() = 0;
	void speed_up_x(const float& val);
	void speed_up_y(const float& val);
	void slow_down_x(const float& val);
	void slow_down_y(const float& val);
	virtual bool isClicked(double openglX, double openglY) = 0;
	virtual bool isUnclicked(double openglX, double openglY) = 0;
	void follow (double dx, double dy);
	void set_color(double r, double g, double b);
};