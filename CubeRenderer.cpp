#include "CubeRenderer.hpp"
#include <algorithm>

void CubeRenderer::InitWindow()
{
	window.create(sf::VideoMode(1200, 700), "Cube 3D");
	window.setFramerateLimit(60);
}

CubeRenderer::CubeRenderer()
{
	this->InitWindow();

	float aspectRatio = this->getWinSize().y / this->getWinSize().x;
	matProj = Matrix4x4::Projection(-0.1, -100.0f, 45.0f, aspectRatio);
	matOrtho = Matrix4x4::Orthographic(-10, 10, 10 * aspectRatio, -10 * aspectRatio, -0.1f, -100.0f);

	cube.f(1);
	cube.u(1);


	running = true;
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
		trianglesToRaster.clear();

		Matrix4x4 matWorld = 
			Matrix4x4::RotationY(45) * 
			Matrix4x4::RotationX(30) * 
			Matrix4x4::Translation(0, 0, -20.f);

		for (int e = 0; e < cube.elements.size(); e++)
		{
			for (int k = 0; k < cube.elements[e]->tri.size(); k++) {

				Triangle tri = *cube.elements[e]->tri[k];
				Triangle triTransformed = matWorld * tri;

				Vector normal = unit(cross(triTransformed[1] - triTransformed[0], triTransformed[2] - triTransformed[0]));

				if (dot(normal, triTransformed[0]) < 0.0f) {
					Triangle triProjected = matProj * triTransformed;

					triProjected[0] = triProjected[0] / triProjected[0].w;
					triProjected[1] = triProjected[1] / triProjected[1].w;
					triProjected[2] = triProjected[2] / triProjected[2].w;

					Vector offset{ 1, 1, 0 };
					triProjected[0].y *= -1; triProjected[1].y *= -1; triProjected[2].y *= -1;
					triProjected[0] = triProjected[0] + offset;
					triProjected[1] = triProjected[1] + offset;
					triProjected[2] = triProjected[2] + offset;
					triProjected[0].x *= 0.5f * this->getWinSize().x; triProjected[0].y *= 0.5f * this->getWinSize().y;
					triProjected[1].x *= 0.5f * this->getWinSize().x; triProjected[1].y *= 0.5f * this->getWinSize().y;
					triProjected[2].x *= 0.5f * this->getWinSize().x; triProjected[2].y *= 0.5f * this->getWinSize().y;

					triProjected.color = sf::Color(tri.color.r, tri.color.g, tri.color.b);

					trianglesToRaster.push_back(triProjected);
				}
			}

			sort(trianglesToRaster.begin(), trianglesToRaster.end(), [](Triangle& a, Triangle& b) {
				return (a[0].z + a[1].z + a[2].z) / 3.0f < (b[0].z + b[1].z + b[2].z) / 3.0f;
				});
		}
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
				if (event.type >= sf::Keyboard::Numpad1 && event.type <= sf::Keyboard::Numpad3) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::U));
				}
			}
		}
	}
}

void CubeRenderer::render()
{
	this->window.clear();

	for (auto& tri : trianglesToRaster) {
		sf::Vertex faces[3] = {
			{{tri[0].x, tri[0].y}, tri.color },
			{{tri[1].x, tri[1].y}, tri.color},
			{{tri[2].x, tri[2].y}, tri.color}
		};
		sf::Vertex lines[4] = {
			{{tri[0].x, tri[0].y}, sf::Color::Black },
			{{tri[1].x, tri[1].y}, sf::Color::Black},
			{{tri[2].x, tri[2].y}, sf::Color::Black},
			{{tri[0].x, tri[0].y}, sf::Color::Black }
		};
		window.draw(faces, 3, sf::Triangles);
		window.draw(lines, 4, sf::LinesStrip);
	}

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