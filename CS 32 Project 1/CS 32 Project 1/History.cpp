#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
	m_nRows = nRows;
	m_nCols = nCols;
	for (int r = 1; r <= m_nRows; r++)
		for (int c = 1; c <= m_nCols; c++)
			m_grid[r - 1][c - 1] = '.';
}

bool History::record(int r, int c)
{
	if (r < 1 || r > m_nRows || c < 1 || c > m_nCols)
		return false;
	char temp = m_grid[r - 1][c - 1];
	if (temp == '.')
		m_grid[r - 1][c - 1] = 'A';
	else if (temp != 'Z')
		m_grid[r - 1][c - 1] = temp + 1;
	return true;
}

void History::display() const
{
	clearScreen();
	for (int i = 1; i <= m_nRows; i++)
	{
		for (int j = 1; j <= m_nCols; j++)
			cout << m_grid[i - 1][j - 1];
		cout << endl;
	}
	cout << endl;
}