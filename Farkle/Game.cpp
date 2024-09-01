// This file is used to include all the necessary files for the game to run properly
// It includes the Player and Game classes
// It also includes the iostream, string, vector, random, and array libraries

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <array>

#include "Player.h"
#include "Game.h"
#include "Menu.h"

using namespace std;

#pragma region Inputs
// Clears the input stream
void Game::ClearInput()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Gets the input from the user
int Game::GetInput()
{
	unsigned int selection;
	while (!(cin >> selection))
	{
		ClearInput();
		cout << "Invalid input. Please enter a number: ";
	}

	ClearInput();
	return selection;

}
#pragma endregion

#pragma region Messages
// Shows the winner of the game
void Game::Congratulate(Player& player)
{
	system("cls");
	cout << "******************" << endl;
	cout << "Congratulations!" << endl;
	cout << "******************" << endl;
	cout << player.Name() << " won the game with a score of " << player.Score() << "!" << endl << endl;

	system("pause");
}

// Shows the final round message
void Game::FinalRound(Player& player)
{
	system("cls");
	cout << "******************" << endl;
	cout << "Final Round!" << endl;
	cout << "******************" << endl;
	cout << player.Name() << " has reached 10,000 points!" << endl;
	cout << "The other players will have one more turn." << endl;

	system("pause");
}

// Shows the dice that were kept
void Game::ShowDiceKept(array<int, 6>& diceKept)
{
	for (unsigned int i = 0; i < diceKept.size(); i++)
	{
		cout << "[" << (i + 1) << "]: " << diceKept[i];

		if (i != diceKept.size() - 1)
		{
			cout << ", ";
		}
	}

	cout << endl << endl;
}

// Shows the dice that were rolled
void Game::ShowDiceRolled(vector<int>& diceGroup)
{
	cout << "Dice Rolled: ";
	for (unsigned int i = 0; i < diceGroup.size(); i++)
	{
		cout << "| Dice " << (i + 1) << ": [" << diceGroup[i] << "] |" << endl;
	}
	cout << endl;
}

// Introduces the players
void Game::IntroducePlayers(vector<Player>& players)
{
	string playerNames;

	system("cls");

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (i == players.size() - 1)
		{
			playerNames += "and " + players[i].Name();
		}
		else
		{
			playerNames += players[i].Name() + ", ";
		}

		cout << "Welcome " << playerNames << "!" << endl << endl;

		system("pause");
	}
}
#pragma endregion

#pragma region Setup
// Prompts the user for the number of players
void Game::PromptNumberOfPlayers()
{
	system("cls");
	cout << "Enter the number of players: ";
}

// Sets the names of the players
void Game::SetPlayerNames(vector<Player>& players)
{
	system("cls");
	
	for (unsigned int i = 0; i < players.size(); i++)
	{
		string name;

		cout << "Enter the name of player " << i + 1 << ": ";

		cin >> name;

		ClearInput();

		players[i] = Player(name);
		

	}
}
#pragma endregion

#pragma region Game
// Counts the number of each die in the dice group
array<int, 6> Game::CountDice(vector<int>& diceGroup)
{
	array<int, 6> diceCount = { 0 };
	for (unsigned int i = 0; i < diceGroup.size(); i++)
	{
		diceCount[diceGroup[i] - 1]++;
	}
	return diceCount;
}

// Checks if the score is greater than or equal to 10,000
bool Game::CheckFor10k(int score)
{
	bool isOver10k = score >= 10000 ? true : false;

	return isOver10k;
}

// Check if the dice roll has any scoring dice
bool Game::ScoringDice(array<int, 6>& diceCount)
{
	// If there is a 1 or a 5, return true
	if (diceCount[0] >= 1 || diceCount[4] >= 1)
	{
		return true;
	}

	// If no 1 or 5, check for any triples
	for (unsigned int i = 1; i < diceCount.size(); i++)
	{
		if (i == 4) { i = 5; }

		if (diceCount[i] >= 3) { return true; }
	}

	// No scoring dice
	return false;
}

// Checks if the selection is a valid dice in the dice pool
bool Game::IsValid(unsigned int& selection, vector<int>& diceGroup)
{
	if (selection > 0 && selection <= diceGroup.size())
	{
		return true;
	}

	return false;
}

int Game::ScoreDice(vector<int>& diceGroup, int dice, array<int, 6>& diceCount, array<int, 6>& diceKept)
{
	dice -= 1;	// since using 0 based index for the dicegroup make it -1
	int score = 0;
	int diceValue = diceGroup[dice];

	// If there are 3 or more dice with the selected value, set aside 3 of the dice
	if (diceCount[diceValue - 1] >= 3)
	{
		int i = 0;
		while (i < 3)
		{
			for (unsigned int j = 0; j < diceGroup.size(); j++)
			{
				if (diceGroup[j] == diceValue)
				{
					diceGroup.erase(diceGroup.begin() + j); // Remove the selected dice from the diceGroup
					diceKept[diceValue - 1]++; // Increment the dice kept for this turn
					i++;
				}
			}
		}

		// if 3 1's were kept, the score is 1000, otherwise is 100x the die value
		score = diceValue == 1 ? 1000 : diceValue * 100;
	}
	else if (diceValue == 1 || diceValue == 5)
	{
		diceGroup.erase(diceGroup.begin() + dice);	// Remove selected dice from the diceGroup
		diceKept[diceValue - 1]++; // Incredment the dice kept for this turn

		// If dice is 1, score is 100, otherwise it's 50
		score = diceValue == 1 ? 100 : 50;
	}

	return score;
}


// Rolls the dice
void Game::RollDice(vector<int>& diceGroup)
{
	random_device rng;

	for (unsigned int i = 0; i < diceGroup.size(); i++)
	{
		diceGroup[i] = rng() % 6 + 1; // Creates a random number from 1 to 6
	}
}


// Gets the winner of the game
Player Game::GetWinner(vector<Player> players)
{
	Player winner = players[0];
	for (unsigned int i = 1; i < players.size(); i++)
	{
		if (players[i].Score() > players[i - 1].Score())
		{
			winner = players[i];
		}
	}
	return winner;
}
#pragma endregion

#pragma region Private Loops
// Main game loop
Player Game::Play()
{
	Player winner; // While this string is empty, the game will continue to loop
	int numberOfPlayers = 0; // variable for number of players
	int playerTurn = 0; // keeps track of players turn
	int firstTo10k = -1; // let's you know when a player reaches 10k
	int turnScore = 0; // The value the player has scored this turn

	PromptNumberOfPlayers();

	// Loop until players is at least 2
	while (!(numberOfPlayers > 1))
	{
		numberOfPlayers = GetInput();

		if (numberOfPlayers < 2)
		{
			cout << "Invalid number of players. Must be more than 1." << endl;
			cout << "Try again: ";
		}
	}
	
	vector<Player> players(numberOfPlayers); // generate a vector to hold Player objects based on number of players

	SetPlayerNames(players);

	IntroducePlayers(players);

	// Continue looping until a winner is declared
	while (winner.Name() == "")
	{
		// Return to first players turn if necessary
		if (playerTurn == players.size())
		{
			playerTurn = 0;
		}

		// The game is over if all players have had a turn after a player reaches 10k
		if (firstTo10k >= 0 && playerTurn == firstTo10k)
		{
			winner = GetWinner(players);
			continue;
		}

		// Run a turn for a player and put their score into the turnScore variable
		turnScore = Turn(players[playerTurn]);

		// If the player has not entered the game and they score more than 1000 points
		if (!players[playerTurn].InGame() && turnScore >= 1000)
		{
			players[playerTurn].SetInGame(); // put player in the game
		}

		// add turnscore to players score
		if (turnScore > 0)
		{
			players[playerTurn].AddScore(turnScore);
		}

		// Check if players score is over 10k
		if (firstTo10k == -1 && CheckFor10k(players[playerTurn].Score()))
		{
			FinalRound(players[playerTurn]);

			firstTo10k = playerTurn;
		}

		playerTurn++; // Send to next players turn
	}

	return winner;
}

// Turn loop
int Game::Turn(Player& player)
{
	vector<int> diceGroup(6); // New dice group of 6 dice
	array<int, 6> diceKept = { 0 }; // Set all dice kept values to 0
	array<int, 6> diceCount = { 0 }; // Variable to count dice values
	int turnScore = 0; // Running score for this turn
	bool farkle = false; // Determines if player has Farkled
	bool canPass = player.InGame(); // Determines if player can pass their turn
	bool canReroll = false; // Determines if player can reroll the dice
	bool hasPassed = false; // Determines when the player has passed their turn

	unsigned int selection = 1;

	while (!hasPassed)
	{
		// if player has set aside all dice
		if (diceGroup.size() == 0)
		{
			// populate diceGroup back to 6 dice
			for (int i = 0; i < 6; i++)
			{
				diceGroup.push_back(1);
			}
		}

		RollDice(diceGroup); // Roll the dice
		canReroll = false;
		canPass = false;

		// Allow player to set aside the rolled dice until they pass or reroll
		do
		{
			system("cls");
			cout << "*****************" << endl;
			cout << player.Name() << "'s Turn!" << endl;
			cout << "*****************" << endl;
			cout << player.Name() << "'s Score: " << player.Score() << endl;
			cout << "Turn Score: " << turnScore << endl << endl;

			ShowDiceRolled(diceGroup);
			ShowDiceKept(diceKept);

			diceCount = CountDice(diceGroup);

			// If the player has no scoring dice and they can't reroll
			if (!ScoringDice(diceCount) && !canReroll)
			{
				farkle = true; // The player has farkled
				selection = 0; // Automatically select to end their turn
				continue; // Skip the rest of the code in this loop
			}

			cout << "Enter the dice # you wish to keep. Triple values will automatically be kept." << endl;
			cout << "Enter 9 to reroll dice or 0 to end your turn." << endl;
			cout << "Selection: ";

			// If the dice group is empty, automatically reroll to generate 6 new dice, otherwise get the player's selection
			selection = diceGroup.size() == 0 ? 9 : GetInput();

			if (IsValid(selection, diceGroup))
			{
				// Add the dice value to turn score
				turnScore += ScoreDice(diceGroup, selection, diceCount, diceKept);

				canReroll = true; // Player has kept a die and can now reroll the dice

				// If the player is in the game or they have over 1000 points, the player can end their turn
				canPass = (player.InGame() || turnScore >= 1000) ? true : false;

			}
			// check if the player has selected a valid move, ending turn or rerolling dice
			else if ((selection == 0 && !canPass) || (selection == 9 && !canReroll))
			{
				string msg;

				system("cls");
				cout << "*****************" << endl;
				cout << "INVALID MOVE" << endl;
				cout << "*****************" << endl;

				msg = selection == 0 ? player.Name() + " cannot score out at this time!" : player.Name() + " cannot reroll at this time!";

				cout << msg << endl << endl;

				selection = 7;

				system("pause");
			}
		} while (selection > 0 && selection != 9);

		// Player selected to end their turn, then they have passed. Otherwise they're rolling dice
		hasPassed = selection == 0 ? true : false;
	}

	system("cls");
	cout << "*****************" << endl;
	cout << player.Name() << "'s TURN ENDS!" << endl;
	cout << "*****************" << endl;

	if (farkle)
	{
		cout << player.Name() << " has FARKLED!" << endl;
	}
	else
	{
		cout << player.Name() << " has scored " << turnScore << " points this turn!" << endl;
	}

	system("pause");

	// return 0 if player farkled or turnScore
	return turnScore = farkle ? 0 : turnScore;
}
#pragma endregion

void Game::GameLoop()
{
	bool quit = false;
	unsigned int selection;
	Player winner;

	while (!quit)
	{
		Menu::ShowMenu();
		selection = GetInput();

		switch (selection)
		{
		case 1:	// New Game
			winner = Play();
			Congratulate(winner);
			break;
		case 2:	// Show Rules
			Menu::ShowRules();
			break;
		case 3:	// Quit
			quit = true;
			break;
		default: // Anything else
			break;
		}
	}
}
