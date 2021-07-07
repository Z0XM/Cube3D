#include "CubeRenderer.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

void CubeRenderer::InitWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	window.create(sf::VideoMode(1200, 700), "Cube 3D", sf::Style::Default, settings);
	window.setFramerateLimit(60);
}

CubeRenderer::CubeRenderer()
{
	this->InitWindow();

	this->cube.create(this->getWinSize());

	running = true;
	paused = false;
}

CubeRenderer::~CubeRenderer()
{
	
}

bool CubeRenderer::isRunning()
{
	return this->running;
}

void CubeRenderer::update()
{
	this->pollEvents();

	if (!this->paused) {
		cube.update();
	}
}

void CubeRenderer::pollEvents()
{
	sf::Event event;
	sf::Vector2f mousePos = this->getMousePosition();
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->running = false;

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)this->paused = !this->paused;

		if (!this->paused) {
			if (event.type == sf::Event::MouseButtonPressed) {

			}
			else if (event.type == sf::Event::MouseButtonReleased) {

			}
			else if (event.type == sf::Event::KeyPressed) {
				cube.handleKeyEvent(event.key.code);
			}
		}
	}
}

void CubeRenderer::render()
{
	this->window.clear();

	this->cube.render(window);

	this->window.display();
}

sf::Vector2f CubeRenderer::getMousePosition()
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

sf::Vector2f CubeRenderer::getWinSize()
{
	return sf::Vector2f(this->window.getSize());
}