/*The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>
#include <windows.h>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

enum class EGuessStatus {
	InvalidStatus,
	OK,
	NotIsogram,
	WrongLength,
	NotLowercase
};

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
	
	public:
		FBullCowGame();

		void Reset();	
		FString GetHiddenWord(FString);
		int32 GetHiddenWordLength() const;
		int32 GetMaxTries() const;
		int32 GetCurrentTry() const;
		FBullCowCount SubmitValidGuess(FString guess);
		EGuessStatus CheckGuessValidity(FString) const; 
		bool IsGameWon() const;

	// should be putting variasbles here
	private:
		int32 MyCurrrentTry;
		FString MyHiddenWord;
		bool bGameIsWon;
		
		bool IsIsogram(FString) const;
		bool IsLowerCase(FString) const;
};