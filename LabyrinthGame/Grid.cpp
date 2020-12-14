
#include "stdafx.h"
#include "Grid.h"


Grid::Grid(int nRows, int nColumns)
{
	nRows += 1;
	nColumns += 1;

	this->grid = new Cell*[nRows];
	for (int i = 0; i < nRows; i++)
		this->grid[i] = new Cell[nColumns];
	_nRows = nRows;
	_nColumns = nColumns;
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nColumns; j++)
		{
			grid[i][j].top = false;
			grid[i][j].right = false;
		}
	for (int i = 0; i < nRows; i++)
	{
		grid[i][0].right = true;
		grid[i][nColumns-1].right = true;
	}
	for (int i = 0; i < nColumns; i++)
	{
		grid[0][i].top = true;
		grid[nRows - 1][i].top = true;
	}
	grid[0][0].top = false;
	grid[nRows-1][0].right = false;
	grid[nRows - 1][0].top = false;
	grid[nRows - 1][nColumns-1].right = false;
}

Grid::Grid()
{
	
}