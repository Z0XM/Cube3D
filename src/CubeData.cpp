#include "CubeData.hpp"
#include<fstream>
#include<sstream>

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

	colorMap = {
		{'r', sf::Color::Red}, {'b', sf::Color::Blue}, {'g', sf::Color::Green}, {'w', sf::Color::White}, {'y', sf::Color::Yellow}, {'o', sf::Color(255,165,0)}
	};

	loadFromFile("data/settings.txt");

	std::vector<std::vector<int>> k;
	for (int i = 0; i < 6; i++) {
		if (i == FRONT)k =		{ { 1,-1, 1,-1}, {-1,-1, 1, 1}, { 0, 0, 0, 0} };
		else if (i == BACK)k =	{ {-1, 1,-1, 1}, {-1,-1, 1, 1}, { 0, 0, 0, 0} };
		else if (i == UP)k =	{ { 1,-1, 1,-1}, { 0, 0, 0, 0}, { 1, 1,-1,-1} };
		else if (i == DOWN)k =	{ { 1,-1, 1,-1}, { 0, 0, 0, 0}, {-1,-1, 1, 1} };
		else if (i == LEFT)k =	{ { 0, 0, 0, 0}, {-1,-1, 1, 1}, { 1,-1, 1,-1} };
		else if (i == RIGHT)k = { { 0, 0, 0, 0}, {-1,-1, 1, 1}, {-1, 1,-1, 1} };
		for (int j = 0; j < 9; j++) {
			Vector p[4] = { v[s[i][j][0]], v[s[i][j][1]], v[s[i][j][2]], v[s[i][j][3]] };
			for (int i = 0; i < 4; i++) {
				p[i].x += dWidth * k[0][i];
				p[i].y += dWidth * k[1][i];
				p[i].z += dWidth * k[2][i];
			}
			mesh.push_back({ p[0], p[2], p[3], colorMap[cubeColors[i][j]] });
			mesh.push_back({ p[0], p[3], p[1], colorMap[cubeColors[i][j]] });
		}
	}
}

void Cube::update()
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 9; j++) {
			mesh[i * 18 + j * 2].color = colorMap[cubeColors[i][j]];
			mesh[i * 18 + j * 2 + 1].color = colorMap[cubeColors[i][j]];
		}
	}
}

void Cube::loadFromFile(const std::string& filename)
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

		if (var == "cubeColors") {
			for (int i = 0; i < 6; i++) {
				getline(file, line);
				stringstream sss;
				sss << line;
				sss >> line;
				cubeColors.push_back(line);
			}
		}

		else if (var == "dWidth") {
			ss >> dWidth;
		}
	}
}

void Cube::setup(std::vector<std::string>& cc, float dw)
{

}


Cube::~Cube()
{
	
}

void rotateClockwise(std::string& face, std::vector<char*>& side, int n = 1)
{
	std::vector<char> temp(face.begin(), face.end());

	auto k = [](int i) {return i / 3 + 6 - (i % 3) * 3; };

	for (int i = 0; i < 9; i++) {
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
		&cubeColors[LEFT][8], &cubeColors[LEFT][6], &cubeColors[LEFT][2],
		&cubeColors[UP][6], &cubeColors[UP][7], &cubeColors[UP][8]
	};

	rotateClockwise(cubeColors[FRONT], side, x % 4);
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
