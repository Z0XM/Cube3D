#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.hpp"
#include "Vector.hpp"
#include <vector>
#include <deque>
#include <unordered_map>

class Cube {
	sf::Vector2f winSize;
	bool insideOut;

	Matrix4x4 matProj, matWorld;
	std::vector<Rectangle> mesh;
	std::vector<int> rectanglesToRotateIndices;

	std::unordered_map<char, sf::Color> colorMap;
	std::vector<std::string> cubeColors;

	float rotation_value, rotation_target;
	bool animating;

	void setup();
public:
	enum Face {
		FRONT, UP, RIGHT, DOWN, LEFT, BACK
	};

	Cube();
	~Cube();

	void create(const sf::Vector2f&);

	void updateMoves();

	bool handleKeyEvent(sf::Keyboard::Key key);
	void update();
	void render(sf::RenderWindow& window);

	void f(int x);
	void u(int x);
	void r(int x);
	void d(int x);
	void l(int x);
	void b(int x);
	void m(int x);
	void s(int x);
	void e(int x);

	void turn_left();
	void turn_right();
	void turn_up();
	void turn_down();
};