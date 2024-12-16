#include <iostream>
//#include <sstream>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

const int MAXATTEMPTFAILS=8; // failed attempts before plr fails
const int SCREENRESX = 1200;
const int SCREENRESY = 800;
// min and max values for valid upper and lowercase letter inputs, used in input validation
const char VALIDCHARLOWERMIN = 64;
const char VALIDCHARLOWERMAX = 91;
const char VALIDCHARUPPERMIN = 96;
const char VALIDCHARUPPERMAX = 123;
const char ESCCHAR = 27;


char getCharInput(vector<char>*);
void setUpRound(char*, char*, int*, vector<char>*, bool*);
void selectWord(char*, int*);

void resetCharArr(char* arrIn, int arrSizeIn) {
	// takes in an arr of chars with a specified size, and resets it ti '_', the char we are using as unguessed letter
	for (int i = 0; i < arrSizeIn; i++){
		arrIn[i] = '_';
	}
}


void setUpRound(char* currentWordArrIn, char* currentGuessArrIn, int* currentWordLen, vector<char>* inputtedChars, bool* solved) {
	// (re)sets all varibles so a new round can start
	resetCharArr(currentWordArrIn, 40);
	resetCharArr(currentGuessArrIn, 40);

	selectWord(currentWordArrIn, currentWordLen);

	*inputtedChars = {};
	*solved = false;
}


bool validateUint(char uintIn) {
	// takes in a user input and returns true if it is a valid input for the game
	// returns false if 
	if ((uintIn > VALIDCHARLOWERMIN) && (uintIn < VALIDCHARLOWERMAX)) {
		return true;
	}
	if ((uintIn > VALIDCHARUPPERMIN) && (uintIn < VALIDCHARUPPERMAX)) {
		return true;
	}
	return false;
}


void selectWord(char* currentWordArrIn, int* currentWordLen) {
	// TODO random word
	string wordPicked = "hello";

	int c = 0;
	for (char i : wordPicked) {
		currentWordArrIn[c] = i;
		++c;
	}

	*currentWordLen = c;
}


bool guessLetter(char guessIn, char* currentWordArrIn, vector<char>* inputtedChars) {
	if (false) {
		;
	}
	return false;
}


int main() {
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(SCREENRESX, SCREENRESY), "Hangman");

	char currentWordArr[40]; fill(currentWordArr, currentWordArr + 40, '_'); // this overwites the end of the char arr (has no /0 or /n anymore)
	char currentGuessArr[40]; fill(currentGuessArr, currentGuessArr + 40, '_'); // be careful when pasing this as a str
	int currentWordLen = 0; // len of the word the plr needs to guess
	int attemptFails = 0;
	char guess; // current guessed letter
	vector<char> inputtedChars = {}; // chars the player has already inputted this round
	bool solved = false;
	bool roundToSetup = true; // use to buffer a setup next game loop
	bool acceptingGuesses = true;


	// Start the game loop 
	while (window.isOpen())
	{
		if (roundToSetup) {
			// setup a new round if buffered
			cout << currentWordArr << currentGuessArr << currentWordLen << solved << endl;
			setUpRound(currentWordArr, currentGuessArr, &currentWordLen, &inputtedChars, &solved);
			cout << currentWordArr << currentGuessArr << currentWordLen << solved << endl;
			roundToSetup = false;
		}



		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// if plr inputs smth, iterate through all inputs this loop
			if (event.type == sf::Event::Closed) {
				window.close(); // x pressed
			}
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == ESCCHAR) { 
					window.close(); // esp pressed
				}
				else if (acceptingGuesses && (validateUint(event.text.unicode))){
					// if valid letter inputted and program is allowing guesses
					cout << (char)event.text.unicode;

				}
			}
		}

		// Clear screen
		window.clear();

		// Update the window
		window.display();
	}
	cout << "hw" << endl;
}