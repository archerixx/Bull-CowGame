#pragma once
#include "FBullCowGame.h"
#include <map>
#include <iostream>

//to make syntax Unreal friendly
#define TMap std::map 
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	MyCurrrentTry = 1;
	bGameIsWon = false;
	return;
}

FString FBullCowGame::GetHiddenWord(FString word)
{
	MyHiddenWord = word;
	return MyHiddenWord;
}

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {1,2},{2,3},{ 3,3 },{ 4,5 },{ 5,8 },{ 6,10 },{7,10},{8,12},{9,15},{10,15} };//ajusting wordlenght to max tries
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrrentTry;}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess)) {
		return EGuessStatus::NotIsogram;
	}
	else if (!IsLowerCase(guess)) {
		return EGuessStatus::NotLowercase;
	}
	else if (guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::WrongLength;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString guess) const
{
	// treat 0 and 1 letter words as isograms
	if (guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : guess) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { //if the letter is in the map
			return false; //we dont have an isogram
		}
		else {
			LetterSeen[Letter] = true;//add the letter to the map as seen
		}
	}
	return true; // in case where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString guess) const
{
	for (auto Letter : guess) {
		// If not lowercase letter return false
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

//receives a Valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length();
	
	//loop trough all letters in the guess
	for (int32 HWChar = 0; HWChar < WordLenght; HWChar++) {
		// compare letters against the hidden word
		for (int32 GWChar = 0; GWChar < WordLenght; GWChar++) {
			if (guess[GWChar] == MyHiddenWord[HWChar]) {
				if (HWChar == GWChar){
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}


	return BullCowCount;
}
