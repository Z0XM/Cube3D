#pragma once
#include <SFML/Graphics.hpp>
#include "src/Utility.hpp"
#include "src/CubeData.hpp"

class CubeRenderer {
private:
	sf::RenderWindow window;
	bool running;
	bool paused;
	float aspectRatio;
	bool methodOfProjection; // 0 - Perspective, 1 - Orthographic
	bool insideOut;

	std::vector<Triangle> trianglesToRaster;
	
	Cube cube;
	
	Matrix4x4 matProj, matOrtho, matWorld;

	void InitWindow();
	void loadFromFile(const std::string& filename);
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
