#include <iostream>
//#include <sstream>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

int MAXATTEMPTFAILS=8;
int SCREENRESX = 1200;
int SCREENRESY = 800;


char getCharInput(vector<char>*);
void setUpRound(char[40], char[40], int*, vector<char>*, bool*);


void resetCharArr(char* arrIn, int arrSizeIn) {
	for (int i = 0; i < arrSizeIn; i++){
		arrIn[i] = '_';
	}
}


bool wordLoop() {
	// true if word guessed, false if not
	

	while (true) {
		
		// game loop
		

		break;
	}
	return false;


}


void setUpRound(char currentWordArrIn[40], char currentGuessArrIn[40], int* currentWordLen, vector<char>* inputtedChars, bool* solved) {
	resetCharArr(currentWordArrIn, 40);
	resetCharArr(currentGuessArrIn, 40);


	string wordPicked = "hello";

	int c = 0;
	for (char i : wordPicked) {
		currentWordArrIn[c] = i;
		++c;
	}

	*currentWordLen = c;
	*inputtedChars = {};
	*solved = false;
}


bool validateUint(char uintIn) {
	if ((uintIn > 64) && (uintIn < 91)) {
		return true;
	}
	if ((uintIn > 96) && (uintIn < 123)) {
		return true;
	}
	return false;
}


int main() {
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(SCREENRESX, SCREENRESY), "Hangman");

	char currentWordArr[40]; fill(currentWordArr, currentWordArr + 40, '_'); // should this be 39??!?!?!?
	char currentGuessArr[40]; fill(currentGuessArr, currentGuessArr + 40, '_');// should this be 39??!?!?!?
	int currentWordLen = 0;
	int attemptFails = 0;
	char guess;
	vector<char> inputtedChars = {};
	bool solved = false;
	bool roundToSetup = true;


	// Start the game loop 
	while (window.isOpen())
	{
		if (roundToSetup) {
			//cout << currentWordArr << currentGuessArr << currentWordLen << solved << endl;
			setUpRound(currentWordArr, currentGuessArr, &currentWordLen, &inputtedChars, &solved);
			//cout << currentWordArr << currentGuessArr << currentWordLen << solved << endl;
			roundToSetup = false;
		}



		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == 27) {
					window.close();
				}
				else if (validateUint(event.text.unicode)){
					cout << (char)event.text.unicode;

				}
			}
		}

		// Clear screen
		window.clear();

		// Update the window
		window.display();
	}
	wordLoop();
	cout << "hw" << endl;
}