#pragma once
#include <string>

using namespace std;

class Player
{
private:
	string name;
	int score;
	bool inGame;

public:
	Player();
	Player(string name); // Player constructor
	
	string Name(); // shows the name of the player
	
	void AddScore(int value); // adds score to the player
	int Score(); // shows the score of the player

	void SetInGame(); // sets the player in game
	bool InGame(); // shows if the player is in game
};

