#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
//#include <cctype>
#include <vector>
#include "strutils.h"
using namespace std;
//The purpose of this homework is to reach given informations within text files, decomposing and assigning them to appropriate values, and using that values to replace given words to nxm matricies. 
//From line 14 to 441, used functions are lisetd and implemented. After the 440th line the main function is located. 
//By Bengisu Ozdemir.

//printing the matrix:
void PrintMatrix(const vector<vector<char>> & mat)
{
	for (int j = 0; j < mat.size(); j++)
	{
		for (int k = 0; k < mat[0].size(); k++)
		{
			cout << setw(4) << mat[j][k];
		}
		cout << endl;
	}
}
//checks the availability of x and y locations, if availabe returns true, else returns false:
bool checkInitial(vector<vector<char>> mat, int x, int y)
{
	if(x >=0 && y >= 0 && mat[x][y] == '-')
		return true;
	else
		return false;
}

//checks the range of the coordinates, if in rage returns true:
bool inLimit(vector<vector<char>> mat, int x, int y)
{
	if (x >= 0 && x < mat.size() && y >= 0 && y < mat[0].size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//the function to go to right direction, uptades the matrix with the appropriate chararacer(s):
void Goright(vector<vector<char>> & mat, string s, int &x, int &y, int l, bool &check)
{
	if (inLimit(mat, x, y) && y + 1 < mat[0].size() && mat[x][y + 1] == '-')
	{
		y++;
		mat[x][y] = s[l];
		check = true;
	}
}

//the function to go to left direction, uptades the matrix with the appropriate chararacer(s):
void Goleft(vector<vector<char>> & mat, string s, int &x, int &y, int l, bool &check)
{

	if (inLimit(mat, x, y) && y - 1 >= 0 && mat[x][y - 1] == '-')
	{
		y--;
		mat[x][y] = s[l];
		check = true;
	}
}

//the function to go to up direction, uptades the matrix with the appropriate chararacer(s):
void Goup(vector<vector<char>> & mat, string s, int &x, int &y, int l, bool &check)
{

	if (inLimit(mat, x, y) && x - 1 >= 0 && mat[x - 1][y] == '-')
	{
		x--;
		mat[x][y] = s[l];
		check = true;
	}
}

//the function to go to down direction, uptades the matrix with the appropriate chararacer(s):
void Godown(vector<vector<char>> & mat, string s, int &x, int &y, int l, bool &check)
{

	if (inLimit(mat, x, y) && x + 1 < mat.size() && mat[x + 1][y] == '-')
	{
		x++;
		mat[x][y] = s[l];
		check = true;
	}
}

//replacing words in CW orientation: 
void replaceCW(vector<vector<char>> & mat, string d, string s, int x, int y, int row, int col)
{
	int startingIndex_x = x, startingIndex_y = y;
	vector<vector<char>> backupMat = mat;								//creating a back-up matrix to use when there is a problem exist during replacement in terms of the availability of the coordinates.
	bool success = true;
	if(checkInitial(mat, x, y))
	{
		mat[x][y] = s[0];												//since there is no problem with checkInitial function, replace the first letter.
		bool check;														//initializing a bool type variable to use and afterwards change within functions.
		if (d == "r")
		{
			for (int a = 1; a < s.length(); a++)						//since the first letter has ben replaced continue with the second letter (i = 1)
			{
				check = false;											//initialize check to false. 
				Goright(mat, s, x, y,a,check);
				if (check) { continue; }
				Godown(mat, s, x, y,a,check);
				if (check) { continue; }								//the purpose of 106-113 is tyring to implement the function of desired direction, if successful continue to increase letters of the word,
				Goleft(mat, s, x, y,a,check);							//if not try to implement other functions of directions until the end of the last direction of the orientation. 
				if (check) { continue; }								//Finally, ,f there is a problem with the replacement of the word, return to the backup matrix, equate success to false, and break the loop. 
				Goup(mat, s, x, y,a,check);								//Abovementioned methods are being used for every orientation and direction.
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success) 
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			PrintMatrix(mat);											//Printing the final matrix via PrintMatrix function.
		}
		
		else if(d == "l")
		{
			//For information go to line 97-131.
			for (int a = 1; a < s.length(); a++)
			{
				check = false;
				Goleft(mat, s, x, y, a, check);
				if (check) { continue; }
				Goup(mat, s, x, y, a, check);
				if (check) { continue; }
				Goright(mat, s, x, y, a, check);
				if (check) { continue; }
				Godown(mat, s, x, y, a, check);
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success) 
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			PrintMatrix(mat);
			
		}
		else if(d == "u")
		{
			//For information go to line 97-131.
			for (int a = 1; a < s.length(); a++)
			{
				check = false;
				Goup(mat, s, x, y, a, check);
				if (check) { continue; }
				Goright(mat, s, x, y, a, check);
				if (check) { continue; }
				Godown(mat, s, x, y, a, check);
				if (check) { continue; }
				Goleft(mat, s, x, y, a, check);
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success) 
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			PrintMatrix(mat);
		}
		else if (d == "d")
		{
			//For information go to line 97-131.
			for (int a = 1; a < s.length(); a++)
			{
				check = false;
				Godown(mat, s, x, y, a, check);
				if (check) { continue; }
				Goleft(mat, s, x, y, a, check);
				if (check) { continue; }
				Goup(mat, s, x, y, a, check);
				if (check) { continue; }
				Goright(mat, s, x, y, a, check);
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success)
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
			}
			PrintMatrix(mat);
		}
	}
	else
	{
		cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CW" << endl;
		PrintMatrix(mat);
	}
}

//replacing the words in CCW orientation, same comments(CW) are valid for this function, only change is the order of the functions that has been written:
void replaceCCW(vector<vector<char>> & mat, string d, string s, int x, int y, int row, int col)
{
	int startingIndex_x = x, startingIndex_y = y;
	vector<vector<char>> backupMat = mat;
	bool success = true;
	string or = "CCW";
	if(checkInitial(mat, x, y))
	{
		mat[x][y] = s[0];
		bool check;
		if (d == "r")
		{
			//For information go to line 97-131.
			for (int i = 1; i < s.length(); i++)
			{
				check = false;
				Goright(mat, s, x, y, i, check);
				if (check) { continue; }
				Goup(mat, s, x, y, i, check);
				if (check) { continue; }
				Goleft(mat, s, x, y, i, check);
				if (check) { continue; }
				Godown(mat, s, x, y, i, check);
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success) 
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}
			PrintMatrix(mat);
		}
		else if(d == "l")
		{
			//For information go to line 97-131.
			for (int i = 1; i < s.length(); i++)
			{
				check = false;
				Goleft(mat, s, x, y, i, check);
				if (check) { continue; }
				Godown(mat, s, x, y, i, check);
				if (check) { continue; }
				Goright(mat, s, x, y, i, check);
				if (check) { continue; }
				Goup(mat, s, x, y, i, check);
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success) 
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}	
			PrintMatrix(mat);
		}
		else if(d == "d")
		{
			//For information go to line 97-131.
			for (int i = 1; i < s.length(); i++)
			{
				check = false;
				Godown(mat, s, x, y, i, check);
				if (check) { continue; }
				Goright(mat, s, x, y, i, check);
				if (check) { continue; }
				Goup(mat, s, x, y, i, check);
				if (check) { continue; }
				Goleft(mat, s, x, y, i, check);
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success)
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}	
			PrintMatrix(mat);
		}
		else if (d == "u")
		{
			//For information go to line 97-131.
			for (int i = 1; i < s.length(); i++)
			{
				check = false;
				Goup(mat, s, x, y, i, check);
				if (check) { continue; }
				Goleft(mat, s, x, y, i, check);
				if (check) { continue; }
				Godown(mat, s, x, y, i, check);
				if (check) { continue; }
				Goright(mat, s, x, y, i, check);
				if (check) { continue; }
				mat = backupMat;
				success = false;
				break;
			}
			if (success)
			{
				cout << "\"" << s << "\"" <<" was put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}
			else
			{
				cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
			}	
			PrintMatrix(mat);
		}
	}
	else
	{
		cout << "\"" << s << "\"" <<" could not be put into the matrix with given starting point:  " << startingIndex_x << ", " << startingIndex_y << " direction: " << d << " " << "orientation: CCW" << endl;
		PrintMatrix(mat);
	}
}

//checking the line if it's valid:
bool lineCheck(string myString)
{
	int counter = 0;
	string s = "", word;
	istringstream sstr(myString);

	//take the words one by one and add blanks manually between words; thus, the lines will be the desired format. 
	while(sstr >> word)
	{
		s += word + " ";
	}
	StripWhite(s);				//erasing the excessive blanks before and after the sentence.

	//for every blank increase counter, at the end the value of counter equals to number of spaces:
	for (int i = 0; i < s.length(); i++)
	{
		if(s[i] == ' ')
		{
			counter++;
		}
	}
	if(counter == 4)			//when the counter equals to 4 that means there are 4 blanks in the sentence representing 5 words exist.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checking coordinates if positive:
bool coordinateCheck(int x, int y)
{
	if(x >= 0 && y>= 0)
	{
		return true;
	}
	return false;
}

//checking the coordinates wheter in range:
bool rangeCheck(int x, int y, int row, int col)
{
	if(x <= row-1 && y <= col-1)
	{
		return true;
	}
	return false;
}

//checking orientation whether CW or CCW:
bool orientationCheck(string o)
{
	if(o == "CW" || o == "CCW")
	{
		return true;
	}
	return false;
}

//ckecking the directions:
bool directionCheck(string d)
{
	if(d == "r" || d == "l" || d == "u" || d== "d")
	{
		return true;
	}
	return false;
}

//ckecking whether the charachters of a string is alphabethic:
bool charCheck(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if(isalpha(s[i]))
		{
			return true;
		}
	}
	return false;
}

//At the main file the variables in order to create and fill matrix are being initialized, the desired files are opened and after checking formats the appropriate functions are being called.
int main()
{
	ifstream input;
	string fileName;
	int row, col;                                  //assigning two integers called row and col which is for to determine the dimesions of the matrix
	cout << "Please enter the name of the file: ";
	cin >> fileName;
	input.open(fileName.c_str());

	// Checking if the file can be opened.
	while (input.fail())
	{
		cout << "File name is incorrect, please enter again: ";
		cin.clear();
		cin >> fileName;
		input.open(fileName.c_str());
	}

	// If there is no error while opening the file, continue from this part.
	if (!input.fail())
	{
		string line, lines;
		getline(input,line);
		istringstream strstream(line);
		strstream >> row >> col;													//decomposing the first line that is taken by getline and assigning this line one by one into row and col integers.
		

		//if there is something wrong with the values of row and col (eg. negative), then exterminate the code:
		if (!coordinateCheck(row, col))
		{
			cout << "Invalid number for row and/or column!" << endl;
			return 0;
		}
		vector<vector<char>> myMatrix(row, vector<char>(col, '-'));                //creating a vector of vector (a matrix) called myMatrix that has rowXcol dimesions and initializing all of the characters of matrix to '-'
		
		//starting to take other variables from other lines and executing the same process for all of them in a while loop.
		while(getline(input,lines))
		{
			string name, dir, or;					// name stands for the word that we are going to replace in matrix,"dir" represents direction, and "or" represents orientation.
			int x, y;								// "x" represents the value for x coordinate(row) and y represents the value for the y coordinate(col).
			istringstream str(lines);
			str >> name >> x >> y >> dir >> or;		// taking inputs one by one from the file and assigning them corresponding variables.

			//in order to variables to fit in desired formats, determined checks are done here:
			if (lineCheck(lines) && rangeCheck(x, y, row, col) && orientationCheck(or) && directionCheck(dir) && coordinateCheck(x, y))
			{
				
				if (or == "CW")
				{
					replaceCW(myMatrix, dir, name, x, y, row, col);				//Clockwise replacement:by using appropriate functions replacing the words within a matrix which is created by the values from the .txt files. (e.g. 6x6, 3x5, etc.)
				}
				else								// or == CCW
				{
					replaceCCW(myMatrix, dir, name, x, y, row, col);			////CounterClockwise replacement:by using appropriate functions replacing the words within a matrix which is created by the values from the .txt files. (e.g. 6x6, 3x5, etc.)
				}
			}
			else if(!lineCheck(lines))
			{
				cout << "Invalid line! Number of values is different than 5." << endl;
			}
			else if (!directionCheck(dir) && charCheck(dir))
			{
				cout << "Invalid input for direction! Direction: " << dir << endl;
			}
			else if(!coordinateCheck(x, y) || !rangeCheck(x, y, row, col))
			{
				cout << "Starting point is out of range! Point: " << x << ", " << y << endl;
			}
			else if(!orientationCheck(or) && lineCheck(lines))
			{
				cout << "Invalid input for orientation! Orientation: " << or << endl;
			}
			
		}
	}
	input.close();			//Closing the file and shoting down the program.
	return 0;
}
