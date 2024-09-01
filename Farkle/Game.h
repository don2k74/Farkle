#pragma once
#include <vector>
#include <array>
#include "Player.h"

class Game
{
private:
	// Input variables
	void ClearInput();
	int GetInput();

	// Message variables
	void Congratulate(Player& player);
	void FinalRound(Player& player);
	void ShowDiceKept(array<int, 6>& diceKept);
	void ShowDiceRolled(vector<int>& diceGroup);
	void IntroducePlayers(vector<Player>& players);

	// Setup
	void PromptNumberOfPlayers();
	void SetPlayerNames(vector<Player>& players);

	// Play
	array<int, 6> CountDice(vector<int>& diceGroup);
	bool CheckFor10k(int score);
	bool IsValid(unsigned int& selection, vector<int>& diceGroup);
	bool ScoringDice(array<int, 6>& diceCount);
	int ScoreDice(vector<int>& diceGroup, int dice, array<int, 6>& diceCount, array<int, 6>& diceKept);
	void RollDice(vector<int>& diceGroup);
	Player GetWinner(vector<Player> players);

	// Private Loops
	int Turn(Player& player);
	Player Play();

public:
	void GameLoop();
};
