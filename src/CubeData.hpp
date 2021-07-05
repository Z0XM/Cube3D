#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.hpp"
#include "Vector.hpp"
#include <vector>
#include <deque>
#include <unordered_map>

struct Cube {
	enum Face {
		FRONT, UP, RIGHT, DOWN, LEFT, BACK
	};
	float dWidth;

	std::deque<Triangle> mesh;

	std::unordered_map<char, sf::Color> colorMap;
	std::vector<std::string> cubeColors;

	Cube();
	~Cube();

	void update();
	void loadFromFile(const std::string& filename);
	void setup(std::vector<std::string>& cc, float dw);

	void f(int x);
	void u(int x);
	void r(int x);
	void d(int x);
	void l(int x);
	void b(int x);
};