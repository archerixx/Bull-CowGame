/* This is console executable, that is made of the BullCow class
This acts as the view in a MVC patter, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
FBullCowGame BCGame; //instant of new game, which we re-use across plays (this is just one instance, we can make many of them), btw this is object
void Printintro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

int main() {

	



	do {

		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode = 0;
		GetConsoleMode(hStdin, &mode);
		SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

		std::string s;
		std::getline(std::cin, s);

		SetConsoleMode(hStdin, mode);

		BCGame.GetHiddenWord(s);

		Printintro();
		PlayGame();
	}while (AskToPlayAgain());
	
	return 0;
}

void Printintro() {
	

	int32 HiddeWordLenght = BCGame.GetHiddenWordLength();
	std::cout << "\n Welcome to game Bull and Cows" << std::endl;
	std::cout << "Can you guess an isogram of " << HiddeWordLenght << " letters that I think of?" << std::endl << std::endl;
	return;
}

void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries=BCGame.GetMaxTries();

	//loop asking for guesses while the game is not won, and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries) 
	{
		FText guess=GetValidGuess();
		FBullCowCount BullCowCount= BCGame.SubmitValidGuess(guess);
		std::cout << "Bulls =" << BullCowCount.Bulls << std ::endl;
		std::cout << "Cows =" << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

//loop continually until te user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::InvalidStatus;
	FText guess = "";
	do{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try "<< CurrentTry << ". out of " << BCGame.GetMaxTries() <<  ". Enter ur guess: ";
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status)
		{
		case EGuessStatus::NotIsogram:
			std::cout << "Please enter a word without repeating letters.\n \n";
			break;
		case EGuessStatus::WrongLength:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "Please enter word in lowercase letters. \n\n";
			break;
		default:
			//assuming guess is valid
			break;
		}
	} while (Status!=EGuessStatus::OK); 
	return guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Well done - You won\n";
	}
	else {
		std::cout << "Better luck next time\n";
	}
}

bool AskToPlayAgain()
{
	FText response="";
	std::cout << "Do u want to play again (y/n) ?";
	std::getline(std::cin, response);
	if (tolower(response[0]) == 'y')
		return true;
	else
		return false;
}
