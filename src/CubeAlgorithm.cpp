#include "CubeAlgorithm.hpp"
#include<algorithm>

using namespace std;

void rotateFaceClockwise(int face, int n);
void rotateSidesClockwise(vector<int>& v, int n);
void setupForRotation(int face, std::vector<int>& v, int n);

void f(int x);
void u(int x);
void r(int x);
void d(int x);
void l(int x);
void b(int x);
void m(int x);
void s(int x);
void e(int x);
void turn_left();
void turn_right();
void turn_up();
void turn_down();

enum Face {
	FRONT, UP, RIGHT, DOWN, LEFT, BACK
};
enum ELement {
	C1, E1, C2, E2, O, E3, C3, E4, C4
};

vector<string> cube(6), moves[6];
int index;

bool fill_moves = true;

void cross();
void f2l();
void upcross();
void oll();
void corner_pll();
void edge_pll();

vector<string> generateAlgorithm(vector<string> cc)
{
	for (index = 0; index < 6; index++) {
		moves[index].clear();
		cube = cc;

		if (index == 1) {
			turn_down();
		}
		else if (index == 2) {
			turn_down(); turn_down();
		}
		else if (index == 3) {
			turn_up();
		}
		else if (index == 4) {
			turn_left(); turn_down();
		}
		else {
			turn_right(); turn_down();
		}

		/////////////////////////////////////////////////////////////////////////////////////////

		if (cube[DOWN][E1] != cube[DOWN][O] || cube[DOWN][E2] != cube[DOWN][O] || cube[DOWN][E3] != cube[DOWN][O] || cube[DOWN][E4] != cube[DOWN][O])
			cross();

		while (cube[FRONT][O] != cube[FRONT][E4])d(1);

		f2l();

		if (cube[UP][E1] != cube[UP][O] || cube[UP][E2] != cube[UP][O] || cube[UP][E3] != cube[UP][O] || cube[UP][E4] != cube[UP][O])
			upcross();

		oll();

		if (cube[FRONT][C1] != cube[FRONT][C2] || cube[BACK][C1] != cube[BACK][C2])
			corner_pll();

		if (cube[FRONT][C1] != cube[FRONT][E1] || cube[BACK][C1] != cube[BACK][E1])
			edge_pll();

		while (cube[FRONT][C1] != cube[FRONT][O])u(1);

		////////////////////////////////////////////////////////////////////////////////////////

		int N = moves[index].size();
		for (int i = 0; i < N - 1; i++, N = moves[index].size()) {
			if (i < 0)continue;
			if (moves[index][i][0] != moves[index][i + 1][0])continue;
			int n1 = moves[index][i][1] - '0', n2 = moves[index][i + 1][1] - '0';
			if (n1 + n2 == 4) {
				moves[index].erase(moves[index].begin() + i, moves[index].begin() + (i + 2));
				i -= 1;
			}
			else {
				moves[index].erase(moves[index].begin() + (i + 1));
				moves[index][i][1] = (n1 + n2) % 4 + '0';
				i -= 1;
			}
			if (i >= 0 && i + 1 < moves[index].size() && moves[index][i][0] == moves[index][i + 1][0]) {
				i -= 1;
			}
		}
	}

	int min = 0;

	for (int i = 1; i < 6; i++) {
		if (moves[i].size() < moves[min].size())min = i;
	}

	return moves[min];
}

void cross()
{
	while (cube[UP][E1] != cube[DOWN][O] || cube[UP][E4] != cube[DOWN][O] || cube[UP][E2] != cube[DOWN][O] || cube[UP][E3] != cube[DOWN][O]) {
		for (int side = 0; side < 6; side++) {
			for (int piece = 1; piece <= 7; piece += 2) {
				if (cube[side][piece] == cube[DOWN][O]) {
					if (piece == E1 && side != DOWN && side != UP) {
						if (side == FRONT) { f(3); l(3); }
						else if (side == BACK) { b(1); l(1); }
						else if (side == LEFT) { l(1); f(1); }
						else if (side == RIGHT) { r(3); f(3); }
					}
					if (piece == E4 && side != DOWN && side != UP) {
						if (side == FRONT) { f(1); l(3); }
						else if (side == BACK) { b(3); l(1); }
						else if (side == LEFT) { l(3); f(1); }
						else if (side == RIGHT) { r(1); f(3); }
					}
					if ((side == DOWN && piece == E1) || (side == RIGHT && piece == E2) || (side == LEFT && piece == E3)) {
						while (cube[UP][E4] == cube[DOWN][O]) u(1);
						if (side == DOWN) f(2);
						else if (side == RIGHT) f(3);
						else if (side == LEFT) f(1);
					}
					if ((side == DOWN && piece == E3) || (side == FRONT && piece == E3) || (side == BACK && piece == E2)) {
						while (cube[UP][E3] == cube[DOWN][O]) u(1);
						if (side == DOWN) r(2);
						else if (side == FRONT) r(1);
						else if (side == BACK) r(3);
					}
					if ((side == DOWN && piece == E4) || (side == RIGHT && piece == E3) || (side == LEFT && piece == E2)) {
						while (cube[UP][E1] == cube[DOWN][O]) u(1);
						if (side == DOWN) b(2);
						else if (side == RIGHT) b(1);
						else if (side == LEFT) b(3);
					}
					if ((side == DOWN && piece == E2) || (side == BACK && piece == E3) || (side == FRONT && piece == E2)) {
						while (cube[UP][E2] == cube[DOWN][O]) u(1);
						if (side == DOWN) l(2);
						else if (side == BACK) l(1);
						else if (side == FRONT) l(3);
					}
				}
			}
		}
	}

	while (cube[DOWN][E1] != cube[DOWN][O] || cube[DOWN][E2] != cube[DOWN][O] || cube[DOWN][E3] != cube[DOWN][O] || cube[DOWN][E4] != cube[DOWN][O]) {
		bool done = false;
		if (cube[FRONT][E1] == cube[FRONT][O] && cube[UP][E4] == cube[DOWN][O]) { f(2); done = true; }
		if (cube[LEFT][E1] == cube[LEFT][O] && cube[UP][E2] == cube[DOWN][O]) { l(2); done = true; }
		if (cube[BACK][E1] == cube[BACK][O] && cube[UP][E1] == cube[DOWN][O]) { b(2); done = true; }
		if (cube[RIGHT][E1] == cube[RIGHT][O] && cube[UP][E3] == cube[DOWN][O]) { r(2); done = true; }
		if (!done) u(1);
	}
}

void f2l()
{
	auto edge_position = []() {
		fill_moves = false;
		bool end = false;
		for (int edge = 0; edge < 8; edge++) {
			switch (edge)
			{
			case 0: u(1); r(3); break;
			case 1: r(3);		break;
			case 2: u(3); r(3); break;
			case 3: u(2); r(3); break;
			case 4: b(2); r(2); break;
			case 5: r(2);		break;
			case 7: f(2);		break;
			}

			if (cube[FRONT][E3] == cube[FRONT][O] && cube[RIGHT][E2] == cube[RIGHT][O] || cube[FRONT][E3] == cube[RIGHT][O] && cube[RIGHT][E2] == cube[FRONT][O])
				end = true;

			switch (edge)
			{
			case 0: r(1); u(3); break;
			case 1: r(1);		break;
			case 2: r(1); u(1); break;
			case 3: r(1); u(2); break;
			case 4: r(2); b(2); break;
			case 5: r(2);		break;
			case 7: f(2);		break;
			}

			if (end) {
				fill_moves = true;
				return edge;
			}
		}
	};

	auto corner_position = []() {
		fill_moves = false;
		bool end = false;
		for (int corner = 0; corner < 8; corner++) {
			switch (corner)
			{
			case 0: u(2); r(3); break;
			case 1: r(2);		break;
			case 2:	r(3);		break;
			case 3: u(3); r(3); break;
			case 4: d(2);		break;
			case 5: d(3);		break;
			case 7: d(1);		break;
			}

			if (cube[DOWN][C2] == cube[DOWN][O] && cube[FRONT][C4] == cube[FRONT][O] || cube[DOWN][C2] == cube[RIGHT][O] && cube[FRONT][C4] == cube[DOWN][O] || cube[DOWN][C2] == cube[FRONT][O] && cube[FRONT][C4] == cube[RIGHT][O])
				end = true;

			switch (corner)
			{
			case 0: r(1); u(2); break;
			case 1: r(2);		break;
			case 2: r(1);		break;
			case 3: r(1); u(1); break;
			case 4:	d(2);		break;
			case 5: d(1);		break;
			case 7: d(3);		break;
			}

			if (end) {
				fill_moves = true;
				return corner;
			}
		}
	};

	for (int turn = 0; turn < 4; turn++) {
		if (cube[DOWN][C2] != cube[DOWN][O] or cube[FRONT][C4] != cube[FRONT][O] or cube[FRONT][E3] != cube[FRONT][O] or cube[RIGHT][E2] != cube[RIGHT][O]) {
			int count = 0;
			int corner = corner_position();
			if (corner >= 4 && corner <= 7) {
				while (corner != 6) {
					count += 1;
					d(1); corner = corner_position();
				}
				f(3); u(3); f(1);
				while (count != 0) {
					count -= 1;
					d(3);
				}
			}
			else {
				while (corner != 1) {
					u(3);
					corner = corner_position();
				}
			}
			int edge = edge_position();
			bool done = false;
			if (edge == 0 && cube[UP][E1] == cube[UP][C2] && cube[BACK][C1] == cube[BACK][E1]) {
				u(2); r(1); u(3); r(3); done = true;
			}
			else if (edge == 1 && cube[UP][C2] == cube[UP][E3] && cube[RIGHT][E1] == cube[RIGHT][C2]) {
				f(3); u(1); f(1); done = true;
			}

			if (!done) {
				switch (edge)
				{
				case 0: r(1); u(3); r(3);		break;
				case 1: u(1); r(1); u(2); r(3); break;
				case 4: l(1); u(1); l(3);		break;
				case 5: u(1); r(3); u(3); r(1);	break;
				case 6: f(3); u(3); f(1);		break;
				case 7: f(1); u(3); f(3);		break;
				}


				while (corner != 2) {
					u(1);
					corner = corner_position();
				}

				edge = edge_position();
				if (edge == 0) {
					u(1); f(3); u(3); f(1); u(3);
				}

				if (cube[FRONT][C2] == cube[DOWN][O]) {
					if (cube[UP][E2] == cube[RIGHT][O]) {
						f(3); u(3); f(1);
					}
					else {
						u(3); r(1); u(2); r(3); u(2); r(1); u(3); r(3);
					}
				}
				else if (cube[FRONT][C2] == cube[RIGHT][O]) {
					if (cube[UP][E2] == cube[RIGHT][O]) {
						u(3); f(3); u(2); f(1); u(3); f(3); u(1); f(1);
					}
					else {
						u(2); r(1); u(1); r(3); u(1); r(1); u(3); r(3);
					}
				}
				else if (cube[FRONT][C2] == cube[FRONT][O]) {
					if (cube[UP][E2] == cube[RIGHT][O]) {
						u(1); f(3); u(3); f(1); u(2); f(3); u(1); f(1);
					}
					else {
						u(1); f(3); u(1); f(1); u(3); r(1); u(1); r(3);
					}
				}
			}
		}
		turn_left();
	}
}

void upcross()
{
	if (cube[UP][E1] != cube[UP][O] && cube[UP][E2] != cube[UP][O] && cube[UP][E3] != cube[UP][O]) {
		f(1); u(1); r(1); u(3); r(3); f(3); u(1); f(1); r(1); u(1); r(3); u(3); f(3);
	}
	else if (cube[UP][E1] == cube[UP][E4]) {
		u(1); f(1); r(1); u(1); r(3); u(3); f(3);
	}
	else if (cube[UP][E3] == cube[UP][E2]) {
		f(1); r(1); u(1); r(3); u(3); f(3);
	}
	else if (cube[UP][E3] == cube[UP][E4]) {
		u(2); f(1); u(1); r(1); u(3); r(3); f(3);
	}
	else if (cube[UP][E1] == cube[UP][E2]) {
		f(1); u(1); r(1); u(3); r(3); f(3);
	}
	else if (cube[UP][E1] == cube[UP][E3]) {
		u(3); f(1); u(1); r(1); u(3); r(3); f(3);
	}
	else if (cube[UP][E4] == cube[UP][E2]) {
		u(1); f(1); u(1); r(1); u(3); r(3); f(3);
	}
}

void oll()
{
	int corners_to_orient = cube[UP][C1] == cube[UP][O];
	corners_to_orient += cube[UP][C2] == cube[UP][O];
	corners_to_orient += cube[UP][C3] == cube[UP][O];
	corners_to_orient += cube[UP][C4] == cube[UP][O];
	corners_to_orient = 4 - corners_to_orient;

	if (corners_to_orient == 3) {
		while (cube[UP][C3] != cube[UP][O]) u(1);
		if (cube[LEFT][C1] == cube[UP][O]) {
			u(3); l(3); u(3); l(1); u(3); l(3); u(2); l(1);
		}
		else if (cube[FRONT][C2] == cube[UP][O]) {
			r(1); u(1); r(3); u(1); r(1); u(2); r(3);
		}
	}

	if (corners_to_orient == 4) {
		while (cube[FRONT][C1] != cube[UP][O] || cube[FRONT][C2] != cube[UP][O]) u(1);
		if (cube[BACK][C1] == cube[UP][O] && cube[BACK][2] == cube[UP][O]) {
			r(1); u(2); r(3); u(3); r(1); u(1); r(3); u(3); r(1); u(3); r(3);
		}
		else {
			u(1); r(1); u(2); r(2); u(3); r(2); u(3); r(2); u(2); r(1);
		}
	}
	if (corners_to_orient == 2) {
		if ((cube[UP][C1] == cube[UP][O] && cube[UP][C4] == cube[UP][O]) || (cube[UP][C2] == cube[UP][O] && cube[UP][C3] == cube[UP][O])) {
			while (cube[FRONT][C1] != cube[UP][O]) u(1);
			r(3); f(1); r(1); b(3); r(3); f(3); r(1); b(1);
		}
		else {
			while (cube[UP][C4] == cube[UP][O] or cube[UP][C3] == cube[UP][O]) u(1);
			if (cube[LEFT][C2] == cube[UP][O]) {
				r(1); b(1); r(3); f(1); r(1); b(3); r(3); f(3);
			}
			if (cube[FRONT][C1] == cube[UP][O]) {
				r(2); d(1); r(3); u(2); r(1); d(3); r(3); u(2); r(3);
			}
		}
	}
}

void corner_pll()
{
	int count = 0;

	while (cube[BACK][C1] != cube[BACK][C2]) {
		u(1); count += 1;
		if (count == 4)break;
	}
	if (count == 4) {
		r(3); f(1); r(3); b(2); r(1); f(3); r(3); b(2); r(2); u(1);
	}
	r(3); f(1); r(3); b(2); r(1); f(3); r(3); b(2); r(2);
}

void edge_pll()
{
	int count = 0;
	while (cube[BACK][C1] != cube[BACK][E1]) {
		u(1); count += 1;
		if (count == 4)break;
	}

	bool done = false;
	if (count == 4) {
		if (cube[FRONT][E1] == cube[BACK][C1] && cube[BACK][E1] == cube[FRONT][C1]) {
			done = true;
			m(2); u(1); m(2);  u(2); m(2); u(1); m(2);
		}
		else {
			r(1); u(3); r(1); u(1); r(1); u(1); r(1); u(3); r(3); u(3); r(2);
			while (cube[BACK][C1] != cube[BACK][E1]) u(1);
		}
	}
	else if (cube[FRONT][E1] == cube[RIGHT][C1] && !done) {
		r(1); u(3); r(1); u(1); r(1); u(1); r(1); u(3); r(3); u(3); r(2);
	}
	else if (cube[FRONT][E1] == cube[LEFT][C1] && !done) {
		r(2); u(1); r(1); u(1); r(3); u(3); r(3); u(3); r(3); u(1); r(3);
	}
}

void rotateFaceClockwise(int face, int n = 1)
{
	std::string temp(cube[face]);
	auto k = [](int i) {return i / 3 + 6 - (i % 3) * 3; };

	for (int i = 0; i < 9; i++) {
		int j = i;
		switch (n) {
		case 3:j = k(j); case 2: j = k(j); case 1: j = k(j);
		}
		cube[face][i] = temp[j];
	}
}

void rotateSidesClockwise(std::vector<int>& v, int n)
{
	std::string temp;

	for (int i = 0; i < 12; i++) {
		temp.push_back(cube[v[i] / 10][v[i] % 10]);
	}

	for (int i = 0; i < 12; i++) {
		cube[v[i] / 10][v[i] % 10] = temp[(i + 12 - 3 * n) % 12];
	}
}

void setupForRotation(int face, std::vector<int>& v, int n)
{
	n = n % 4;
	if (face >= 0)rotateFaceClockwise(face, n);
	rotateSidesClockwise(v, n);

	if (fill_moves) {
		string move;
		switch (face)
		{
		case 0:move = "f"; break;
		case 1:move = "u"; break;
		case 2:move = "r"; break;
		case 3:move = "d"; break;
		case 4:move = "l"; break;
		case 5:move = "b"; break;
		case -1:move = "m"; break;
		case -2:move = "s"; break;
		case -3:move = "e"; break;
		}
		move += char(n + 48);
		moves[index].push_back(move);
	}
}

void f(int n)
{
	std::vector<int> v = {
		16, 17, 18,
		20, 23, 26,
		32, 31, 30,
		48, 45, 42
	};
	setupForRotation(0, v, n);
}

void u(int n)
{
	std::vector<int> v = {
		22, 21, 20,
		 2,  1,  0,
		42, 41, 40,
		52, 51, 50
	};

	setupForRotation(1, v, n);
}

void r(int n)
{
	std::vector<int> v = {
		38, 35, 32,
		 8,  5,  2,
		18, 15, 12,
		50, 53, 56
	};

	setupForRotation(2, v, n);
}

void d(int n)
{
	std::vector<int> v = {
		26, 27, 28,
		56, 57, 58,
		46, 47, 48,
		 6,  7,  8
	};

	setupForRotation(3, v, n);
}

void l(int n)
{
	std::vector<int> v = {
		10, 13, 16,
		 0,  3,  6,
		30, 33, 36,
		58, 55, 52
	};

	setupForRotation(4, v, n);
}

void b(int n)
{
	std::vector<int> v = {
		36, 37, 38,
		28, 25, 22,
		12, 11, 10,
		40, 43, 46
	};

	setupForRotation(5, v, n);
}

void m(int n)
{
	std::vector<int> v = {
		 7,  4,  1,
		17, 14, 11,
		51, 54, 57,
		37, 34, 31
	};

	setupForRotation(-1, v, n);
}

void s(int n)
{
	std::vector<int> v = {
		 5,  4,  3,
		45, 44, 43,
		55, 54, 53,
		25, 24, 23
	};

	setupForRotation(-2, v, n);
}

void e(int n)
{
	std::vector<int> v = {
		21, 24, 27,
		35, 34, 33,
		47, 44, 41,
		13, 14, 15
	};

	setupForRotation(-3, v, n);
}

void turn_left()
{
	if (fill_moves) {
		moves[index].push_back("y1");
		fill_moves = false;
	}
	u(1); s(1); d(3);

	if (!moves[index].empty() && moves[index].back() == "y1")fill_moves = true;
}

void turn_right()
{
	if (fill_moves) {
		moves[index].push_back("y3");
		fill_moves = false;
	}
	u(3); s(3); d(1);
	if (!moves[index].empty() && moves[index].back() == "y3")fill_moves = true;
}

void turn_up()
{
	if (fill_moves) {
		moves[index].push_back("x1");
		fill_moves = false;
	}
	r(1); m(1); l(3);
	if (!moves[index].empty() && moves[index].back() == "x1")fill_moves = true;
}

void turn_down()
{
	if (fill_moves) {
		moves[index].push_back("x3");
		fill_moves = false;
	}
	r(3); m(3); l(1);
	if (!moves[index].empty() && moves[index].back() == "x3")fill_moves = true;
}