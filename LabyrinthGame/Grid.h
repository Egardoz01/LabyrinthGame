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
	int nRows;
	int nColumns;

public:
	Grid(int nRows, int nColumns);
	Grid();
private:
	void GenerateLabyrynth();
};