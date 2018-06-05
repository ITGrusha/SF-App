#include "hamburger.h"

int frameCnt = 0;

hamburger::hamburger()
{
	setOrigin(Vector2f(0.f, 0.f));
}


hamburger::~hamburger()
{
}

void hamburger::setPosition(Vector2f position) {
	bg.setPosition(position);
	lineTop.setPosition(position);
	lineMid.setPosition(position);
	lineBot.setPosition(position);
}

void hamburger::setSpacing(float spacing) {
	if (spacing * 4.f <= size.x)
	{
		this->spacing = spacing;
		setSize(size);
		setOrigin(origin);
	}
}

void hamburger::setPadding(Vector2f padding) {
	this->padding = padding;
	setSize(size);
	setOrigin(origin);
}

void hamburger::setOrigin(Vector2f origin) {
	bg.setOrigin(origin);
	lineTop.setOrigin(-padding);
	lineMid.setOrigin(Vector2f(-padding.x, -padding.y - spacing - lineSize.y));
	lineBot.setOrigin(Vector2f(-padding.x, -padding.y - 2 * spacing - 2 * lineSize.y));
}

void hamburger::setSize(Vector2f size) {
	this->size = size;
	bg.setSize(size);
	setLineSize(Vector2f(size.x - 2 * padding.x, (size.y - 2 * (padding.y + spacing)) / 3));
	setOrigin(origin);
}

void hamburger::setLineSize(Vector2f size) {
	lineSize = size;
	lineTop.setSize(size);
	lineTop.setCornerRadius(size.y / 2.f);
	lineMid.setSize(size);
	lineMid.setCornerRadius(size.y / 2.f);
	lineBot.setSize(size);
	lineBot.setCornerRadius(size.y / 2.f);
}

void hamburger::setBGColor(Color color) {
	bg.setFillColor(color);
}

void hamburger::setBtnColor(Color color) {
	lineTop.setFillColor(color);
	lineMid.setFillColor(color);
	lineBot.setFillColor(color);
}

void hamburger::draw(RenderWindow& wndPtr) {
	if (state % 2 == 0) {
		if (state == 1) {
			animateToX(60);
		}
		else if (state == 3) {
			animateFromX(60);
		}
	}
	wndPtr.draw(bg);
	lineTop.draw(wndPtr);
	lineMid.draw(wndPtr);
	lineBot.draw(wndPtr);
}

void hamburger::animate() {

}