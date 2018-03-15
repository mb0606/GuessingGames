// BothGuessingGame.cpp : Guessing and reverse guessing game.
// Autor: Marco Berardini

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

//Prototypes
void games(int game, string username, int& min, int &max);
void guessingGame(string username, int& min, int &max);
void reverseGuessingGame(int game, string username, int& min, int &max);
bool setMinMax(int &min, int &max);
int numVariation(int min, int max);
void analyseGuesses(int const guessesArray[], int const bestGuessesArray[], bool won, int attempts, int range);

// Global Variables
int const MIN_ALLOWED_RANGE = 10;
int const MAX_ALLOWED_RANGE = 120;
int const MAX_ALLOWED_GUESSES = 3;

int main()
{

	string username;
	int game;

	cout << "Please enter your name to enter the game. " << endl;
	cin >> username;

	cout << "---------------------------------------------" << endl;
	cout << "    Welcome to Guessing Game " << username << endl;
	cout << "---------------------------------------------" << endl;
	do {

		do {
			cout << "Please choose : " << endl;
			cout << "1. Guessing Game" << endl;
			cout << "2. Reverse Guessing game" << endl;
			cout << "3. Exit Guessing game" << endl;
			cout << "Enter your choice: ";
			cin >> game;
			if (cin.fail() || cin.bad()) {
				cin.clear();
				cerr << "You did not enter a number. " << endl;
				cin.ignore();
			}

		} while (game != 1 && game != 2 && game !=3);

		int min = 0;
		int max = 0;
		
		if (game != 3) {
			switch (game) {
			case 1: {
				games(game, username, min, max);
				break;
			}
			case 2: {
				games(game, username, min, max);
				break;
			}
			}
		};

	} while (game != 3);
	system("pause");
    return 0;
}

/////////////////////////////////////
// functions
/////////////////////////////////////

// Set up commonalities for both games and call appropriate function.
void games(int game, string username, int& min, int &max) {

	bool rangeAllowence = false; // When true range is within defined limits
	char playAgain = 'n';

	// Do while playAgain is Y/y
	do{

		do {
			rangeAllowence = setMinMax(min, max);
			if (!rangeAllowence) {
				cout << "Please re-enter a range that is a minimum of 10 and a maxium of 120." << endl;
			}
		} while (!rangeAllowence);

		if (game == 1) {
			guessingGame(username, min, max);
		}
		else if (game == 2) {
			reverseGuessingGame(game, username, min, max);
		}

		// Ask user if they would like to play the same game again.
		cout << "\nWould you like to play again(Y/N)" << endl;
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');
}

// Computer guesses a number that the user is keeping secret.
void reverseGuessingGame(int game, string username, int& min, int &max) {
	// Declarations
	int userNum;
	int userGuidence;
	bool guessed = false;
	int attempts = 0;
	bool cheating = false;
	int highestMin = min;
	int lowestMax = max;
	int computerGuesses[MAX_ALLOWED_GUESSES] = { 0 };
	int guidedGuesses[MAX_ALLOWED_GUESSES] = { 0 };


	cout << "Think of a number betwwen " << min << " and " << max << endl;

	int aiGuess = ((max - min) / 2) + numVariation(min, max);
	computerGuesses[0] = aiGuess;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "The computers first guesses: " << aiGuess << endl;
	do {

		// highestMin < lowestMax  or user is lying.
		if (highestMin < lowestMax) {
			do {
				cout << "Please let me know if it is too high/low or if I guesses right. " << endl;
				cout << "1 - Too low" << endl;
				cout << "2 - Too high" << endl;
				cout << "3 - You guessed right" << endl;
				cout << "--------------------------------------------------------------------" << endl;
				cout << "Enter you choice: ";
				cin >> userGuidence;
				cout << endl;
			} while (userGuidence != 1 && userGuidence != 2 && userGuidence != 3);

			if (userGuidence == 1) {
				if (highestMin < aiGuess) 
				{
					highestMin = aiGuess;
					// Current max value - (range/2)
					aiGuess = lowestMax - ((lowestMax - highestMin) / 2) + numVariation(min, max);
					// Parallel array to check if user has been guiding computer correctly 
					guidedGuesses[attempts] = 1;
					++attempts;
					// Store computer guesses
					computerGuesses[attempts] = aiGuess;
					if (attempts < MAX_ALLOWED_GUESSES) {
						cout << "The Computers new guess is : " << aiGuess << endl;
					}
				}
				else 
				{
					cout << "Seems like you maybe lying just a mintue ago you told me " << highestMin << " was too low." << endl;
					cheating = true;
					attempts = MAX_ALLOWED_GUESSES;
				}
			}
			else if (userGuidence == 2) {
				if (lowestMax > aiGuess) {
					lowestMax = aiGuess;
					// Current min value + (range/2)
					aiGuess = highestMin + ((lowestMax - highestMin) / 2) + numVariation(min, max);
					// Parallel array to check if user has been guiding computer correctly 
					guidedGuesses[attempts] = 2;
					++attempts;
					// Store computer guesses
					computerGuesses[attempts] = aiGuess;
					if (attempts < MAX_ALLOWED_GUESSES) {
						cout << "The Computers new guess is : " << aiGuess << endl;
					}
				}
				else 
				{
					cout << "Seems like you maybe lying just a mintue ago you told me " << lowestMax << " was too high." << endl;
					cheating = true;
					attempts = MAX_ALLOWED_GUESSES;
				}
			}
			else if (userGuidence == 3) 
			{
				guessed = true;
			}
		}
		// If there is a difference of 1 between current min and max. There is only on possible option. 
		else if (highestMin == lowestMax)
		{
			cout << "Something is not right the number must be:  " << lowestMax <<  endl;
			attempts = MAX_ALLOWED_GUESSES;
		}
		// If current min and max crisscrossed the user is cheating.
		else 
		{
			cheating = true;
			attempts = MAX_ALLOWED_GUESSES;
		}


	} while (!guessed && MAX_ALLOWED_GUESSES != attempts);

    // If it was obvious that the user was misleading the computer.
	if (cheating)  {
		cout << "We would have loved to continue playing but you are obviously cheating! " << endl;
	}
	if (!cheating) {
		// User enters sercret number 
		cout << "Enter the number we were guessing : ";
		cin >> userNum;
		cout << endl;
		// Declare var to validate users actions.
		int compare;
		bool misled = false;

		bool guessedRight = false;
		for (int i = 0; i < attempts; ++i) {
			// Compare user guiding to answer. 1 - too low/ 2 - too high 
			compare = (computerGuesses[i] < userNum) ? 1 : 2;
			if (compare != guidedGuesses[i]) {
				misled = true;
			}
			// compare user guesses with computer guesses.
			if (computerGuesses[i] == userNum) {
				guessedRight = true;
			}
		}
		// If the computer guessed right and the user did not press 3.
		if (guessedRight) {
			cout << "After careful analyses it has been determined that you were misleading." << endl;
			cout << "The computer guesses right and you contunied to play. " << endl;
		}
		else 
		{
			// Computer guessed the number inspite of the user being misleading.
			if (guessed && misled) {
				cout << "After careful analyses it has been determined that you were misleading." << endl;
				cout << "The computer guessed your number in  " << attempts << "." << endl;
			}
			// User did not guess the number and user was being misleading.
			if (!guessed && misled) {
				cout << "After careful analyses it has been determined that you were misleading." << endl;
				cout << "Your guidence was not in the right direction. " << endl;
			}
			// Computer guesses users number.
			if (guessed && !misled) {
				cout << "The computer guessed your number in  " << attempts << "." << endl;
			}
			// Computer did not guess the number.
			if (!guessed && !misled) {
				cout << "You out smarted the computer. Good job! " << endl;
			}
		}
		// Prints out all of the computers guesses.
		cout << "Here are all the guesses: ";
		for (int i = 0; i < attempts; ++i) {
			cout << computerGuesses[i] << ((i < attempts - 1) ? "," : ". ");
		}
		cout << endl;
	}

}

// Computer generates random number and user tries to guess it.
void guessingGame(string username, int& min, int &max) {

	int guessesArray[MAX_ALLOWED_GUESSES] = { 0 };
	int bestGuessesArray[MAX_ALLOWED_GUESSES] = { 0 };

	bool won = false;
	int userGuess;
	int attempts = 0;

	int range = max - min;
	int highestMin = min; // Changes based on user guess
	int lowestMax = max; // Changes based on user guess

	int ai = rand() % max + min; // Computer random number 


	cout << "The computer has made it's selection please enter your guess." << endl;
	cout << "Please choose a number between : " << min << " and " << max << endl;
	// First best guess based on min and max
	bestGuessesArray[attempts] = (lowestMax - highestMin) / 2;

	do {
		// User chooses
		cin >> userGuess;

		// Check that guess is between min and max.
		if (userGuess >= min && userGuess <= max) {
			if (userGuess == ai) {
				cout << "Your guessed right and won the game! " << endl;
				won = true;
				++attempts;
			}
			// User guessed to lower.
			else if (userGuess < ai) {
				cout << "Your guess was too low. " << endl;
				guessesArray[attempts] = userGuess;
				++attempts;
				if (highestMin < userGuess) {
					highestMin = userGuess;
				}
				bestGuessesArray[attempts] = lowestMax - ((lowestMax - highestMin) / 2);
			}
			// User guessed to high.
			else {
				cout << "Your answer was too high." << endl;
				guessesArray[attempts] = userGuess;
				++attempts;
				if (lowestMax > userGuess) {
					lowestMax = userGuess;
				}					
				bestGuessesArray[attempts] = highestMin + ((lowestMax - highestMin) / 2);
			}
		}
		// User value no in range
		// Will not increment attempts
		else
		{
			cerr << "Your number is out of bounds. Please enter a valid number" << endl;
		}
	} while (!won && MAX_ALLOWED_GUESSES != attempts); // Do While user has not won and user has not reached max guesses.

	if (!won) {
		cout << "Sorry "
			<< username
			<< " you did not guess my number - it's "
			<< ai
			<< "!" << endl;

	}
	cout << "Here is the list of you prior guesses: [ ";
	for (int i = 0; i < attempts; i++) {
		cout << guessesArray[i] << ((i + 1 < attempts) ? ", " : "");
	}
	cout << " ]" << endl;
	analyseGuesses(guessesArray, bestGuessesArray, won, attempts, range);
}

// Will add a varying number to the computers best guess.
int numVariation(int min, int max) {
	int posORneg = ((rand() % 2 + 1) == 1) ? -1 : 1;
	int randomValue = rand() % 5 + 1;
	int variation = (((max - min)*.1) / (randomValue)) * (posORneg);
	return variation;

}

// Sets the min and max value for the range of the guesses.
bool setMinMax(int &min, int &max) {
	cout << "Please enter a min value: " ;
	cin >> min;
	cout << "Please enter a max value: ";
	cin >> max;
	return (((max - min) >= MIN_ALLOWED_RANGE) && ((max - min) <= MAX_ALLOWED_RANGE));
}

// Set a threshold to compare to best guess to the users guess.
// Based on the threshold function will determine if the guesses were to far off 
//       from optium guessing pattern.
void analyseGuesses(int const guessesArray[], int const bestGuessesArray[], bool won, int attempts, int range) {
	double threshold = (range*.1) * attempts;
	double userTrushHold = 0;

	for (int i = 0; i < attempts; i++) {
		userTrushHold += (guessesArray[i] - bestGuessesArray[i]);
		userTrushHold *= (userTrushHold < 0) ? -1 : 1;
	}

	if (won && userTrushHold < threshold) {
		cout << "You did a great job of guessing!" << endl;
	}
	else if (won && userTrushHold > threshold) {
		cout << "You got really luck. Your guesses could have been better." << endl;
	}
	else if (!won && userTrushHold < threshold) {
		cout << "You may have lost but you made some great guesses!" << endl;
	}
	else if (!won && userTrushHold > threshold) {
		cout << "You need a better stratagey when guessing." << endl;
	}

};
