#pragma once
#include <SFML/Graphics.hpp>

#include <functional>
#include "Utility.hpp"

class CubeAnimation {
public:
	float speed, target;
	int dir;
	bool animating;
	
	sf::Vector3f angles;

	float* var;

	CubeAnimation();

	void setup(float speed, float target, float* var = nullptr);

	void reset();
	void instant();
	std::function<void()> work;
	std::function<void()> finish;
	bool isOver();

	void animate();
};
