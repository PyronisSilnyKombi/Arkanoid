#pragma once
#include <GL/freeglut.h>
#include"cFigure.h"

class cRectangle : public cFigure {
	double a_, b_;
	double angle_;
public:
	cRectangle(double a, double b, double x, double y, double v_x, double v_y, double angle);
	void draw();
	void update();
	void extend(const double& val);
	void reduce(const double& val);
	bool isClicked(double openglX, double openglY);
	bool isUnclicked(double openglX, double openglY);
};