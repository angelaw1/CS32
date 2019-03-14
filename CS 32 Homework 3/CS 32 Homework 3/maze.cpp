#include <string>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	if (sr == er && sc == ec)
		return true;
	maze[sr][sc] = '*';
	if (maze[sr - 1][sc] == '.') {
		if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
			return true;
	}
	if (maze[sr][sc + 1] == '.') {
		if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
			return true;
	}
	if (maze[sr + 1][sc] == '.') {
		if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
			return true;
	}
	if (maze[sr][sc - 1] == '.') {
		if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
			return true;
	}
	return false;
}

/* #include <cassert>
int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X........X",
		"XX.X.XXXXX",
		"X..X.X...X",
		"X..X...X.X",
		"XXXX.XXX.X",
		"X.X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	assert(pathExists(maze, 10, 10, 6, 4, 1, 1));

	string maze1[10] = {
		"XXXXXXXXXX",
		"X........X",
		"XX.X.XXXXX",
		"X..X.X...X",
		"X..X...X.X",
		"XXXX.XXX.X",
		"X.X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};
	assert(!pathExists(maze1, 10, 10, 6, 1, 1, 8));

	string maze2[10] = {
		"XXXXXXXXXX",
		"X........X",
		"XX.X.XXXXX",
		"X..X.X...X",
		"X..X...X.X",
		"XXXX.XXX.X",
		"X.X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};
	assert(pathExists(maze2, 10, 10, 8, 8, 5, 8));

	cout << "Passed All Tests" << endl;
} */