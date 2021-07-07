#include "CubeData.hpp"
#include<fstream>
#include<sstream>

Cube::Cube()
{	
	rotation_value = 0;
	animating = false;
}

Cube::~Cube()
{
}

void Cube::create(const sf::Vector2f& winSize)
{
	this->winSize = winSize;

	matWorld =
		Matrix4x4::RotationZ(0) *
		Matrix4x4::RotationY(45) *
		Matrix4x4::RotationX(30) *
		Matrix4x4::Translation(0, 0, -20);

	float aspectRatio = winSize.y / winSize.x;
	matProj = Matrix4x4::Projection(-0.1, -100, 45, aspectRatio);

	insideOut = 0;

	colorMap = {
		{'r', sf::Color::Red}, {'b', sf::Color::Blue}, {'g', sf::Color::Green}, {'w', sf::Color::White}, {'y', sf::Color::Yellow}, {'o', sf::Color(255,165,0)}
	};

	cubeColors = {
		"rgbwyogbr",
		"yyyyyyyyy",
		"ggggggggg",
		"wwwwwwwww",
		"bbbbbbbbb",
		"ooooooooo"
	};

	setup();
}


void Cube::updateMoves()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			mesh[i * 9 + j].color = colorMap[cubeColors[i][j]];
		}
	}
}

void Cube::setup()
{
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

void rotateClockwise(std::string& face, std::vector<char*>& side, int n = 1)
{
	std::vector<char> temp(face.begin(), face.end());

	auto k = [](int i) {return i / 3 + 6 - (i % 3) * 3; };

	for (int i = 0; i < face.size(); i++) {
		int j = i;
		switch (n) { case 3:j = k(j); case 2: j = k(j); case 1: j = k(j); }
		face[i] = temp[j];
	}

	temp.clear();
	for (int i = 0; i < 12; i++) {
		temp.push_back(*side[i]);
	}

	for (int i = 0; i < 12; i++) {
		*side[i] = temp[(i + 12 - 3*n) % 12];
	}
}

void Cube::f(int x)
{
	std::vector<char*> side = 
	{
		&cubeColors[RIGHT][0], &cubeColors[RIGHT][3], &cubeColors[RIGHT][6],
		&cubeColors[DOWN][2], &cubeColors[DOWN][1], &cubeColors[DOWN][0],
		&cubeColors[LEFT][8], &cubeColors[LEFT][5], &cubeColors[LEFT][2],
		&cubeColors[UP][6], &cubeColors[UP][7], &cubeColors[UP][8]
	};

	rotateClockwise(cubeColors[FRONT], side, x % 4);


	rectanglesToRotateIndices = {
		16, 17, 18,
		20, 23, 26,
		32, 31, 30,
		48, 45, 42
	};
	for (int i = 0; i < 9; i++) {
		rectanglesToRotateIndices.push_back(FRONT * 10 + i);
	}

	rotation_target = 90;
}

void Cube::u(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[RIGHT][2], &cubeColors[RIGHT][1], &cubeColors[RIGHT][0],
		&cubeColors[FRONT][2],& cubeColors[FRONT][1],& cubeColors[FRONT][0],
		&cubeColors[LEFT][2], &cubeColors[LEFT][1], &cubeColors[LEFT][0],
		&cubeColors[BACK][2],& cubeColors[BACK][1],& cubeColors[BACK][0]
	};

	rotateClockwise(cubeColors[UP], side, x % 4);

}

void Cube::r(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[DOWN][8], &cubeColors[DOWN][5], &cubeColors[DOWN][2],
		&cubeColors[FRONT][8],&cubeColors[FRONT][5],&cubeColors[FRONT][2],
		&cubeColors[UP][8], &cubeColors[UP][5], &cubeColors[UP][2],
		&cubeColors[BACK][0],&cubeColors[BACK][3],&cubeColors[BACK][6]
	};

	rotateClockwise(cubeColors[RIGHT], side, x % 4);
}

void Cube::d(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[RIGHT][6], &cubeColors[RIGHT][7], &cubeColors[RIGHT][8],
		&cubeColors[BACK][6],&cubeColors[BACK][7],&cubeColors[BACK][8],
		&cubeColors[LEFT][6], &cubeColors[LEFT][7], &cubeColors[LEFT][8],
		&cubeColors[FRONT][6],&cubeColors[FRONT][7],&cubeColors[FRONT][8]
	};

	rotateClockwise(cubeColors[DOWN], side, x % 4);
}

void Cube::l(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[DOWN][0], &cubeColors[DOWN][3], &cubeColors[DOWN][6],
		&cubeColors[BACK][8],&cubeColors[BACK][5],&cubeColors[BACK][2],
		&cubeColors[UP][0], &cubeColors[UP][3], &cubeColors[UP][6],
		&cubeColors[FRONT][0],&cubeColors[FRONT][3],&cubeColors[FRONT][6]
	};

	rotateClockwise(cubeColors[LEFT], side, x % 4);
}

void Cube::b(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[RIGHT][8], &cubeColors[RIGHT][5], &cubeColors[RIGHT][2],
		&cubeColors[UP][2],&cubeColors[UP][1],&cubeColors[UP][0],
		&cubeColors[LEFT][0], &cubeColors[LEFT][3], &cubeColors[LEFT][6],
		&cubeColors[DOWN][6],&cubeColors[DOWN][7],&cubeColors[DOWN][8]
	};

	rotateClockwise(cubeColors[BACK], side, x % 4);
}

void Cube::m(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[FRONT][7], &cubeColors[FRONT][4], &cubeColors[FRONT][1],
		&cubeColors[UP][7],&cubeColors[UP][4],&cubeColors[UP][1],
		&cubeColors[BACK][1], &cubeColors[BACK][4], &cubeColors[BACK][7],
		&cubeColors[DOWN][7],&cubeColors[DOWN][4],&cubeColors[DOWN][1]
	};
	std::string face = "";
	rotateClockwise(face, side, x % 4);
}

void Cube::s(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[FRONT][5], &cubeColors[FRONT][4], &cubeColors[FRONT][3],
		&cubeColors[LEFT][5],&cubeColors[LEFT][4],&cubeColors[LEFT][3],
		&cubeColors[BACK][5], &cubeColors[BACK][4], &cubeColors[BACK][3],
		&cubeColors[RIGHT][5],&cubeColors[RIGHT][4],&cubeColors[RIGHT][3]
	};
	std::string face = "";
	rotateClockwise(face, side, x % 4);
}

void Cube::e(int x)
{
	std::vector<char*> side =
	{
		&cubeColors[RIGHT][1], &cubeColors[RIGHT][4], &cubeColors[RIGHT][7],
		&cubeColors[DOWN][5], &cubeColors[DOWN][4], &cubeColors[DOWN][3],
		&cubeColors[LEFT][7], &cubeColors[LEFT][4], &cubeColors[LEFT][1],
		&cubeColors[UP][3], &cubeColors[UP][4], &cubeColors[UP][5]
	};
	std::string face = "";
	rotateClockwise(face, side, x % 4);
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
	if (animating)return false;

	if (key == sf::Keyboard::I)insideOut = !insideOut;
	else if (key == sf::Keyboard::R)r(1);
	else if (key == sf::Keyboard::U)u(1);
	else if (key == sf::Keyboard::F)f(1);
	else if (key == sf::Keyboard::L)l(1);
	else if (key == sf::Keyboard::D)d(1);
	else if (key == sf::Keyboard::B)b(1);
	else if (key == sf::Keyboard::M)m(1);
	else if (key == sf::Keyboard::S)s(1);
	else if (key == sf::Keyboard::E)e(1);
	else if (key == sf::Keyboard::Right)turn_right();
	else if (key == sf::Keyboard::Left)turn_left();
	else if (key == sf::Keyboard::Up)turn_up();
	else if (key == sf::Keyboard::Down)turn_down();
	else return false;

	animating = true;
	return true;
}

void Cube::update() 
{
	if (animating) {
		rotation_value++;

		for (auto i : rectanglesToRotateIndices) {
			i = (i / 10) * 9 + i % 10;
			mesh[i].vertex[0] = Matrix4x4::RotationZ(1) * mesh[i].vertex[0];
			mesh[i].vertex[1] = Matrix4x4::RotationZ(1) * mesh[i].vertex[1];
			mesh[i].vertex[2] = Matrix4x4::RotationZ(1) * mesh[i].vertex[2];
			mesh[i].vertex[3] = Matrix4x4::RotationZ(1) * mesh[i].vertex[3];
		}

		if (rotation_value >= rotation_target) {
			animating = false;
			rotation_value = 0;
			rectanglesToRotateIndices.clear();
		}
	}
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

			auto offsetPoint = [this](Vector& p) {
				p = p / p.w;
				p.y *= -1;
				p = p + Vector{ 1, 1, 0 };
				p.x *= 0.5f * winSize.x;
				p.y *= 0.5f * winSize.y;
			};

			offsetPoint(rectProjected[0]);
			offsetPoint(rectProjected[1]);
			offsetPoint(rectProjected[2]);
			offsetPoint(rectProjected[3]);

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