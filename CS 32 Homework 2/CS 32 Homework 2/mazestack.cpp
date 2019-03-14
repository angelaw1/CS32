#include <string>
#include <iostream>
#include <stack>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	stack<Coord> coordStack;
	Coord start(sr, sc);
	Coord end(er, ec);
	coordStack.push(start);
	maze[sr][sc] = '*';
	while (!coordStack.empty()) {
		Coord current = coordStack.top();
		coordStack.pop();
		if (current.r() == end.r() && current.c() == end.c())
			return true;
		Coord north(current.r() - 1, current.c());
		if (maze[north.r()][north.c()] == '.') {
			coordStack.push(north);
			maze[north.r()][north.c()] = '*';
		}
		Coord east(current.r(), current.c() + 1);
		if (maze[east.r()][east.c()] == '.') {
			coordStack.push(east);
			maze[east.r()][east.c()] = '*';
		}
		Coord south(current.r() + 1, current.c());
		if (maze[south.r()][south.c()] == '.') {
			coordStack.push(south);
			maze[south.r()][south.c()] = '*';
		}
		Coord west(current.r(), current.c() - 1);
		if (maze[west.r()][west.c()] == '.') {
			coordStack.push(west);
			maze[west.r()][west.c()] = '*';
		}
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