#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.hpp"
#include "Vector.hpp"
#include <vector>
#include <deque>

struct Cube {
	enum Face {
		FRONT, UP, RIGHT, DOWN, LEFT, BACK
	};

	std::deque<Triangle> mesh;

	std::vector<std::vector<Triangle*>> elements;
	std::vector<std::vector<Triangle*>> faces[6];

	Cube();
	~Cube();

	void f(int x);
	void u(int x);
	void r(int x);
	void d(int x);
	void l(int x);
	void b(int x);
};