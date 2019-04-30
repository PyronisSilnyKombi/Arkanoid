#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include"cFigure.h"

class cCircle : public cFigure {
	double r_;
public:
	cCircle(double r, double x, double y, double v_x, double v_y);
	void draw();
	void update();
	void extend(const double& val);
	void reduce(const double& val);
	bool isClicked(double openglX, double openglY);
	bool isUnclicked(double openglX, double openglY);
};