#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int row = 30, col = 30; // Initialization and Declaration
int rules_for_alive(char game_of_life[row][col], int l, int m); // Function prototype to implement the rules for game of life
string get_output_file_name(); // Function prototype to get the name of the output file from the user
void fill_with_blankspace(char array[row][col]); // Function prototype for filling an array with whitespaces(to simulate 'dead' cells)
void print_array_to_file(char array[row][col], string output_file_name); // Function prototype for printing the contents of array to a text file
void print_to_file(int i, string output_file_name); // Function prototype for printing to a text file
void copy_to_original_array(char array[row][col], char temp_array[row][col]); // Function prototype for copying the contents of the temporary array to the original array
void read_from_file(char array[row][col], char temp_array[row][col], int& generations, int& max_x, int& max_y, int& min_x, int& min_y); // Function prototype to read initial values for game_of_life array from a text file
void find_max_min(int x, int y, int& max_x, int& max_y, int& min_x, int& min_y); // Function prototype to find the extreme values of the x and y coordinates of 'alive' cells
int main()
{
	int generations, max_x, max_y, min_x, min_y; // Declaration
	char game_of_life[row][col], temp_game_of_life[row][col]; // Initialization and Declaration
	fill_with_blankspace(game_of_life); // Initializing  game_of_life array with blank whitespaces (aka dead cells)
	fill_with_blankspace(temp_game_of_life); // Initializing  temporary game_of_life array with blank whitespaces (aka dead cells)
	read_from_file(game_of_life, temp_game_of_life, generations, max_x, max_y, min_x, min_y); // Reading Initial values for game_of_life array from text file
	string output_file_name = get_output_file_name(); // Storing the input of the output file name from the user
	for (int i = 1; i <= generations; i++) // Implementing 'for' loop up till the generations specified in the text file
	{
		print_to_file(i,output_file_name); // Printing what generation # is being outputted to the text file
		print_array_to_file(game_of_life,output_file_name); // Printing the contents of the game_of_life array to the text file
		for (int l = min_x - 3; l < max_x + 3; l++) // Iterating only between the extreme (minimum and maximum) values, minus (in the case of minimum) and plus (in the case of maximum) 3, of the 'rows' 
		{                                           // of the 'alive' cells in the 2D array 'game_of_life'
			for (int m = min_y - 3; m < max_x + 3; m++) // Iterating only between the extreme (minimum and maximum) values, minus (in the case of minimum) and plus (in the case of maximum) 3, of the 
			{                                           // 'columns' of the 'alive' cells in the 2D array 'game_of_life'
				if ((game_of_life[l][m]) == '*') // Checking if the specific cell is 'alive' (i-e has a value of '*')
				{

					if (rules_for_alive(game_of_life, l, m) != 2 && rules_for_alive(game_of_life, l, m) != 3) // If the cell is 'alive', checks whether the number of neighbouring cells that are alive
					{                                                                                         // are equal to 2 or 3
						temp_game_of_life[l][m] = ' '; // If the number of neighbouring cells that are alive are not equal to 2 or 3, that specific cell is 'killed off' (i-e is given a whitespace)
					}
				}
				else // If the cell is not 'alive', that means it must be 'dead'
				{
					if (rules_for_alive(game_of_life, l, m) == 3) // If the cell is 'dead', checks whether the number of neighbouring cells are equal to 3
					{
						temp_game_of_life[l][m] = '*'; // If the number of neighbouring cells are equal to 3, that specific cell is 'brought to life' (i-e given a value of '*')
						find_max_min(l, m, max_x, max_y, min_x, min_y); // Checking if the new 'alive' cell has extreme (minimum or maximum) x or y coordinates among the rest of the alive cells.
					}                                                   // If so, updates the new extreme x and y coordinates, so that the next loop will only iterate between the minimum and the maximum
				}                                                       // value, hence making the program more efficient
			}
		}
		copy_to_original_array(game_of_life, temp_game_of_life); // Copying contents of temporary game_of_life array to the original game_of_life array
	}
	return 0;
}

// DEFINING FUNCTIONS FROM HERE ON

void fill_with_blankspace(char array[row][col]) // Function to fill a 2D array with zeroes
{
	for (int i = 0; i < row; i++) // Iterating through the 'rows' of the 2D array
	{
		for (int j = 0; j < col; j++) // Iterating through the 'columns' of the 2D array
		{
			array[i][j] = ' '; // Setting the element in that particular location in the 2D array to a blank whitespace
		}
	}
}
string get_output_file_name() // Function to get the name of the output file from the user
{
	string output_file_name; // Declaration
	cout << "\n\nWhat would you like the name of the output text file to be\n\n"; // Asking the user to input the name of the text file that the game_of_life array is going to be printed to
	getline(cin, output_file_name); // Taking input of the name of the text file
	if (output_file_name.find(".txt") == std::string::npos) // Checking if the user did not include the file extension of text files, txt, at the end of the file name, either intentionally or by accidnet
	{
		cout << "\nYou did not include the file extension(.txt) at the end, so it has been added automatically\n"; // If the user did not include .txt at the end of the file name, informs the user of this,
		output_file_name += ".txt";                                                                                // and automatically adds .txt at the end of the file name
	}
	return output_file_name; // Returning the name of the output text file
}
int rules_for_alive(char game_of_life[row][col], int l, int m) // Function to count the number of 'alive' neighbouring cells for a particular cell
{
	int count = 0; // Initializing the number of 'alive' neighbouring cells to '0'
	// The following 32 lines of code check whether the neighbouring cells (8 in total) for a particular cell are 'alive'. If a neighbouring cell is alive, increments the number of 'alive' cells by 1
	if (game_of_life[l - 1][m - 1] == '*') // Checking if the top-left cell is 'alive'
	{
		count++;
	}
	if (game_of_life[l][m - 1] == '*') // Checking if the left cell is 'alive'
	{
		count++; // If that cell is alive, increments the total number of 'alive' cells by 1
	}
	if (game_of_life[l + 1][m - 1] == '*') // Checking if the bottom-left cell is 'alive'
	{
		count++; // If that cell is alive, increments the total number of 'alive' cells by 1
	}
	if (game_of_life[l - 1][m] == '*') // Checking if the top cell is 'alive'
	{
		count++; // If that cell is alive, increments the total number of 'alive' cells by 1
	}
	if (game_of_life[l + 1][m] == '*') // Checking if the bottom cell is 'alive'
	{
		count++; // If that cell is alive, increments the total number of 'alive' cells by 1
	}
	if (game_of_life[l - 1][m + 1] == '*') // Checking if the top-right cell is 'alive'
	{
		count++; // If that cell is alive, increments the total number of 'alive' cells by 1
	}
	if (game_of_life[l][m + 1] == '*') // Checking if the right cell is 'alive'
	{
		count++; // If that cell is alive, increments the total number of 'alive' cells by 1
	}
	if (game_of_life[l + 1][m + 1] == '*') // Checking if the bottom-right cell is 'alive'
	{
		count++; // If that cell is alive, increments the total number of 'alive' cells by 1
	}
	return count; // Returning the total number of 'alive' neighbours for that particular cell
}
void print_to_file(int i, string output_file_name) // Function to output to a text file what generation # is being outputted to the text file
{
	fstream print_to_file; // Declaring a variable to handle the text file
	print_to_file.open(output_file_name, ios::app); // Opening the text file, and pointing the said variable to a text file path to append the said text file
	print_to_file << "\n\nDISPLAYING GRID FOR GENERATION # " << i << "\n\n"; // Outputting to the text file what generation # is being outputted to it
	print_to_file.close(); // Closing the text file
}
void print_array_to_file(char array[row][col], string output_file_name) // Function to output the contents of an array to a text file
{
	fstream printarray; // Declaring a variable to handle that text file
	printarray.open(output_file_name, ios::app); // Opening the text file, and pointing the said variable to a text file path to append the said text file
	printarray << "\n"; // Outputting an empty line to the text file
	for (int i = 0; i < row; i++) // Iterating through the 'rows' of the 2D array
	{
		for (int j = 0; j < col; j++) // Iterating through the 'columns' of the 2D array
		{
			printarray << array[i][j]; // Outputting the contents of the 2D array at that particular location to the text file
		}
		printarray << "\n"; // Outputting an empty line to the text file
	}
	printarray.close(); // Closing the text file
}
void copy_to_original_array(char array[row][col], char temp_array[row][col]) // Function to copy an arrays contents to another array
{
	for (int i = 0; i < row; i++) // Iterating through the 'rows' of both the 2D arrays
	{
		for (int j = 0; j < col; j++) // Iterating through the 'columns' of both the 2D arrays
		{
			array[i][j] = temp_array[i][j]; // Copying an element at that particular location of a 2D array to the same location of another 2D array
		}
	}
}
void read_from_file(char array[row][col], char temp_array[row][col], int& generations, int& max_x, int& max_y, int& min_x, int& min_y) // Function to get a text file name from the user, and to read the 
{                                                                                                                                     // initial values for the game_of_life array from that text file
	fstream input_file; // Declaring a variable to handle the text file
	int alive_cells, x, y; // Declaring variables for number of alive cells, and the 'x' and 'y' coordinates of the alive cells. This data is already given in the text file that we're reading from
	string filename; // Declaring a variable to store the name of the text file, that is to be taken from the user
	cout << "Input file name (including file extension), from which you want to read the initial values for the array\n" // Asking the user to input the name of the text file
		 << "You may enter the path of the file as well\n\n";                                                            // The user may enter the path of the file as well
	getline(cin, filename); // Getting the input of the file name from the user
	input_file.open(filename, ios::in); // Opening the text file, and pointing the said variable to a text file path to append the said text file
	if (!input_file) // Checking if the file name that the user provided was able to be opened
	{
		cout << "\n\nERROR\n" // If the file could not be opened, informs the user of it
			<< "File could not be opened. Please close the program and try again\n\n";
		exit(0); // Exiting the console
	}
	else
	{
		cout << "\n\nFile opened successfully\n"; // If the file was able to be opened, informs the user of it
	}
	input_file >> generations >> alive_cells; // Reads the data for the number of generations and the number of 'alive' cells from the text file
	max_x = -99, max_y = -99, min_x = row + 3, min_y = col + 3; // Initializing the maximum and minimum coordinates of 'alive' cells
	for (int i = 0; i < alive_cells; i++) // Implementing 'for' loop up till the number of alive cells
	{
		input_file >> x; // Reading the 'x' coordinate for the 'alive' cell from the text file
		if (x > max_x) // Checking if the 'x' coordinate of this alive cell is greater than the maximum 'x' coordinate of the 'alive' cells
		{
			max_x = x; // If it is greater than the maximum value, assigns this new 'x' coordinate as the new maximum 'x' coordinate of the 'alive' cells
		}
		if (x < min_x && x >= 0) // Checking if the 'x' coordinate of this alive cell is lesser than the minimum 'x' coordinate of the 'alive' cells
		{
			min_x = x; // If it is lesser than the minimum value, assigns this new 'x' coordinate as the new minimum 'x' coordinate of the 'alive' cells
		}
		input_file >> y; // Reading the 'y' coordinate for the 'alive' cell from the text file
		if (y > max_y) // Checking if the 'y' coordinate of this alive cell is greater than the maximum 'y' coordinate of the 'alive' cells
		{
			max_y = y; // If it is greater than the maximum value, assigns this new 'y' coordinate as the new maximum 'x' coordinate of the 'alive' cells
		}
		if (y < min_y && y >= 0) // Checking if the 'y' coordinate of this alive cell is lesser than the minimum 'y' coordinate of the 'alive' cells
		{
			min_y = y; // If it is lesser than the minimum value, assigns this new 'y' coordinate as the new minimum 'x' coordinate of the 'alive' cells
		}
		array[x][y] = '*'; // Setting the particular cell in the given 'x' and 'y' coordinates in the game_of_life array to 'alive' (i-e given a value of '*')
		temp_array[x][y] = '*'; // Setting the particular cell in the given 'x' and 'y' coordinates in the temp_game_of_life array to 'alive' (i-e given a value of '*')
	}
	input_file.close(); // Closing the text file
}
void find_max_min(int x, int y, int& max_x, int& max_y, int& min_x, int& min_y) // Function to find the extreme values of the x and y coordinates of 'alive' cells, so that the loop can only iterate
{                                                                               // between extreme values of the array, and not the whole grid. This improves the program's efficiency
	if (x > max_x) // Checking if the 'x' coordinate of this alive cell is greater than the maximum 'x' coordinate of the 'alive' cells
	{
		max_x = x; // If it is greater than the maximum value, assigns this new 'x' coordinate as the new maximum 'x' coordinate of the 'alive' cells
	}
	if (x < min_x) // Checking if the 'x' coordinate of this alive cell is lesser than the minimum 'x' coordinate of the 'alive' cells
	{
		min_x = x; // If it is lesser than the minimum value, assigns this new 'x' coordinate as the new minimum 'x' coordinate of the 'alive' cells
	}
	if (y > max_y) // Checking if the 'y' coordinate of this alive cell is greater than the maximum 'y' coordinate of the 'alive' cells
	{
		max_y = y; // If it is greater than the maximum value, assigns this new 'y' coordinate as the new maximum 'x' coordinate of the 'alive' cells
	}
	if (y < min_y) // Checking if the 'y' coordinate of this alive cell is lesser than the minimum 'y' coordinate of the 'alive' cells
	{
		min_y = y; // If it is lesser than the minimum value, assigns this new 'y' coordinate as the new minimum 'x' coordinate of the 'alive' cells
	}
}