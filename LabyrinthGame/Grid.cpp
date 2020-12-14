
#include "stdafx.h"
#include "Grid.h"
#include <stack>
#include <time.h>
#include <utility>
#include <vector>

Grid::Grid(int nRows, int nColumns)
{


	this->grid = new Cell*[nRows];
	for (int i = 0; i < nRows; i++)
		this->grid[i] = new Cell[nColumns];
	_nRows = nRows;
	_nColumns = nColumns;
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nColumns; j++)
		{
			grid[i][j].top = true;
			grid[i][j].right = true;
		}
	
	GenerateLabyrynth();
}

Grid::Grid()
{
	
}

void Grid::GenerateLabyrynth()
{
	std::stack<std::pair<int,int>> st;
	srand(time(NULL));
	int x = rand() % _nColumns;
	int y = rand() % _nRows;
	st.push({ x,y });
	std::vector<std::vector<int>> visited(_nRows, std::vector<int>(_nColumns));
	//visited[x][y] = true;
	std::vector<std::vector<std::pair<int, int>>> parent(_nRows, std::vector < std::pair<int, int >> (_nColumns));
	while (!st.empty())
	{

		int x = st.top().first;
		int y = st.top().second;
		st.pop();
		if (visited[y][x])
			continue;
		visited[y][x] = true;
		int px = parent[y][x].first;
		int py = parent[y][x].second;
		
		if (py == y && px == x-1)
		{
			grid[py][px].right = false;
		}

		if (py == y && px == x + 1)
		{
			grid[y][x].right = false;
		}

		if (py == y+1 && px == x)
		{
			grid[py][px].top = false;
		}

		if (py == y - 1 && px == x)
		{
			grid[y][x].top = false;
		}


		std::vector<char> next;
		if (x > 0)
			if(!visited[y][x-1])
				next.push_back('l');
		if (y > 0)
			if (!visited[y-1][x])
				next.push_back('t');
		if (x < _nColumns-1)
			if (!visited[y][x+1])
				next.push_back('r');
		if (y < _nRows - 1)
			if (!visited[y +1][x])
				next.push_back('b');
		
		while (!next.empty())
		{
			int ind = rand() % next.size();
			char nextStep = next[ind];
			for (int i = ind; i < next.size()-1; i++)
				next[i] = next[i + 1];
			next.pop_back();
			
			if (nextStep == 'l')
			{
				st.push({ x - 1,y });
				parent[y][x - 1] = { x,y };
			}
			if (nextStep == 'r')
			{
				
				st.push({ x + 1,y });
				parent[y][x + 1] = { x,y };
			}
			if (nextStep == 'b')
			{
				
				st.push({ x,y +1});
				parent[y+1][x] = { x,y };
			}
			if (nextStep == 't')
			{	
				st.push({ x,y - 1 });
				parent[y-1][x] = { x,y };
			}
		}
	}

	int a = 1;
}