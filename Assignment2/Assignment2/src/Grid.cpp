#include "Grid.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;
//constructor
Grid::Grid(int x, int y){ 
	srand(time(NULL));
	cout << "Starting Program" << endl;
	generation = 0;
	width = x;
	height = y;
	//two arrays one for current and one for handling changes to board without affecting current array
	Grid::currentArray = new char *[y];
	Grid::newArray = new char *[y];
	for (int i = 0; i<y; i++){
		currentArray[i] = new char [x];
		newArray[i] = new char [x];

	}

	

   }
   	//Assigns grid spots based on file given by user
    void Grid::mapGrid(std::string fname){
   	ifstream gridInput(fname.c_str());
   	if (gridInput.is_open()){
   		std::string line;
   		int currentLine = 0;
   		//searches each line for X and assigns proper grid position
   		while(getline(gridInput, line)){
   			for(int i=0; i<line.length(); ++i){
   				if(line[i] == 'X' || line[i] == 'x'){
   					currentArray[i][currentLine] = 'X';
   				}
   			}
   			currentLine++;
   		}
   	}
   }
   //populates new and current grid as empty
   void Grid::populate(){
   	for(int i = 0; i < height; i++){
          for(int j = 0; j < width; j++){
               Grid::currentArray[i][j] = '.';
               Grid::newArray[i][j] = '.';

          }
       }
       Grid::print(currentArray);

   }
   //prints array given
   void Grid::print(char **pGrid){
   	for (int i = 0; i < height; i++)
   	{
   		for (int j = 0; j<width; j++){
   			cout << pGrid[i][j];
   			if (j<width-1){
   				cout << ' ';
   			}
   		}
   		cout << endl;
   	}
   	cout << "Generation: "<< generation << endl;
   }
   //creates random grid with random X's based on density
   void Grid::randomGrid(double percentPop){
   	//calculation for density
   	int availables = width * height * percentPop;
   	int randY;
   	int randX;
   	//randomly assigns X in array
   	while (availables > 0) {
   		randY = (rand() % height);
   		randX = (rand() % width);
   		if (currentArray[randY][randX] == '.'){
   				currentArray[randY][randX] = 'X';
   				availables--;
   		}
   	}

   }

   //simulates classic mode
   void Grid::classicSimulator(){
   	Grid::print(currentArray);
   	generation++;
   	int counter = 0;
   	//sets new array to empty
   	for(int i = 0; i < height; i++){
   		for (int j = 0; j < width; j++){
   			Grid::newArray[i][j] = '.';
   		}
   	}
   	//searches for neighbors to calculate what will occur in simulation based on classic rules
   	for (int y = 0; y < height; y++){
   		for (int x = 0; x < width; x++){
   			if(x==0&&y==0){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   			}
   			else if (x==0&&y<height-1){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   			}
   			else if (y==0&&x<width-1){
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   			}
   			else if (y<height-1&&x<width-1){
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x-1] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   			}
   			//rules based on neighbors
   			if (counter == 1 | counter == 0){
   			newArray[y][x] = '.';
   		}
   			if (counter == 2){
   				newArray[y][x] = currentArray[y][x];
   			}
   			if (counter == 3){
   				newArray[y][x] = 'X';
   			}
   			if (counter > 3){
   				newArray[y][x] = '.';
   			}

   			counter = 0;

   		}

   	}
   	//prints array
   		Grid::print(newArray);
   		//sets current to new array
   		for(int i = 0; i < height; i++){
   			for (int j = 0; j < width; j++){
   			currentArray[i][j] = newArray[i][j];
   		}
   	}

   }
   //same as classic but with different if rules
   void Grid::mirrorSimulator(){
   	Grid::print(currentArray);
   	generation++;
   	int counter = 0;
   	for(int i = 0; i < height; i++){
   		for (int j = 0; j < width; j++){
   			Grid::newArray[i][j] = '.';
   		}
   	}
   	//more in depth if rules allowing to bounce off edge and count multiples
   	for (int y = 0; y < height; y++){
   		for (int x = 0; x < width; x++){
   			if(x==0&&y==0){
   				if(currentArray[y][x] == 'X') counter = counter + 3;
   				if(currentArray[y][x+1] == 'X') counter = counter + 2;
   				if(currentArray[y+1][x] == 'X') counter = counter + 2;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   			} else if (x==0&&y==height-1){
   				if(currentArray[y][x] == 'X') counter = counter + 3;
   				if(currentArray[y][x+1] == 'X') counter = counter + 2;
   				if(currentArray[y-1][x] == 'X') counter = counter + 2;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   			} else if (x<width-1&&y==height-1){
   				if(currentArray[y][x] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter = counter + 2;
   				if(currentArray[y][x-1] == 'X') counter = counter + 2;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x-1] == 'X') counter++;
   			} else if (y==0&&x==width-1){
   				if(currentArray[y][x] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter = counter + 2;
   				if(currentArray[y][x-1] == 'X') counter = counter + 2;
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   			} else if (y<height-1&&x==width-1){
   				if(currentArray[y][x] == 'X') counter++;
   				if(currentArray[y+1][x] == 'X') counter = counter + 2;
   				if(currentArray[y-1][x] == 'X') counter = counter + 2;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   				if(currentArray[y-1][x-1] == 'X') counter++;
   			} 
   			else if (x==0&&y<height-1){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   			}
   			else if (y==0&&x<width-1){
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   			}
   			else if (y<height-1&&x<width-1){
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x-1] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   			}
   			
   			if (counter == 1 | counter == 0){
   			newArray[y][x] = '.';
   		}
   			if (counter == 2){
   				newArray[y][x] = currentArray[y][x];
   			}
   			if (counter == 3){
   				newArray[y][x] = 'X';
   			}
   			if (counter > 3){
   				newArray[y][x] = '.';
   			}

   			counter = 0;

   		}

   	}
   		Grid::print(newArray);

   		for(int i = 0; i < height; i++){
   			for (int j = 0; j < width; j++){
   			currentArray[i][j] = newArray[i][j];
   		}
   	}

   }
   //same as other game modes with different if statements
   void Grid::doughnutSimulator(){
   	Grid::print(currentArray);
   	generation++;
   	int counter = 0;
   	for(int i = 0; i < height; i++){
   		for (int j = 0; j < width; j++){
   			Grid::newArray[i][j] = '.';
   		}
   	}
   	//allows neighbors to be counted if they "wrap" around the edge
   	for (int y = 0; y < height; y++){
   		for (int x = 0; x < width; x++){
   			if(x==0&&y==0){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y][width-1] == 'X') counter++;
   				if(currentArray[height-1][x] == 'X') counter++;
   				if(currentArray[height-1][width-1] == 'X') counter++;
   			} else if (x==0&&y==height-1){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   				if(currentArray[y][width-1] == 'X') counter++;
   				if(currentArray[y-1][width-1] == 'X') counter++;
   			} else if (x<width-1&&y==height-1){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x-1] == 'X') counter++;
   				if(currentArray[0][x] == 'X') counter++;
   				if(currentArray[0][x+1] == 'X') counter++;
   				if(currentArray[0][x-1] == 'X') counter++;
   			} else if (y==0&&x==width-1){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[height-1][x] == 'X') counter++;
   				if(currentArray[0][x] == 'X') counter++;
   			} else if (y<height-1&&x==width-1){
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   				if(currentArray[y-1][x-1] == 'X') counter++;
   				if(currentArray[y][0] == 'X') counter++;
   				if(currentArray[y+1][0] == 'X') counter++;
   				if(currentArray[y-1][0] == 'X') counter++;
   			} 
   			else if (x==0&&y<height-1){
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   				if(currentArray[y][width-1] == 'X') counter++;
   				if(currentArray[y+1][width-1] == 'X') counter++;
   				if(currentArray[y-1][width-1] == 'X') counter++;
   			}
   			else if (y==0&&x<width-1){
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   				if(currentArray[height-1][x] == 'X') counter++;
   				if(currentArray[height-1][x-1] == 'X') counter++;
   				if(currentArray[height-1][x+1] == 'X') counter++;
   			}
   			else if (y<height-1&&x<width-1){
   				if(currentArray[y+1][x] == 'X') counter++;
   				if(currentArray[y-1][x] == 'X') counter++;
   				if(currentArray[y+1][x+1] == 'X') counter++;
   				if(currentArray[y+1][x-1] == 'X') counter++;
   				if(currentArray[y-1][x+1] == 'X') counter++;
   				if(currentArray[y-1][x-1] == 'X') counter++;
   				if(currentArray[y][x+1] == 'X') counter++;
   				if(currentArray[y][x-1] == 'X') counter++;
   			}
   			
   			if (counter == 1 | counter == 0){
   			newArray[y][x] = '.';
   		}
   			if (counter == 2){
   				newArray[y][x] = currentArray[y][x];
   			}
   			if (counter == 3){
   				newArray[y][x] = 'X';
   			}
   			if (counter > 3){
   				newArray[y][x] = '.';
   			}

   			counter = 0;

   		}

   	}
   		Grid::print(newArray);

   		for(int i = 0; i < height; i++){
   			for (int j = 0; j < width; j++){
   			currentArray[i][j] = newArray[i][j];
   		}
   	}

   }
     
