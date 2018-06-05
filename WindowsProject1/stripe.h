#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;
using namespace std;

class stripe
{
public:
	stripe();
	~stripe();
	void draw(RenderWindow&);
	void setSize(Vector2f);
	void setPosition(Vector2f);
	void setOrigin(Vector2f);
	void setTLCornerRadius(float);
	void setBLCornerRadius(float);
	void setBRCornerRadius(float);
	void setTRCornerRadius(float);
	void setCornerRadius(float, float, float, float);
	void setCornerRadius(float);
	void setFillColor(Color);
	void rotate(float);
private:
	Vector2f size = Vector2f(40, 40),
		position = Vector2f(0, 0),
		origin = Vector2f(0, 0);
	float angle = 0.f;
	void bodyAdjust();
	void cornerAdjust();
	RectangleShape bodyL,
		bodyR,
		bodyT,
		bodyB,
		bodyMain;
	CircleShape tlCorner,
		blCorner,
		brCorner,
		trCorner;
};

