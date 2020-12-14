#pragma once

class Cell
{
public:
	bool top;
	bool right;
};


class Grid
{
public:
	Cell **grid;
	int _nRows;
	int _nColumns;

public:
	Grid(int nRows, int nColumns);
	Grid();
};