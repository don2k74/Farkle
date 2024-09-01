// This file contains the implementation of the Player class
// It contains the constructor, Name, AddScore, Score, SetInGame, and InGame functions

#include <string>
#include "Player.h"

using namespace std;
Player::Player()
{
}

Player::Player(string n) : name(n), score(0), inGame(false)

{
}

string Player::Name()
{
	return name;
}

void Player::AddScore(int value)
{
	score += value;
}

int Player::Score()
{
	return score;
}

void Player::SetInGame()
{
	inGame = true;
}

bool Player::InGame()
{
	return inGame;
}
