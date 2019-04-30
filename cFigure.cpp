#include "cFigure.h"

cFigure::cFigure(double x, double y, double v_x, double v_y) :cFizyka()
{
	x_ = x;
	y_ = y;
	v_x_ = v_x;
	v_y_ = v_y;
	rgb_[0] = 1.0;
	rgb_[1] = 0.0;
	rgb_[2] = 0.0;
}

void cFigure::move(double dx, double dy) {
	x_ += dx;
	y_ += dy;
}

void cFigure::rotate_clockwise() {
	glPushMatrix();
	glRotated(-10, 0.0, 0.0, 1.0);
	glPopMatrix();
}

void cFigure::speed_up_x(const float& val) {
	if (v_x_ < 0)
		v_x_ -= val;
	else
		v_x_ += val;
}

void cFigure::speed_up_y(const float& val) {
	if (v_y_ < 0)
		v_y_ -= val;
	else
		v_y_ += val;
}

void cFigure::slow_down_x(const float& val) {
	if (v_x_ > 0.001||v_x_<0.001) {
		if (v_x_ > 0)v_x_ -= val;
		if (v_x_ < 0)v_x_ += val;
	}
}

void cFigure::slow_down_y(const float& val) {
	if (v_y_ > 0.001 || v_y_ < 0.001) {
		if (v_y_ > 0)v_y_ -= val;
		if (v_y_ < 0)v_y_ += val;
	}
}

void cFigure::follow(double x, double y) {
	x_ = x;
	/*y_ = y;*/
}

void cFigure::set_color(double r, double g, double b) {
	rgb_[0] = r;
	rgb_[1] = g;
	rgb_[2] = b;
}
