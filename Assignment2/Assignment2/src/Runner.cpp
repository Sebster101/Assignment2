#include "Grid.h"
#include "Runner.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;
//main method for handling Grid class
Runner::Runner(){
	//introduces game to user
	decider = 0;
	cout << "Welcome to game of life!" << endl;
	cout << "How would you like your board generated" << endl;
	//asks for random file or input
	cout << "1. Random" << endl;
	cout << "2. Input File" << endl;
	cin >> decider;
	//if statement for random generation
	if (decider == 1){
		cout << "Enter height of the board" << endl;
		cin >> y;
		cout << "Enter width of the board" << endl;
		cin >> x;
		//creates empty grid with user dimensions
		Grid g(x,y);
		g.populate();
		//asks for density from 0 - 100 percent then populates
		cout << "Enter density from 0-100" << endl;
		cin >> density;
		density = density / 100;
		g.randomGrid(density);
		//asks user for gamemode
		cout << "What game mode would you like to play?" << endl;
		cout << "1. Classic" << endl;
		cout << "2. Mirror" << endl;
		cout << "3. Doughnut" << endl;
		cin >> decider;
		//classic game mode
		while (decider == 1){
				cout << "Classic Mode" << endl;
				cout << "Enter 1 to generate a new generation or type 0 to exit" << endl;
				cin >> decider;
				g.classicSimulator();
			}
		//mirror
		while (decider == 2){
				cout << "Mirror Mode" << endl;
				cout << "Enter 2 to generate a new generation or type 0 to exit" << endl;
				cin >> decider;
				g.mirrorSimulator();
			}
		//doughnut
		while (decider == 3){
				cout << "Doughtnut Mode" << endl;
				cout << "Enter 3 to generate a new generation or type 0 to exit" << endl;
				cin >> decider;
				g.doughnutSimulator();
			}
		//invalid input
		while (decider != 0){
			cout << "Invalid Entry please reenter" << endl;
			cout << "What game mode would you like to play?" << endl;
			cout << "1. Classic" << endl;
			cout << "2. Mirror" << endl;
			cout << "3. Doughnut" << endl;
			cin >> decider;
		}
		//for file input
	} else if (decider == 2){
		cout << "Enter height of the board" << endl;
		cin >> y;
		cout << "Enter width of the board" << endl;
		cin >> x;
		Grid g(x,y);
		g.populate();
		//asks user for filename
		cout << "Enter file name including extension" << endl;
		cin >> fname;
		g.mapGrid(fname);
		cout << "What game mode would you like to play?" << endl;
		cout << "1. Classic" << endl;
		cout << "2. Mirror" << endl;
		cout << "3. Doughnut" << endl;
		cin >> decider;
		//classic mode
		while (decider == 1){
				cout << "Classic Mode" << endl;
				cout << "Press enter 1 to generate a new generation or type 0 to exit" << endl;
				cin >> decider;
				g.classicSimulator();
			}
		//mirror
		while (decider == 2){
				cout << "Mirror Mode" << endl;
				cout << "Press enter 2 to generate a new generation or type 0 to exit" << endl;
				cin >> decider;
				g.mirrorSimulator();
			}
		//doughnut
		while (decider == 3){
				cout << "Doughtnut Mode" << endl;
				cout << "Press enter 3 to generate a new generation or type 0 to exit" << endl;
				cin >> decider;
				g.doughnutSimulator();
			}
		//invalid input
		while (decider != 0){
			cout << "Invalid Entry please reenter" << endl;
			cout << "What game mode would you like to play?" << endl;
			cout << "1. Classic" << endl;
			cout << "2. Mirror" << endl;
			cout << "3. Doughnut" << endl;
			cin >> decider;
		}
		//catches invalid input for first question of input method
	} else {
		cout << "Invalid entry please try again" << endl;
	}
}