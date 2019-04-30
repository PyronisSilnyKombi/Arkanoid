#include "cRectangle.h"

cRectangle::cRectangle(double a=2, double b=2, double x=0, double y=0, double v_x = 0, double v_y = 0, double angle= 0) :cFigure(x, y, v_x, v_y), a_(a), b_(b), angle_(angle) {
	ustaw_geometria(x, y, -a / 2, -b / 2, a / 2, b / 2);
}

void cRectangle::draw() {
	glPushMatrix();

	glTranslated(x_, y_, 0.0);
	glRotated(angle_, 1.0, 0.0, 0.0);
	glRotated(angle_, 0.0, 1.0, 0.0);
	glRotated(angle_, 0.0, 0.0, 1.0);

	glColor3d(rgb_[0], rgb_[1], rgb_[2]);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, -b_ / 2, 0);
		glVertex3d(-a_ / 2, -b_ / 2, 0);
	}
	glEnd();
	glPopMatrix();
}

void cRectangle::update()
{
	if (x_ >= 10.0 - a_ / 2)
	{
		v_x_ = -v_x_;
		x_ = x_ + v_x_;
	}
	else if (x_ <= -10.0 + a_ / 2)
	{
		v_x_ = -v_x_;
		x_ = x_ + v_x_;
	}
	else
	{
		x_ = x_ + v_x_;
	}

	if (y_ >= 10.0 - b_ / 2)
	{
		v_y_ = -v_y_;
		y_ = y_ + v_y_;
	}
	else if (y_ <= -10.0 + b_ / 2)
	{
		v_y_ = -v_y_;
		y_ = y_ + v_y_;
	}
	else
	{
		y_ = y_ + v_y_;
	}
}

void cRectangle::extend(const double& val) {
	a_ += val;
	b_ += val;
}

void cRectangle::reduce(const double& val) {
	if (a_ > 1 && b_ > 1) {
		a_ -= val;
		b_ -= val;
	}
}

bool cRectangle::isClicked(double openglX, double openglY) {	
	if (openglX <( x_ + (a_ / 2)) && openglX > (x_ - (a_ / 2)) && openglY < (y_ + (b_ / 2)) && openglY > (y_ - (b_ / 2))) {
		rgb_[0] = 1.0;
		rgb_[1] = 0.0;
		return true;
	}
	return false;
}

bool cRectangle::isUnclicked(double openglX, double openglY) {
	if (openglX <(x_ + (a_ / 2)) && openglX >(x_ - (a_ / 2)) && openglY < (y_ + (b_ / 2)) && openglY >(y_ - (b_ / 2))) {
		rgb_[0] = 0.0;
		rgb_[1] = 1.0;
		return true;
	}
	return false;
}