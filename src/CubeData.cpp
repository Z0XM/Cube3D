#include "CubeData.hpp"
#include<fstream>
#include<sstream>
#include<iostream>
#include "GUI.hpp"
#include "CubeAlgorithm.hpp"

Cube::Cube(float aspectRatio)
{
	matProj = Matrix4x4::Projection(-0.1, -100, 45, aspectRatio);

	filling_colors = false;

	colorMap = {
		{'r', sf::Color::Red}, {'b', sf::Color::Blue}, {'g', sf::Color::Green}, {'w', sf::Color::White}, {'y', sf::Color::Yellow}, {'o', sf::Color(255,165,0)}, {'x', sf::Color(126,126,126)}
	};
}

Cube::~Cube()
{
}

void Cube::setButtons()
{
	gui::Textbox::Group["CurMove"]->setString("");

	gui::Button::Group["Save"]->setAction([this]() {
		saveToFile("data/scramble.txt");
	});

	gui::Button::Group["Load"]->setAction([this]() {
		this->create();
		this->loadFromFile("data/scramble.txt"); 
		gui::Button::Group["Solve"]->setString("Solve"); 
	});
	gui::Button::Group["Solve"]->setAction([this]() {
		this->following_moves = !this->following_moves;
		std::string text = this->following_moves ? "Pause" : "Solve";
		gui::Button::Group["Solve"]->setString(text);
		if (moves.empty() && following_moves) {
			auto algo = generateAlgorithm(cubeColors);
			for (auto& s : algo) {
				std::cout << s << ' ';
				moves.push(s);
			}
			std::cout << std::endl << std::endl;
		}

		if(!following_moves)gui::Textbox::Group["CurMove"]->setString("");
	});

	gui::Button::Group["Reset"]->setAction([this]() {
		this->create();
		if (filling_colors)gui::Button::Group["Fill Colors"]->action();
		gui::Button::Group["Solve"]->setString("Solve");
	});

	gui::Button::Group["Inside Out"]->setAction([this]() {
		insideOut = !insideOut;
	});

	gui::Button::Group["Fill Colors"]->setAction([this]() {
		filling_colors = !filling_colors;

		if (this->following_moves) {
			gui::Button::Group["Solve"]->action();
		}

		if (filling_colors) {
			std::string cs = "xxxxxxxxx";
			for (int i = 0; i < 6; i++)cubeColors[i] = cs;

			viewAngles = { 30,45,0 };

			initWorldMatrix(viewAngles);

			insideOut = 0;

			rectanglesToRotateIndices.clear();

			setupCubeFromColors();

			gui::Button::Group["Solve"]->setString("Solve");

			currentColor = 'x';

			sf::Vector2f offset(0, gui::Button::Group["Fill Colors"]->getSize().y + 10);
			sf::Vector2f size(50, 50);
			sf::Color c = sf::Color::Red;
			gui::Button::Group["Red"] = gui::Button::create(size);
			gui::Button::Group["Red"]->setPosition(gui::Button::Group["Fill Colors"]->getPosition() + offset);
			gui::Button::Group["Red"]->setFillColor(c);
			gui::Button::Group["Red"]->setOutlineColor(sf::Color::Transparent);
			gui::Button::Group["Red"]->setHighlightFillColor(c);
			gui::Button::Group["Red"]->setHighightOutlineColor(c);
			gui::Button::Group["Red"]->setHighlightOutlineThickness(5);
			gui::Button::Group["Red"]->setAction([this]() {currentColor = 'r'; });

			offset.x += 55;
			c = sf::Color::Yellow;
			gui::Button::Group["Yellow"] = gui::Button::create(size);
			gui::Button::Group["Yellow"]->setPosition(gui::Button::Group["Fill Colors"]->getPosition() + offset);
			gui::Button::Group["Yellow"]->setFillColor(c);
			gui::Button::Group["Yellow"]->setOutlineColor(sf::Color::Transparent);
			gui::Button::Group["Yellow"]->setHighlightFillColor(c);
			gui::Button::Group["Yellow"]->setHighightOutlineColor(c);
			gui::Button::Group["Yellow"]->setHighlightOutlineThickness(5);
			gui::Button::Group["Yellow"]->setAction([this]() {currentColor = 'y'; });

			offset.x += 55;
			c = sf::Color::Green;
			gui::Button::Group["Green"] = gui::Button::create(size);
			gui::Button::Group["Green"]->setPosition(gui::Button::Group["Fill Colors"]->getPosition() + offset);
			gui::Button::Group["Green"]->setFillColor(c);
			gui::Button::Group["Green"]->setOutlineColor(sf::Color::Transparent);
			gui::Button::Group["Green"]->setHighlightFillColor(c);
			gui::Button::Group["Green"]->setHighightOutlineColor(c);
			gui::Button::Group["Green"]->setHighlightOutlineThickness(5);
			gui::Button::Group["Green"]->setAction([this]() {currentColor = 'g'; });

			offset.x += 55;
			c = sf::Color::White;
			gui::Button::Group["White"] = gui::Button::create(size);
			gui::Button::Group["White"]->setPosition(gui::Button::Group["Fill Colors"]->getPosition() + offset);
			gui::Button::Group["White"]->setFillColor(c);
			gui::Button::Group["White"]->setOutlineColor(sf::Color::Transparent);
			gui::Button::Group["White"]->setHighlightFillColor(c);
			gui::Button::Group["White"]->setHighightOutlineColor(c);
			gui::Button::Group["White"]->setHighlightOutlineThickness(5);
			gui::Button::Group["White"]->setAction([this]() {currentColor = 'w'; });

			offset.x += 55;
			c = sf::Color::Blue;
			gui::Button::Group["Blue"] = gui::Button::create(size);
			gui::Button::Group["Blue"]->setPosition(gui::Button::Group["Fill Colors"]->getPosition() + offset);
			gui::Button::Group["Blue"]->setFillColor(c);
			gui::Button::Group["Blue"]->setOutlineColor(sf::Color::Transparent);
			gui::Button::Group["Blue"]->setHighlightFillColor(c);
			gui::Button::Group["Blue"]->setHighightOutlineColor(c);
			gui::Button::Group["Blue"]->setHighlightOutlineThickness(5);
			gui::Button::Group["Blue"]->setAction([this]() {currentColor = 'b'; });

			offset.x += 55;
			c = colorMap['o'];
			gui::Button::Group["Orange"] = gui::Button::create(size);
			gui::Button::Group["Orange"]->setPosition(gui::Button::Group["Fill Colors"]->getPosition() + offset);
			gui::Button::Group["Orange"]->setFillColor(c);
			gui::Button::Group["Orange"]->setOutlineColor(sf::Color::Transparent);
			gui::Button::Group["Orange"]->setHighlightFillColor(c);
			gui::Button::Group["Orange"]->setHighightOutlineColor(c);
			gui::Button::Group["Orange"]->setHighlightOutlineThickness(5);
			gui::Button::Group["Orange"]->setAction([this]() {currentColor = 'o'; });
		}
		else {
			delete gui::Button::Group["Red"]; gui::Button::Group.erase("Red");
			delete gui::Button::Group["Yellow"]; gui::Button::Group.erase("Yellow");
			delete gui::Button::Group["Green"]; gui::Button::Group.erase("Green");
			delete gui::Button::Group["White"]; gui::Button::Group.erase("White");
			delete gui::Button::Group["Blue"]; gui::Button::Group.erase("Blue");
			delete gui::Button::Group["Orange"]; gui::Button::Group.erase("Orange");
		}
	});

	sf::Vector2f barSize = gui::Textbox::Group["Speed"]->getSize();
	gui::Textbox::Group["SpeedBar"]->setSize({ (logf(rotationSpeed) / logf(90)) * barSize.x, barSize.y });
	
	gui::Button::Group["SpeedI"]->setAction([this]() {
		do {
			if (rotationSpeed == 90)break;
			rotationSpeed += 1;
		} while (90 % rotationSpeed != 0);

		sf::Vector2f barSize = gui::Textbox::Group["Speed"]->getSize();
		gui::Textbox::Group["SpeedBar"]->setSize({ (logf(rotationSpeed) / logf(90)) * barSize.x, barSize.y });

		});
	gui::Button::Group["SpeedD"]->setAction([this]() {
		do {
			if (rotationSpeed == 1)break;
			rotationSpeed -= 1;
		} while (90 % rotationSpeed != 0);

		sf::Vector2f barSize = gui::Textbox::Group["Speed"]->getSize();
		gui::Textbox::Group["SpeedBar"]->setSize({ (logf(rotationSpeed) / logf(90)) * barSize.x, barSize.y });

		});
}

void Cube::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;

	for (int i = 0; i < 6; i++) {
		getline(file, line);
		cubeColors[i] = line;
	}
	file.close();

	setupCubeFromColors();
}

void Cube::saveToFile(const std::string& filename)
{
	std::ofstream file(filename, std::ofstream::trunc);

	for (int i = 0; i < 6; i++) {
		file << cubeColors[i] << '\n';
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

void Cube::create()
{
	while (!moves.empty())moves.pop();

	insideOut = false;

	rotationSpeed = 5;

	cubeColors = {
		"ooooooooo",
		"yyyyyyyyy",
		"bbbbbbbbb",
		"wwwwwwwww",
		"ggggggggg",
		"rrrrrrrrr"
	};

	following_moves = false;

	viewAngles = { 30,45,0 };

	initWorldMatrix(viewAngles);

	rectanglesToRotateIndices.clear();

	setupCubeFromColors();

	setButtons();
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
		temp.push_back(cubeColors[v[(i/3) * 4]][v[i + i / 3 + 1]]);
	}

	for (int i = 0; i < 12; i++) {
		cubeColors[v[(i / 3) * 4]][v[i + i / 3 + 1]] = temp[(i + 12 - 3 * n) % 12];
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
	for (int i = 0; i < 12; i++) {
		rectanglesToRotateIndices.push_back(v[(i/3) * 4] * 10 + v[i + i/3 + 1]);
	}

	rotationSettings.dir = dir;
	if (n == 3) {
		rotationSettings.dir *= -1;
		n = 1;
	}

	rotationSettings.setup(rotationSpeed, 90 * n * rotationSettings.dir);

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
		UP,    6, 7, 8, 
		RIGHT, 0, 3, 6,
		DOWN,  2, 1, 0,
		LEFT,  8, 5, 2
	};

	setupForRotation(FRONT, v, n, -1, 2);
}

void Cube::u(int n)
{
	std::vector<int> v = {
		RIGHT, 2, 1, 0,
		FRONT, 2, 1, 0,
		LEFT,  2, 1, 0,
		BACK,  2, 1, 0
	};

	setupForRotation(UP, v, n, 1, 1);
}

void Cube::r(int n)
{
	std::vector<int> v = {
		DOWN,  8, 5, 2,
		FRONT, 8, 5, 2,
		UP,    8, 5, 2,
		BACK,  0, 3, 6
	};

	setupForRotation(RIGHT, v, n, -1, 0);
}

void Cube::d(int n)
{
	std::vector<int> v = {
		RIGHT, 6, 7, 8,
		BACK,  6, 7, 8,
		LEFT,  6, 7, 8,
		FRONT, 6, 7, 8
	};

	setupForRotation(DOWN, v, n, -1, 1);
}

void Cube::l(int n)
{
	std::vector<int> v = {
		UP,    0, 3, 6,
		FRONT, 0, 3, 6,
		DOWN,  0, 3, 6,
		BACK,  8, 5, 2
	};

	setupForRotation(LEFT, v, n, 1, 0);
}

void Cube::b(int n)
{
	std::vector<int> v = {
		DOWN,  6, 7, 8,
		RIGHT, 8, 5, 2,
		UP,    2, 1, 0,
		LEFT,  0, 3, 6
	};

	setupForRotation(BACK, v, n, 1, 2);
}

void Cube::m(int n)
{
	std::vector<int> v = {
		FRONT, 7, 4, 1,
		UP,    7, 4, 1,
		BACK,  1, 4, 7,
		DOWN,  7, 4, 1
	};

	setupForRotation(-1, v, n, -1, 0);
}

void Cube::s(int n)
{
	std::vector<int> v = {
		FRONT, 5, 4, 3,
		LEFT,  5, 4, 3,
		BACK,  5, 4, 3,
		RIGHT, 5, 4, 3
	};

	setupForRotation(-1, v, n, 1, 1);
}

void Cube::e(int n)
{
	std::vector<int> v = {
		RIGHT, 1, 4, 7,
		DOWN,  5, 4, 3,
		LEFT,  7, 4, 1,
		UP,    3, 4, 5
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
		if (key == sf::Keyboard::Numpad8) viewSettings.dir = -1;
		else if (key == sf::Keyboard::Numpad2) viewSettings.dir = 1;

		viewSettings.setup(5, 30 * viewSettings.dir, &viewAngles.x);

		viewSettings.work = [this]() {
			viewSettings.instant();
			initWorldMatrix(viewAngles);
		};

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

		int n = move[1] - '0';

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
		case 'y': if (n == 1)turn_left(); else if (n == 2) { turn_left(); turn_left(); } else turn_right(); break;
		case 'x': if (n == 1)turn_up(); else if (n == 2) { turn_up(); turn_up(); } else turn_down(); break;
		}

		if (move[1] == '1')move = move[0];
		else if (move[1] == '3')move[1] = '\'';
		move[0] = std::toupper(move[0]);
		gui::Textbox::Group["CurMove"]->setString(move);
	}
	else if(!rotationSettings.animating && following_moves && moves.empty())
	{
		gui::Button::Group["Solve"]->action();
	}
	
	if (rotationSettings.animating)rotationSettings.animate();

	if (viewSettings.animating)viewSettings.animate();
}

void Cube::render(sf::RenderWindow& window)
{
	std::vector<Quad> rectanglesToRaster;

	for (int i = 0; i < mesh.size(); i++)
	{
		Quad rectTransformed = matWorld * mesh[i];

		Vector normal = unit(cross(rectTransformed[1] - rectTransformed[0], rectTransformed[2] - rectTransformed[0]));

		if ((insideOut ? -1 : 1) * dot(normal, rectTransformed[0]) < 0.0f) {
			Quad rectProjected;

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

			rectProjected.color = sf::Color(mesh[i].color.r, mesh[i].color.g, mesh[i].color.b);

			if (filling_colors) {
				if (rectProjected.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					rectProjected.color = colorMap[currentColor] - sf::Color(0, 0, 0, 70);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						cubeColors[i / 9][i % 9] = currentColor;
						mesh[i].color = colorMap[cubeColors[i / 9][i % 9]];
					}
				}
			}

			rectanglesToRaster.push_back(rectProjected);
		}
	}

	sort(rectanglesToRaster.begin(), rectanglesToRaster.end(), [](Quad& a, Quad& b) {
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