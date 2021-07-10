#include "CubeData.hpp"
#include<fstream>
#include<sstream>

Cube::Cube()
{
	insideOut = false;

	cubeColors = {
		"ooooooooo",
		"yyyyyyyyy",
		"bbbbbbbbb",
		"wwwwwwwww",
		"ggggggggg",
		"rrrrrrrrr"
	};		

	following_moves = false;
}

Cube::~Cube()
{
}

void Cube::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;

	while (!file.eof()) {
		getline(file, line);
		std::stringstream ss;
		ss << line;
		ss >> line;
		if (line == "#scramble") {
			for (int i = 0; i < 6; i++) {
				getline(file, line);
				cubeColors[i] = line;
			}
		}
		else if (line == "#solve") {
			std::string move;
			while (move != "#end") {
				file >> move;
				moves.push(move);
			}
		}
	}
	file.close();
}

void Cube::initWorldMatrix(const sf::Vector3f& angles) 
{
	matWorld =
		Matrix4x4::RotationZ(angles.z) *
		Matrix4x4::RotationY(angles.y) *
		Matrix4x4::RotationX(angles.x) *
		Matrix4x4::Translation(0, 0, -20);
}

void Cube::create(float aspectRatio)
{
	viewAngles = { 30,45,0 };

	initWorldMatrix(viewAngles);

	matProj = Matrix4x4::Projection(-0.1, -100, 45, aspectRatio);

	insideOut = 0;

	setupCubeFromColors();
}

void Cube::setupCubeFromColors()
{
	mesh.clear();

	std::vector<Vector> v =
	{
		{-3, 3, 3}, {-1, 3, 3}, {1, 3, 3}, {3, 3, 3}, //  0  1  2  3 //t 0 2 3, 0 3 1 
		{-3, 1, 3}, {-1, 1, 3}, {1, 1, 3}, {3, 1, 3}, //  4  5  6  7
		{-3,-1, 3}, {-1,-1, 3}, {1,-1, 3}, {3,-1, 3}, //  8  9 10 11
		{-3,-3, 3}, {-1,-3, 3}, {1,-3, 3}, {3,-3, 3}, // 12 13 14 15

		{-3, 3, 1}, {-1, 3, 1}, {1, 3, 1}, {3, 3, 1}, // 16 17 18 19
		{-3, 1, 1},                        {3, 1, 1}, // 20       21
		{-3,-1, 1},                        {3,-1, 1}, // 22       23
		{-3,-3, 1}, {-1,-3, 1}, {1,-3, 1}, {3,-3, 1}, // 24 25 26 27

		{-3, 3,-1}, {-1, 3,-1}, {1, 3,-1}, {3, 3,-1}, // 28 29 30 31
		{-3, 1,-1},                        {3, 1,-1}, // 32       33
		{-3,-1,-1},                        {3,-1,-1}, // 34       35
		{-3,-3,-1}, {-1,-3,-1}, {1,-3,-1}, {3,-3,-1}, // 36 37 38 39

		{-3, 3,-3}, {-1, 3,-3}, {1, 3,-3}, {3, 3,-3}, // 40 41 42 43
		{-3, 1,-3}, {-1, 1,-3}, {1, 1,-3}, {3, 1,-3}, // 44 45 46 47
		{-3,-1,-3}, {-1,-1,-3}, {1,-1,-3}, {3,-1,-3}, // 48 49 50 51
		{-3,-3,-3}, {-1,-3,-3}, {1,-3,-3}, {3,-3,-3}, // 52 53 54 55
	};

	int s[6][9][4] =
	{
		{{ 0, 1, 4, 5}, { 1, 2, 5, 6}, { 2, 3, 6, 7}, { 4, 5, 8, 9}, { 5, 6, 9,10}, { 6, 7,10,11}, { 8, 9,12,13}, { 9,10,13,14}, {10,11,14,15}}, //front
		{{40,41,28,29}, {41,42,29,30}, {42,43,30,31}, {28,29,16,17}, {29,30,17,18}, {30,31,18,19}, {16,17, 0, 1}, {17,18, 1, 2}, {18,19, 2, 3}}, //up
		{{ 3,19, 7,21}, {19,31,21,33}, {31,43,33,47}, { 7,21,11,23}, {21,33,23,35}, {33,47,35,51}, {11,23,15,27}, {23,35,27,39}, {35,51,39,55}}, //right
		{{12,13,24,25}, {13,14,25,26}, {14,15,26,27}, {24,25,36,37}, {25,26,37,38}, {26,27,38,39}, {36,37,52,53}, {37,38,53,54}, {38,39,54,55}}, //down
		{{40,28,44,32}, {28,16,32,20}, {16, 0,20, 4}, {44,32,48,34}, {32,20,34,22}, {20, 4,22, 8}, {48,34,52,36}, {34,22,36,24}, {22, 8,24,12}}, //left
		{{43,42,47,46}, {42,41,46,45}, {41,40,45,44}, {47,46,51,50}, {46,45,50,49}, {45,44,49,48}, {51,50,55,54}, {50,49,54,53}, {49,48,53,52}}  //back
	};

	colorMap = {
		{'r', sf::Color::Red}, {'b', sf::Color::Blue}, {'g', sf::Color::Green}, {'w', sf::Color::White}, {'y', sf::Color::Yellow}, {'o', sf::Color(255,165,0)}
	};

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			Vector p[4] = { v[s[i][j][0]], v[s[i][j][2]], v[s[i][j][3]], v[s[i][j][1]] };
			mesh.push_back({ p[0], p[1], p[2], p[3], colorMap[cubeColors[i][j]] });
		}
	}
}

void Cube::loadColorsInCube()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			mesh[i * 9 + j].color = colorMap[cubeColors[i][j]];
		}
	}
}

void Cube::rotateFaceClockwise(int face, int n = 1)
{
	std::string temp(cubeColors[face]);
	auto k = [](int i) {return i / 3 + 6 - (i % 3) * 3; };

	for (int i = 0; i < 9; i++) {
		int j = i;
		switch (n) {
		case 3:j = k(j); case 2: j = k(j); case 1: j = k(j); 
		}
		cubeColors[face][i] = temp[j];
	}
}

void Cube::rotateSidesClockwise(std::vector<int>& v, int n)
{
	std::string temp;

	for (int i = 0; i < 12; i++) {
		temp.push_back(cubeColors[v[i] / 10][v[i] % 10]);
	}

	for (int i = 0; i < 12; i++) {
		cubeColors[v[i] / 10][v[i] % 10] = temp[(i + 12 - 3 * n) % 12];
	}
}

void Cube::setupForRotation(int face, std::vector<int>& v, int n, int dir, int axis)
{
	n = n % 4;

	if (face != -1) {
		for (int i = 0; i < 9; i++)
			rectanglesToRotateIndices.push_back(face * 10 + i);
		
		rotateFaceClockwise(face, n % 4);
	}

	rotateSidesClockwise(v, n % 4);
	rectanglesToRotateIndices.insert(rectanglesToRotateIndices.end(), v.begin(), v.end());

	rotationSettings.dir = dir;
	if (n == 3) {
		rotationSettings.dir *= -1;
		n = 1;
	}

	rotationSettings.setup(5, 90 * n * rotationSettings.dir);

	switch (axis) {
	case 0: rotationSettings.var = &rotationSettings.angles.x; break;
	case 1: rotationSettings.var = &rotationSettings.angles.y; break;
	case 2: rotationSettings.var = &rotationSettings.angles.z; break;
	}

	rotationSettings.work = [this]() {
		sf::Vector3f pre = rotationSettings.angles;

		rotationSettings.instant();

		Matrix4x4 rotMat =
			Matrix4x4::RotationX(rotationSettings.angles.x - pre.x) *
			Matrix4x4::RotationY(rotationSettings.angles.y - pre.y) *
			Matrix4x4::RotationZ(rotationSettings.angles.z - pre.z);

		for (auto i : rectanglesToRotateIndices) {
			i = (i / 10) * 9 + i % 10;
			sf::Color c = mesh[i].color;
			mesh[i] = rotMat * mesh[i];
			mesh[i].color = c;
		}
	};

	rotationSettings.finish = [this]() {
		Matrix4x4 rotMat =
			Matrix4x4::RotationX(-rotationSettings.angles.x) *
			Matrix4x4::RotationY(-rotationSettings.angles.y) *
			Matrix4x4::RotationZ(-rotationSettings.angles.z);
		
		for (auto i : rectanglesToRotateIndices) {
			i = (i / 10) * 9 + i % 10;
			sf::Color c = mesh[i].color;
			mesh[i] = rotMat * mesh[i];
			mesh[i].color = c;
		}

		loadColorsInCube();
		rectanglesToRotateIndices.clear();
	};
}

void Cube::f(int n)
{
	std::vector<int> v = {
		16, 17, 18,
		20, 23, 26,
		32, 31, 30,
		48, 45, 42
	};

	setupForRotation(FRONT, v, n, -1, 2);
}

void Cube::u(int n)
{
	std::vector<int> v = {
		22, 21, 20,
		 2,  1,  0,
		42, 41, 40,
		52, 51, 50
	};

	setupForRotation(UP, v, n, 1, 1);
}

void Cube::r(int n)
{
	std::vector<int> v = {
		38, 35, 32,
		 8,  5,  2,
		18, 15, 12,
		50, 53, 56
	};

	setupForRotation(RIGHT, v, n, -1, 0);
}

void Cube::d(int n)
{
	std::vector<int> v = {
		26, 27, 28,
		56, 57, 58,
		46, 47, 48,
		 6,  7,  8
	};

	setupForRotation(DOWN, v, n, -1, 1);
}

void Cube::l(int n)
{
	std::vector<int> v = {
		10, 13, 16,
		 0,  3,  6,
		30, 33, 36,
		58, 55, 52
	};

	setupForRotation(LEFT, v, n, 1, 0);
}

void Cube::b(int n)
{
	std::vector<int> v = {
		36, 37, 38,
		28, 25, 22,
		12, 11, 10,
		40, 43, 46
	};

	setupForRotation(BACK, v, n, 1, 2);
}

void Cube::m(int n)
{
	std::vector<int> v = {
		 7,  4,  1,
		17, 14, 11,
		57, 54, 51,
		37, 34, 31
	};

	setupForRotation(-1, v, n, -1, 0);
}

void Cube::s(int n)
{
	std::vector<int> v = {
		 5,  4,  3,
		45, 44, 43,
		55, 54, 53,
		25, 24, 23
	};

	setupForRotation(-1, v, n, 1, 1);
}

void Cube::e(int n)
{
	std::vector<int> v = {
		21, 24, 27,
		35, 34, 33,
		47, 44, 41,
		13, 14, 15
	};

	setupForRotation(-1, v, n, -1, 2);
}

void Cube::turn_left()
{
	u(1); s(1); d(3);
}

void Cube::turn_right()
{
	u(3); s(3); d(1);
}

void Cube::turn_up()
{
	r(1); m(1); l(3);
}

void Cube::turn_down()
{
	r(3); m(3); l(1);
}

bool Cube::handleKeyEvent(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Q) {
		loadFromFile("data/scramble.txt");
		setupCubeFromColors();
		return true;
	}

	if (!viewSettings.animating && (key >= sf::Keyboard::Numpad4 && key <= sf::Keyboard::Numpad6)) {
		if (key == sf::Keyboard::Numpad4) viewSettings.dir = 1;
		else if (key == sf::Keyboard::Numpad6) viewSettings.dir = -1;
		float rval = 90;

		if (key == sf::Keyboard::Numpad5) {
			viewSettings.dir *= -1;
			rval = 45;
		}

		viewSettings.setup(5, viewAngles.y + rval * viewSettings.dir, &viewAngles.y);

		viewSettings.work = [this]() {
			viewSettings.instant();
			initWorldMatrix(viewAngles);
		};

		return true;
	}

	if (viewSettings.var != &viewAngles.y && (key == sf::Keyboard::Numpad8 || key == sf::Keyboard::Numpad2)){
		if (key == sf::Keyboard::Numpad2) viewSettings.dir = -1;
		else if (key == sf::Keyboard::Numpad8) viewSettings.dir = 1;

		viewSettings.setup(5, 30 * viewSettings.dir, &viewAngles.x);

		viewSettings.work = [this]() {
			viewSettings.instant();
			initWorldMatrix(viewAngles);
		};

		return true;
	}

	if (key == sf::Keyboard::Enter) {
		following_moves = !following_moves;
		return true;
	}
	if (key == sf::Keyboard::I) {
		insideOut = !insideOut;
		return true;
	}
	
	if (following_moves)return false;

	if (rotationSettings.animating)return false;

	int n = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))n = 3;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))n = 2;

	if (key == sf::Keyboard::R)r(n);
	else if (key == sf::Keyboard::U)u(n);
	else if (key == sf::Keyboard::F)f(n);
	else if (key == sf::Keyboard::L)l(n);
	else if (key == sf::Keyboard::D)d(n);
	else if (key == sf::Keyboard::B)b(n);
	else if (key == sf::Keyboard::M)m(n);
	else if (key == sf::Keyboard::S)s(n);
	else if (key == sf::Keyboard::E)e(n);
	else if (key == sf::Keyboard::Right)turn_right();
	else if (key == sf::Keyboard::Left)turn_left();
	else if (key == sf::Keyboard::Up)turn_up();
	else if (key == sf::Keyboard::Down)turn_down();
	else return false;
	return true;
}

void Cube::update()
{
	if (!rotationSettings.animating && following_moves && !moves.empty()) {
		std::string move = moves.front();
		moves.pop();

		int n = 1;
		if (move.size() == 2) {
			if (move[1] == '!')n = 3;
			else if (move[1] == '2')n = 2;
		}

		switch (move[0]) {
		case 'r': r(n); break;
		case 'f': f(n); break;
		case 'u': u(n); break;
		case 'l': l(n); break;
		case 'b': b(n); break;
		case 'd': d(n); break;
		case 's': s(n); break;
		case 'm': m(n); break;
		case 'e': e(n); break;
		}
	}

	if (rotationSettings.animating)rotationSettings.animate();

	if (viewSettings.animating)viewSettings.animate();
}

void Cube::render(sf::RenderWindow& window)
{
	std::vector<Rectangle> rectanglesToRaster;

	for (auto& rect : mesh)
	{
		Rectangle rectTransformed = matWorld * rect;

		Vector normal = unit(cross(rectTransformed[1] - rectTransformed[0], rectTransformed[2] - rectTransformed[0]));

		if ((insideOut ? -1 : 1) * dot(normal, rectTransformed[0]) < 0.0f) {
			Rectangle rectProjected;

			rectProjected = matProj * rectTransformed;

			sf::Vector2f winSize(window.getSize().x, window.getSize().y);
			auto offsetPoint = [this, &winSize](Vector& p) {
				p = p / p.w;
				p.y *= -1;
				p = p + Vector{ 0.5, 1, 0 };
				p.x *= 0.5f * winSize.x;
				p.y *= 0.5f * winSize.y;
			};

			for(int j = 0; j < 4; j++)
				offsetPoint(rectProjected[j]);

			rectProjected.color = sf::Color(rect.color.r, rect.color.g, rect.color.b);

			rectanglesToRaster.push_back(rectProjected);
		}
	}

	sort(rectanglesToRaster.begin(), rectanglesToRaster.end(), [](Rectangle& a, Rectangle& b) {
		return (a[0].z + a[1].z + a[2].z + a[3].z) / 4.0f < (b[0].z + b[1].z + b[2].z + b[3].z) / 4.0f;
		});


	sf::ConvexShape shape;
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(-2);
	shape.setPointCount(4);

	for (auto& rect : rectanglesToRaster) {
		shape.setFillColor(rect.color);
		shape.setPoint(0, { rect[0].x, rect[0].y });
		shape.setPoint(1, { rect[1].x, rect[1].y });
		shape.setPoint(2, { rect[2].x, rect[2].y });
		shape.setPoint(3, { rect[3].x, rect[3].y });
		window.draw(shape);
	}
}