#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Menu.h"

using namespace std;

// Shows Main Menu
void Menu::ShowMenu()
{
	cout << "******************" << endl;
	cout << "Welcome to Farkle!" << endl;
	cout << "******************" << endl;
	cout << "1. Play Game" << endl;
	cout << "2. Show Rules" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice: ";
}

// Shows Rules
void Menu::ShowRules()
{
	ifstream inputFile("Rules.txt"); // Open the file

	if (inputFile.is_open()) // Check if the file is open
	{
		string line;
		while (getline(inputFile, line)) // Read the file line by line
		{
			cout << line << endl; // Print the line
		}
		inputFile.close(); // Close the file
	}
	else
	{
		cout << "Unable to open file" << endl; // Print an error message
	}
	cout << endl;
	system("pause"); // Wait for user to press enter
}
