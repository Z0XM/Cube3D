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

void CubeRenderer::loadFromFile(const std::string& filename)
{
	using namespace std;

	ifstream file(filename);
	while (!file.eof())
	{
		string line;
		getline(file, line);

		stringstream ss;
		ss << line;

		string var;
		ss >> var;
		if (var == "matProj") {
			string subvar;
			float zNear = 0, zFar = 0, fov = 0;
		
			do {
				getline(file, line);
				stringstream sss;
				sss << line;
				sss >> subvar;
				if (subvar == "zNear")sss >> zNear;
				else if (subvar == "zFar")sss >> zFar;
				else if (subvar == "fov")sss >> fov;
			} while (subvar != ")");

			matProj = Matrix4x4::Projection(zNear, zFar, fov, aspectRatio);
		}

		else if (var == "matOrtho") {
			string subvar;
			float left = 0, right = 0, top = 0, bottom = 0, near = 0, far = 0;

			do {
				getline(file, line);
				stringstream sss;
				sss << line;
				sss >> subvar;
				if (subvar == "left")sss >> left;
				else if (subvar == "right")sss >> right;
				else if (subvar == "top")sss >> top;
				else if (subvar == "bottom")sss >> bottom;
				else if (subvar == "near")sss >> near;
				else if (subvar == "far")sss >> far;
			} while (subvar != ")");
			
			matOrtho = Matrix4x4::Orthographic(left, right, top * aspectRatio, bottom * aspectRatio, near, far);
		}

		else if (var == "matWorld") {
			string subvar;
			float rotationZ = 0, rotationY = 0, rotationX = 0;
			Vector translation;

			do {
				getline(file, line);
				stringstream sss;
				sss << line;
				sss >> subvar;
				if (subvar == "rotationZ")sss >> rotationZ;
				else if (subvar == "rotationY")sss >> rotationY;
				else if (subvar == "rotationX")sss >> rotationX;
				else if (subvar == "translation")sss >> translation.x >> translation.y >> translation.z;
			} while (subvar != ")");

			matWorld =
				Matrix4x4::RotationZ(rotationZ) * 
				Matrix4x4::RotationY(rotationY) *
				Matrix4x4::RotationX(rotationX) *
				Matrix4x4::Translation(translation.x, translation.y, translation.z);
		}
		else if (var == "methodOfProjection") {
			ss >> methodOfProjection;
		}
		else if (var == "insideOut") {
			ss >> insideOut;
		}
	}
}

CubeRenderer::CubeRenderer()
{
	this->InitWindow();

	aspectRatio = this->getWinSize().y / this->getWinSize().x;

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
		loadFromFile("data/settings.txt");

		trianglesToRaster.clear();
		
		for (auto& tri : cube.mesh)
		{
			Triangle triTransformed = matWorld * tri;

			Vector normal = unit(cross(triTransformed[1] - triTransformed[0], triTransformed[2] - triTransformed[0]));

			if ((insideOut?-1:1) * dot(normal, triTransformed[0]) < 0.0f) {
				Triangle triProjected;

				if(methodOfProjection == 0)triProjected = matProj * triTransformed;
				else if(methodOfProjection == 1)triProjected = matOrtho * triTransformed;

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
				if (event.key.code >= sf::Keyboard::Numpad1 && event.key.code <= sf::Keyboard::Numpad3) {
					int n = event.key.code - sf::Keyboard::Numpad0;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))cube.u(n);
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))cube.r(n);
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))cube.f(n);
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))cube.b(n);
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))cube.l(n);
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))cube.d(n);
					cube.update();
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
			{{tri[0].x, tri[0].y}, sf::Color::Black},
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
		//window.draw(lines, 4, sf::LinesStrip);
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