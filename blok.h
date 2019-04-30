#pragma once

#include <GL/freeglut.h>
#include "cRectangle.h"

class cBlok : public cRectangle {
	int zycia;
public:
	cBlok(double a, double b, double x, double y);
};

