//<Multi-Array Assignment> -- Simulate Battleship
//CSIS 111-B04
//<Sources if necessary>
//Include statements

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

//Global declarations: Constants and type definitions only -- no variables
ifstream inData;
ofstream outData;

//Function prototypes
//Copies the game board to a different file for game use, preserving the original board, defined on lines 90-119
void GameInitializer();
//Takes inputed coordinates and checks if there is a ship tile there, defined on lines 120-196
void Fire();
//Checks if all the ships are sunk, defined on lines 197-239
bool FleetSunk();

int main()
{
	//In cout statement below SUBSTITUTE your name and lab number
	cout << "Aaron Tindall -- Lab 7" << endl << endl;

	//Variable declarations
	//C Stands for collum to allow for the game board to be put in a 2D array
	int c;
	//R stands for row to allow for the game board to be put in a 2D array
	int r;
	//Win condition, set to false when the game is won
	bool keepLooping = true;
	//Stores the game board for the final print out
	char gameboard[25][25];
	//Program logic

	//see line 18
	GameInitializer();

	//user interaction
	cout << "Welcome, general. We're glad you're here. The enemy is jamming our scanners, but they have ships out there that are too close for comfort." << endl;
	cout << "We have torpedos ready and waiting to strike, just give us the word." << endl << endl;

	//keeps the game running as long as there are still ships on the board
	while (keepLooping)
	{
		//see line 20
		Fire();
		//Ends the game if there are no ships left
		keepLooping = FleetSunk();
	}

	//user interaction
	cout << "Well done, general. The enemy fleet is no more. We just recieved a satalite image of the battlefield, sending it to you now." << endl;

	//copies the final map state to the 2D array gameboard for printing
	inData.open("DoNotEdit.txt");
	for (r = 0; r < 25; r++)
	{
		for (c = 0; c < 25; c++)
		{
			inData >> gameboard[r][c];
		}
	}
	inData.close();

	//prints the map to the console one coordinate at a time
	for (r = 0; r < 25; r++)
	{
		for (c = 0; c < 25; c++)
		{
			cout << gameboard[r][c] << " ";
		}
		cout << endl;
	}

	//user interaction
	cout << endl;
	cout << "An H marks a hit, an X marks a miss" << endl;

	//Closing program statements
	system("pause");
	return 0;
}
//Function definitions
void GameInitializer()
{
	//serves as the bridge between the two files
	char gameboard[25][25];
	int r;
	int c;

	//Copies the user made board to the 2D array gameboard
	inData.open("Battleship.txt");
	for (r = 0; r < 25; r++)
	{
		for (c = 0; c < 25; c++)
		{
			inData >> gameboard[r][c];
		}
	}
	inData.close();

	//Copies the 2D array to the file the game will use as the live map
	outData.open("DoNotEdit.txt");
	for (r = 0; r < 25; r++)
	{
		for (c = 0; c < 25; c++)
		{
			outData << gameboard[r][c];
		}
		outData << endl;
	}
	outData.close();
}
void Fire()
{
	//X coordinate in the 2D array, aka collumn number, for the torpedo launch
	int x;
	//Y coordinate in the 2D array, aka row number, for the torpedo launch
	int y;
	//Stores map for manipulation
	char gameboard[25][25];
	//Row counter
	int r;
	//Collumn counter
	int c;

	//Copies live map to the 2D array
	inData.open("DoNotEdit.txt");
	for (r = 0; r < 25; r++)
	{
		for (c = 0; c < 25; c++)
		{
			inData >> gameboard[r][c];
		}
	}
	inData.close();

	//User interaction
	cout << "Enter coordinates in the form of x y, general. Remember, the map is 25x25, left to right, top to bottom." << endl;
	cout << "Ex: 4 25" << endl;
	//Gets coordinates for torpedo
	cin >> x >> y;
	//Converts coordinates to the language of 2D array
	x = x - 1;
	y = y - 1;
	//Checks if coordinates are valid
	if (x < 0 || y < 0 || x > 24 || y > 24)
	{
		cout << "Those coordinates are off the map general, we have good intel there are no ships there.";
		Fire();
	}
	else
	{
		//Checks if there is a ship tile at the coordinates
		if (gameboard[y][x] == '#')
		{
			cout << "HIT" << endl << endl;
			gameboard[y][x] = 'H';
		}
		//Checks if the coordinates were already hit
		else if (gameboard[y][x] == 'H')
		{
			cout << "HIT AGAIN" << endl << endl;
		}
		//Checks if there is a water tile tile at the coordinates
		else if (gameboard[y][x] == '~')
		{
			cout << "MISS" << endl << endl;
			gameboard[y][x] = 'X';
		}
		//Safety else just in case something weird/unexpected happens
		else
		{
			cout << "Something went seriously wrong, general. Make sure you give us proper coordinates so we can win this battle!" << endl;
		}
	}

	//Sends updated board to the live map
	outData.open("DoNotEdit.txt");
	for (r = 0; r < 25; r++)
	{
		for (c = 0; c < 25; c++)
		{
			outData << gameboard[r][c];
		}
		outData << endl;
	}
	outData.close();

}
bool FleetSunk()
{
	//Row counter
	int r;
	//Collumn counter
	int c;
	//Row counter
	int l;
	//Collumn counter
	int m;
	//Stores map for manipulation
	char gameboard[25][25];

	//Copies live game board to the 2D array for manipulation
	inData.open("DoNotEdit.txt");
	for (r = 0; r < 25; r++)
	{
		for (c = 0; c < 25; c++)
		{
			inData >> gameboard[r][c];
		}
	}
	inData.close();

	//Checks if there is at least 1 ship tile left
	for (l = 0; l < 25; l++)
	{
		for (m = 0; m < 25; m++)
		{
			if (gameboard[l][m] == '#')
			{
				return true;
			}
		}
	}

	//If it could not find a ship tile on any coordinate, it sends the win condition
	if (l == 25 && m == 25 && gameboard[l][m] != '#')
	{
		cout << "The fleet was destroyed!" << endl;
		return false;
	}
}