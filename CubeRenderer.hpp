#pragma once
#include <SFML/Graphics.hpp>
#include "src/Utility.hpp"
#include "src/CubeData.hpp"

class CubeRenderer {
private:
	sf::RenderWindow window;
	bool running;
	bool paused;

	sf::Font mainFont, subFont;
	
	Cube cube;

	void initWindow();
	void initButtons();
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
