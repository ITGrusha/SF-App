#include <SFML/Graphics.hpp>
#include "stripe.h"
#include "hamburger.h"
#include <fstream>

using namespace sf;
using namespace std;
float angle = 1;

//ofstream logg("log.txt", ofstream::out);

int main() {
	ContextSettings settings;
	settings.antialiasingLevel = 64;

	RenderWindow window(VideoMode(200, 200), "This is spinner!", 7U, settings);
	window.setFramerateLimit(60);
	window.setMouseCursorGrabbed(true);

	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);
	shape.setPointCount(64);

	RectangleShape rect(Vector2f(100.f, 100.f));
	rect.setFillColor(Color::Red);
	rect.setOrigin(Vector2f(50.f, 50.f));
	rect.setPosition(Vector2f(100.f, 100.f));

	Text txt;
	Font font;
	font.loadFromFile("font.ttf");
	txt.setString("Hello!\nTo exit press Esc");
	txt.setFont(font);
	txt.setCharacterSize(20);
	txt.setFillColor(Color::Black);
	txt.setOrigin(Vector2f(0.f, 0.f));
	txt.setPosition(Vector2f(0.f, 0.f));

	Text txtVel;
	txtVel.setFont(font);
	txtVel.setCharacterSize(16);
	txtVel.setFillColor(Color::Magenta);

	/*stripe test;
	test.setSize(Vector2f(40.f, 4.f));
	test.setOrigin(Vector2f(0.f, 0.f));
	test.setPosition(Vector2f(10.f, 10.f));
	test.setCornerRadius(2.f);
	test.setFillColor(Color::White);*/
	hamburger test;
	test.setSize(Vector2f(50.f, 50.f));
	test.setPadding(Vector2f(8.f, 12.f));
	test.setBGColor(Color::Blue);
	test.setBtnColor(Color::White);
	test.setPosition(Vector2f(10.f, 10.f));
	test.setOrigin(Vector2f(0.f, 0.f));
	test.setSpacing(6.f);

	float av = 0.f;
	int frame = 0;
	while (window.isOpen()) {
		frame = frame == 60 ? 0 : ++frame;
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
				window.close();
			}
			if (event.type == Event::MouseButtonPressed) {
				if (rect.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
					if (event.mouseButton.button == Mouse::Button::Left)
						angle -= 0.5f;
					else if (event.mouseButton.button == Mouse::Button::Right)
						angle += 0.5f;
			}
		}

		rect.rotate(angle);
		if (angle != 0)
			angle += (angle < 0.f ? 1 : -1) * 0.00005f * angle * angle;
		if (0.0001f < abs(angle))
			angle += (angle < 0.f ? 1 : -1) * 0.005f;
		if (abs(angle) <= 0.01f)
			angle = 0.f;
		//sleep(microseconds((int)(1000000 / 60)));

		av += angle;
		if ((frame + 1) % 5 == 0) {
			av /= 5;
			txtVel.setString(std::to_string(av * 60) + "deg/sec");
			txtVel.setOrigin(Vector2f(txtVel.getLocalBounds().width, txtVel.getLocalBounds().height));
			txtVel.setPosition(Vector2f(window.getSize().x, window.getSize().y));
			av = 0;
		}

		window.clear(Color(64,64,64,255));
		window.draw(shape);
		//window.draw(txt);
		window.draw(rect);
		window.draw(txtVel);
		test.draw(window);
		window.display();
	}
	//logg.close();
	return 0;
}