#include "CubeData.hpp"

Cube::Cube()
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

	sf::Color faceColors[6] = { sf::Color::Red, sf::Color::Yellow, sf::Color::Green, sf::Color::White, sf::Color::Blue, sf::Color(255, 165, 0) };

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			mesh.push_back({ v[s[i][j][0]], v[s[i][j][2]], v[s[i][j][3]], faceColors[i] });
			mesh.push_back({ v[s[i][j][0]], v[s[i][j][3]], v[s[i][j][1]], faceColors[i] });
		}
	}

	std::vector<std::vector<int>> e =
	{
		{FRONT * 9 + 0, UP * 9 + 6, LEFT * 9 + 2},
		{FRONT * 9 + 1, UP * 9 + 7},
		{FRONT * 9 + 2, UP * 9 + 8, RIGHT * 9 + 0},
		{FRONT * 9 + 3, LEFT * 9 + 5},
		{FRONT * 9 + 4},
		{FRONT * 9 + 5, RIGHT * 9 + 3},
		{FRONT * 9 + 6, DOWN * 9 + 0, LEFT * 9 + 8},
		{FRONT * 9 + 7, DOWN * 9 + 1},
		{FRONT * 9 + 8, DOWN * 9 + 2, RIGHT * 9 + 6},

		{LEFT * 9 + 1, UP * 9 + 3},
		{UP * 9 + 4},
		{RIGHT * 9 + 1, UP * 9 + 5},
		{LEFT * 9 + 4},
		{},
		{RIGHT * 9 + 4},
		{LEFT * 9 + 7, DOWN * 9 + 3},
		{DOWN * 9 + 4},
		{RIGHT * 9 + 7, DOWN * 9 + 5},
		
		{BACK * 9 + 2, UP * 9 + 0, LEFT * 9 + 0},
		{BACK * 9 + 1, UP * 9 + 1},
		{BACK * 9 + 0, UP * 9 + 2, RIGHT * 9 + 2},
		{BACK * 9 + 5, LEFT * 9 + 3},
		{BACK * 9 + 4},
		{BACK * 9 + 3, RIGHT * 9 + 5},
		{BACK * 9 + 8, DOWN * 9 + 6, LEFT * 9 + 6},
		{BACK * 9 + 7, DOWN * 9 + 7},
		{BACK * 9 + 6, DOWN * 9 + 8, RIGHT * 9 + 8}
	};

	for (int i = 0; i < e.size(); i++) {
		elements.push_back(std::vector<Triangle*>());
		for (int j = 0; j < e[i].size(); j++)
		{
			elements.back().push_back(&mesh[e[i][j] * 2]);
			elements.back().push_back(&mesh[e[i][j] * 2 + 1]);
		}
	}

	for (int i = 0; i < 9; i++) {
		faces[FRONT].push_back(elements[i]);
		faces[UP].push_back(elements[(i / 3) * 9 + i % 3]);
		faces[RIGHT].push_back(elements[(i + 1) * 3 - 1]);
		faces[DOWN].push_back(elements[(i / 3) * 9 + i % 3 + 6]);
		faces[LEFT].push_back(elements[i * 3]);
		faces[BACK].push_back(elements[i + 18]);
	}
}

Cube::~Cube()
{
	
}

void Cube::f(int x)
{
	x = x % 4;
	float theta = -90 * x;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < faces[FRONT][i].size(); j++){
			*faces[FRONT][i][j] = Matrix4x4::RotationZ(theta) * *faces[FRONT][i][j];
		}
	}
	for (int k = 0; k < x; k++) {
		std::vector<std::vector<Triangle*>> temp(faces[FRONT].begin(), faces[FRONT].end());
		for (int i = 0; i < 9; i++)
		{
			faces[FRONT][i] = temp[i / 3 + 6 - (i % 3) * 3];
		}

	}

	// 0 1 2
	// 3 4 5
	// 6 7 8

	// 6 3 0
	// 7 4 1
	// 8 5 2
}

void Cube::u(int x)
{
	x = x % 4;
	float theta = 90 * x;
	
	for (int i = 0; i < 9; i++) {
		faces[UP][i]->transform = faces[UP][i]->transform * Matrix4x4::RotationY(theta);
	}
}

void Cube::r(int x)
{
	x = x % 4;
	float theta = -90 * x;

	for (int i = 0; i < 9; i++) {
		faces[RIGHT][i]->transform = faces[RIGHT][i]->transform * Matrix4x4::RotationX(theta);
	}
}

void Cube::d(int x)
{
	x = x % 4;
	float theta = -90 * x;

	for (int i = 0; i < 9; i++) {
		faces[DOWN][i]->transform = faces[DOWN][i]->transform * Matrix4x4::RotationY(theta);
	}
}

void Cube::l(int x)
{
	x = x % 4;
	float theta = 90 * x;

	for (int i = 0; i < 9; i++) {
		faces[LEFT][i]->transform = faces[LEFT][i]->transform * Matrix4x4::RotationX(theta);
	}
}

void Cube::b(int x)
{
	x = x % 4;
	float theta = 90 * x;

	for (int i = 0; i < 9; i++) {
		faces[BACK][i]->transform = faces[BACK][i]->transform * Matrix4x4::RotationZ(theta);
	}
}
