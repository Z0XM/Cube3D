#pragma once
#include <SFML/Graphics.hpp>
#include "src/Utility.hpp"
#include "src/CubeData.hpp"

class CubeRenderer {
private:
	sf::RenderWindow window;
	bool running;
	bool paused;

	std::vector<Triangle> trianglesToRaster;
	
	Cube cube;
	
	Matrix4x4 matProj, matOrtho;

	void InitWindow();
public:
	CubeRenderer();
	~CubeRenderer();

	bool isRunning();

	void update();
	void pollEvents();
	void render();

	sf::Vector2f getMousePosition();
	sf::Vector2f getWinSize();
};
