#pragma once
#include <SFML/Graphics.hpp>
#include "stripe.h"

using namespace sf;

class hamburger
{
public:
	hamburger();
	~hamburger();
	void setPosition(Vector2f);
	void setOrigin(Vector2f);
	void setSize(Vector2f);
	void setBGColor(Color);
	void setBtnColor(Color);
	void setSpacing(float);
	void setPadding(Vector2f);
	void draw(RenderWindow&);
	void animateToX(int framerate);
	void animateToX(int framerate, float duration);
	void animateFromX(int framerate);
	void animateFromX(int framerate, float duration);
private:
	int state = 0;
	void setLineSize(Vector2f);
	stripe lineTop,
		lineMid,
		lineBot;
	RectangleShape bg;
	Vector2f position,
		origin,
		padding = Vector2f(10.f, 10.f),
		size,
		lineSize;
	float spacing = 8.0f;
	Color btnColor,
		bgColor;
};

