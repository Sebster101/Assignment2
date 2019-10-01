#ifndef Grid_h
#define Grid_h
#include <iostream>
#include <string>


class Grid{
public:
	Grid(int x, int y);
	//methods used in program
	void populate();
	void print(char **pGrid);
	void randomGrid(double percentPop);
	void mapGrid(std::string fname);
	void classicSimulator();
	void doughnutSimulator();
	void mirrorSimulator();

	//variables
	int height;
	int width;
	int generation;
	//arrays used
	char **currentArray;
	char **newArray;

};

#endif