#include "stripe.h"
#include <fstream>

stripe::stripe()
{
	setOrigin(origin);
}

stripe::~stripe()
{
}

void stripe::setTLCornerRadius(float radius) {
	if (this->size.x <= radius + this->trCorner.getRadius() && this->size.y <= radius + this->blCorner.getRadius()) {
		this->tlCorner.setRadius(radius);
		bodyAdjust();
		cornerAdjust();
	}
	else {
		throw - 5;
	}
}

void stripe::setTRCornerRadius(float radius) {
	if (this->size.x <= radius + this->tlCorner.getRadius() && this->size.y <= radius + this->brCorner.getRadius()) {
		this->trCorner.setRadius(radius);
		bodyAdjust();
		cornerAdjust();
	}
	else {
		throw - 5;
	}
}

void stripe::setBRCornerRadius(float radius) {
	if (this->size.x <= radius + this->blCorner.getRadius() && this->size.y <= radius + this->trCorner.getRadius()) {
		this->brCorner.setRadius(radius);
		bodyAdjust();
		cornerAdjust();
	}
	else {
		throw - 5;
	}
}

void stripe::setBLCornerRadius(float radius) {
	if (this->size.x <= radius + this->brCorner.getRadius() && this->size.y <= radius + this->tlCorner.getRadius()) {
		this->blCorner.setRadius(radius);
		bodyAdjust();
		cornerAdjust();
	}
	else {
		throw - 5;
	}
}

void stripe::setCornerRadius(float tl, float tr, float br, float bl) {
	if (size.x >= tl + tr && size.x >= bl + br && size.y >= tl + bl && size.y >= tr + br)
	{
		//logg << "[Debug]Corner Radius set!" << endl;
		this->tlCorner.setRadius(tl);
		this->trCorner.setRadius(tr);
		this->brCorner.setRadius(br);
		this->blCorner.setRadius(bl);
		bodyAdjust();
		cornerAdjust();
	}
	//else
	//	logg << "[Error]Corner radius unpropriate" << endl;
}

void stripe::setCornerRadius(float radius) {
	setCornerRadius(radius, radius, radius, radius);
}

void stripe::setSize(Vector2f size) {
	this->size = size;
	bodyAdjust();
	cornerAdjust();
}

void stripe::setPosition(Vector2f pos) {
	this->position = pos;
	bodyAdjust();
	cornerAdjust();
}

void stripe::bodyAdjust() {
	Vector2f &pos = this->position,
		&size = this->size;
	//Left body
	RectangleShape &L = this->bodyL;
	L.setSize(Vector2f(min(this->tlCorner.getRadius(), this->blCorner.getRadius()), size.y - this->tlCorner.getRadius() - this->blCorner.getRadius()));
	//L.setPosition(Vector2f(pos.x, pos.y + this->tlCorner.getRadius()));
	L.setPosition(pos);
	//Bottom body
	RectangleShape &B = this->bodyB;
	B.setSize(Vector2f(size.x - this->blCorner.getRadius() - this->brCorner.getRadius(), min(this->blCorner.getRadius(), this->brCorner.getRadius())));
	//B.setPosition(Vector2f(pos.x + this->blCorner.getRadius(), pos.y + size.y - B.getSize().y));
	B.setPosition(pos);
	//Right body
	RectangleShape &R = this->bodyR;
	R.setSize(Vector2f(min(this->trCorner.getRadius(), this->brCorner.getRadius()), size.y - this->trCorner.getRadius() - this->brCorner.getRadius()));
	//R.setPosition(Vector2f(pos.x + size.x - R.getSize().x, pos.x + this->trCorner.getRadius()));
	R.setPosition(pos);
	//Top body
	RectangleShape &T = this->bodyT;
	T.setSize(Vector2f(size.x - this->tlCorner.getRadius() - this->trCorner.getRadius(), min(this->tlCorner.getRadius(), this->trCorner.getRadius())));
	//T.setPosition(Vector2f(pos.x + this->tlCorner.getRadius(), pos.y));
	T.setPosition(pos);
	//Main body
	RectangleShape &M = this->bodyMain;
	M.setSize(Vector2f(size.x - this->bodyL.getSize().x - this->bodyR.getSize().x, size.y - this->bodyT.getSize().y - this->bodyB.getSize().y));
	M.setPosition(position);
}

void stripe::cornerAdjust() {
	this->tlCorner.setPosition(position);
	this->trCorner.setPosition(position);
	this->brCorner.setPosition(position);
	this->blCorner.setPosition(position);
}

void stripe::setFillColor(Color color) {
	this->bodyMain.setFillColor(color);
	this->bodyT.setFillColor(color);
	this->bodyB.setFillColor(color);
	this->bodyL.setFillColor(color);
	this->bodyR.setFillColor(color);
	this->tlCorner.setFillColor(color);
	this->trCorner.setFillColor(color);
	this->brCorner.setFillColor(color);
	this->blCorner.setFillColor(color);
}

void stripe::setOrigin(Vector2f origin) {
	this->origin = origin;
	tlCorner.setOrigin(Vector2f(0, 0) + origin);
	bodyT.setOrigin(Vector2f(-tlCorner.getRadius(), 0) + origin);
	trCorner.setOrigin(Vector2f(2 * trCorner.getRadius() - size.x, 0) + origin);
	bodyR.setOrigin(Vector2f(bodyR.getSize().x - size.x, -trCorner.getRadius()) + origin);
	brCorner.setOrigin(Vector2f(2 * brCorner.getRadius() - size.x, 2 * brCorner.getRadius() - size.y) + origin);
	bodyB.setOrigin(Vector2f(-blCorner.getRadius(), bodyB.getSize().y - size.y) + origin);
	blCorner.setOrigin(Vector2f(0, 2 * blCorner.getRadius() - size.y) + origin);
	bodyL.setOrigin(Vector2f(0, -tlCorner.getRadius()) + origin);
	bodyMain.setOrigin(Vector2f(-bodyL.getSize().x, -bodyT.getSize().y));
}

void stripe::draw(RenderWindow &wndPtr) {
	bodyAdjust();
	cornerAdjust();
	setOrigin(origin);
	//	logg << "[Debug]Overhaul size = " << size.x << ';' << size.y << endl;
	wndPtr.draw(bodyMain);
	//	logg << "[Debug]bodyMain.size = " << bodyMain.getSize().x << ';' << bodyMain.getSize().y << endl;
	wndPtr.draw(bodyT);
	//	logg << "[Debug]bodyT.size =" << bodyT.getSize().x << ';' << bodyT.getSize().y << endl;
	wndPtr.draw(bodyB);
	//	logg << "[Debug]bodyB.size =" << bodyB.getSize().x << ';' << bodyB.getSize().y << endl;
	wndPtr.draw(bodyL);
	//logg << "[Debug]bodyL.size =" << bodyL.getSize().x << ';' << bodyL.getSize().y << endl
	//	<< "[Debug]bodyL.position = " << bodyL.getPosition().x << ';' << bodyL.getPosition().y << endl
	//	<< "[Debug]bodyL.origin = " << bodyL.getOrigin().x << ';' << bodyL.getOrigin().y << endl;
	wndPtr.draw(bodyR);
	//	logg << "[Debug]bodyR.size =" << bodyR.getSize().x << ';' << bodyR.getSize().y << endl;
	wndPtr.draw(tlCorner);
	//	logg << "[Debug]tlCorner.size =" << tlCorner.getRadius() << endl;
	wndPtr.draw(trCorner);
	//	logg << "[Debug]trCorner.size =" << trCorner.getRadius() << endl;
	wndPtr.draw(brCorner);
	//	logg << "[Debug]brCorner.size =" << brCorner.getRadius() << endl;
	wndPtr.draw(blCorner);
	//	logg << "[Debug]blCorner.size =" << blCorner.getRadius() << endl;
}

void stripe::rotate(float angle) {
	this->angle = angle;
	bodyMain.rotate(angle);
	tlCorner.rotate(angle);
	bodyT.rotate(angle);
	trCorner.rotate(angle);
	bodyR.rotate(angle);
	brCorner.rotate(angle);
	bodyB.rotate(angle);
	blCorner.rotate(angle);
	bodyL.rotate(angle);
}