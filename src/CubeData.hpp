#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.hpp"
#include "Vector.hpp"
#include "CubeAnimation.hpp"
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>

class Cube {
	bool insideOut;
	bool filling_colors;
	int rotationSpeed;
	char currentColor;

	Matrix4x4 matProj, matWorld;
	std::vector<Quad> mesh;
	std::vector<int> rectanglesToRotateIndices;

	std::unordered_map<char, sf::Color> colorMap;
	std::vector<std::string> cubeColors;
	
	sf::Vector3f viewAngles;
	CubeAnimation rotationSettings, viewSettings;

	bool following_moves;
	std::queue<std::string> moves;

	void initWorldMatrix(const sf::Vector3f& angles);
	void setupCubeFromColors();
	void loadColorsInCube();
	void setupForRotation(int face, std::vector<int>& v, int n, int dir, int axis);
	void rotateFaceClockwise(int face, int n);
	void rotateSidesClockwise(std::vector<int>& v, int n);
public:
	enum Face {
		FRONT, UP, RIGHT, DOWN, LEFT, BACK
	};

	Cube(float aspectRatio);
	~Cube();

	void setButtons();
	void create();
	void loadFromFile(const std::string& filename);
	void saveToFile(const std::string& filename);

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