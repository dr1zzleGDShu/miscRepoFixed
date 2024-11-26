//---------------------------------------------------------------------------
//Program: Skeleton starter code for the BLOB!
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//----- include libraries
//---------------------------------------------------------------------------

//include standard libraries
#include <iostream> //for output and input: cout <<, cin >>
#include <iomanip> //for output manipulators
#include <conio.h> //for getch()
#include <string> //for string
#include <assert.h>
#include <windows.h>
#include <algorithm>
#include <cstdlib>

using namespace std;


/*
**A simple library of console routines (from http://sunlightd.virtualave.net/Windows/FAQ.html)
---------------------------------------
** Clrscr() - clear the screen, and reset cursor to (0, 0)
** Gotoxy(x, y) - move the text cursor to position (x, y)
** SelectBackColour(colour) - select a background colour from the colour constants list
** SelectTextColour(colour) - select a text colour from the colour constants list
** SetNewConsoleTitle(title) - set a new title for the console window

** NOTE:Assume that whenever you write text to the screen the attributes will apply to all text
** sent to the screen from that point until the next point at which you select different text
** or background colour, and output text with the new attributes.
* Later we will learn how to move this library out of this source file into its own!
*/
//colour constants for translation
const WORD clBlack = 0;
const WORD clDarkRed = 1;
const WORD clDarkGreen = 2;
const WORD clDarkBlue = 3;
const WORD clDarkCyan = 4;
const WORD clDarkMagenta = 5;
const WORD clDarkYellow = 6;
const WORD clDarkGrey = 7;
const WORD clGrey = 8;
const WORD clRed = 9;
const WORD clGreen = 10;
const WORD clBlue = 11;
const WORD clCyan = 12;
const WORD clMagenta = 13;
const WORD clYellow = 14;
const WORD clWhite = 15;

WORD backColour = 0;
WORD textColour = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
WORD textAttributes = backColour | textColour;

//-------------
//clear the screen, and reset cursor to (0, 0)
void Clrscr()
{
	//from web-site
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

//-------------
//move the text cursor to position (x, y)
void Gotoxy(int x, int y)
{
	//from web-site
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//-------------
//select a background colour from the colour constants list
void SelectBackColour(int colour)
{
	void SelectAttributes();
	switch (colour)
	{
	case clBlack: backColour = 0; break;
	case clDarkRed: backColour = BACKGROUND_RED; break;
	case clDarkGreen: backColour = BACKGROUND_GREEN; break;
	case clDarkBlue: backColour = BACKGROUND_BLUE; break;
	case clDarkCyan: backColour = BACKGROUND_GREEN | BACKGROUND_BLUE; break;
	case clDarkMagenta: backColour = BACKGROUND_RED | BACKGROUND_BLUE; break;
	case clDarkYellow: backColour = BACKGROUND_RED | BACKGROUND_GREEN; break;
	case clDarkGrey: backColour = BACKGROUND_INTENSITY; break;
	case clGrey: backColour = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
	case clRed: backColour = BACKGROUND_INTENSITY | BACKGROUND_RED; break;
	case clGreen: backColour = BACKGROUND_INTENSITY | BACKGROUND_GREEN; break;
	case clBlue: backColour = BACKGROUND_INTENSITY | BACKGROUND_BLUE; break;
	case clCyan: backColour = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
	case clMagenta: backColour = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE; break;
	case clYellow: backColour = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN; break;
	default: backColour = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	}
	SelectAttributes();
}

//-------------
//select a text colour from the colour constants list
void SelectTextColour(int colour)
{
	void SelectAttributes();
	switch (colour)
	{
	case clBlack: textColour = 0; break;
	case clDarkRed: textColour = FOREGROUND_RED; break;
	case clDarkGreen: textColour = FOREGROUND_GREEN; break;
	case clDarkBlue: textColour = FOREGROUND_BLUE; break;
	case clDarkCyan: textColour = FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	case clDarkMagenta: textColour = FOREGROUND_RED | FOREGROUND_BLUE; break;
	case clDarkYellow: textColour = FOREGROUND_RED | FOREGROUND_GREEN; break;
	case clDarkGrey: textColour = FOREGROUND_INTENSITY; break;
	case clGrey: textColour = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	case clRed: textColour = FOREGROUND_INTENSITY | FOREGROUND_RED; break;
	case clGreen: textColour = FOREGROUND_INTENSITY | FOREGROUND_GREEN; break;
	case clBlue: textColour = FOREGROUND_INTENSITY | FOREGROUND_BLUE; break;
	case clCyan: textColour = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	case clMagenta: textColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE; break;
	case clYellow: textColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN; break;
	default: textColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	SelectAttributes();
}

//-------------
//select the text attributes
void SelectAttributes()
{
	textAttributes = backColour | textColour;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textAttributes);
}

//-------------
//get the heigth of the screen (console window)
int screenHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom + 1;
}

//-------------
//get the width of the screen (console window)
int screenWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right + 1;
}

void SetNewConsoleTitle(const std::string& s)
{
	SetConsoleTitle(s.c_str());
}

/*
//---------------------------------------------------------------------------
//----- LIBRARY ENDS HERE AND THE GAME CODE BEGINS
//---------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------
//Program: Starter code for the BLOB! game
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//----- define constants
//---------------------------------------------------------------------------
const bool LOUD(false);

const char BLOBBY('@');
const char ZOMB('%');
const char WALL('*');
const char FLOOR(' ');
const char ESC(27);
const char UP('W'), UP_ARROW(72), DOWN('S'), DOWN_ARROW(80), LEFT('A'), LEFT_ARROW(75), RIGHT('D'), RIGHT_ARROW(77), BOMBSKEY('B');
const unsigned char CTRL_CODE(224); //ignore control codes
const int SIZEY(10);		//vertical dimension
const int SIZEX(10);		//horizontal dimension
const int MSSG_WIDTH(40);	//for displaying messages
const int GIRDOFFSETX(4);
const int GIRDOFFSETY(2);
const char GRIDSPACER(' ');



/*
display on screen
g - the grid to display, a two dimensional array of locations
NOTE - normally an array is indexed 0->(SIZE-1), which can be a bit odd
*/
void PaintGrid(const char g[][SIZEX]) 
{
	//display grid content on screen
	SelectBackColour(clBlack);
	SelectTextColour(clWhite);
	Gotoxy(GIRDOFFSETX, GIRDOFFSETY);
	//for (int row(GIRDOFFSETY); row < (SIZEY + GIRDOFFSETY); ++row)  //for each row (vertically)
	for (int row(0); row < (SIZEY); ++row)  //for each row (vertically)
	{
		//for (int col(GIRDOFFSETX); col < (SIZEX + GIRDOFFSETX); ++col)  //for each column (horizontally)
		for (int col(0); col < (SIZEX); ++col)  //for each column (horizontally)
		{
			switch (g[row][col]) 
			{

			case BLOBBY:
				SelectTextColour(clRed);
				break;
			case ZOMB:
				SelectTextColour(clGreen);
				break;
			case WALL:
				SelectBackColour(clBlack);
				SelectTextColour(clYellow);
				break;
			}
			cout << g[row][col]; //output cell content
			SelectBackColour(clBlack);
			SelectTextColour(clWhite);
			cout << GRIDSPACER;
		}
		cout << endl;
		Gotoxy(GIRDOFFSETX, GIRDOFFSETY+row+1);
	}
}

/*
display a string using specified colour at a given position 
backColour, textColour - these take special colour values, see consoleutils.h
x,y	- where on screen, these coordinates are in text console space
message - the text to show
*/
void ShowMessage(const WORD backColour, const WORD textColour, int x, int y, const string& message)
{	
	Gotoxy(x, y);
	SelectBackColour(backColour);
	SelectTextColour(textColour);
	assert(message.length() < MSSG_WIDTH);
	cout << message + string(MSSG_WIDTH - message.length(), ' ');
}

//get key or command (in uppercase) selected by user
int GetKeyPress()
{
	int keyPressed;
	keyPressed = _getch(); //read in the selected arrow key or command letter
	while (keyPressed == CTRL_CODE) //ignore symbol following cursor/arrow key
		keyPressed = _getch();
	return toupper(keyPressed); //return it in uppercase
}

/*
test if that coordinate is inside the map and not a wall
x,y - a position on the map
g - the map grid
*/

bool IsLegalPosition(int x, int y, const char g[][SIZEX])
{
	/* GOT RID OF THIS FUNCTION, TO BASIC
	Currently no illegal moves

	assert(x >= 0 && x < SIZEX);
	assert(y >= 0 && y < SIZEY);
	if (g[y][x] == ' ')
		return true;
	return false;
	*/
	return true;
}

void flipPosAtWall(int& x, int& y, const char g[][SIZEX]){
	assert(x >= 0 && x < SIZEX);
	assert(y >= 0 && y < SIZEY);
	if (g[y][x] == WALL){
		if (x == 0) {
			x = SIZEX - 2;
		} else if(x == SIZEX-1) {
			x = 1;
		}
		if (y == 0) {
			y = SIZEY - 2;
		}else if (y == SIZEY - 1) {
			y = 1;
		}
	}

}



/*
* update the map
* x,y - a map position
* symbol - the item to add to the map
* g - the map grid array
*/
void PlaceItem(const int x, const int y, const char symbol, char g[][SIZEX])
{
	assert(x >= 0 && x < SIZEX);
	assert(y >= 0 && y < SIZEY);
	g[y][x] = symbol;
}

//dest - the grid we are overwrting
//src - the original data
void CopyGrid(char dst[][SIZEX], const char src[][SIZEX])
{
	for (int i = 0; i < (SIZEY*SIZEX); ++i)
		((char*)dst)[i] = ((char*)src)[i];
}

//set the default play area
//g - the handle of the grid to setup
void InitialiseGrid(char g[][SIZEX])
{
	char grid[SIZEY][SIZEX]
		= {
		{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WALL },
		{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
	};
	
	CopyGrid(g, grid);
}

/*
move the blob around
blob - where he is currently
grid - the map
key - could be a direction move key (up,down,left,right)
*/
void UpdateBlob(int& x, int& y, char grid[][SIZEX], char key)
{
	int nX = x, nY = y;
	switch (key)
	{
	case UP:
	case UP_ARROW:
		nY -= 1;
		break;
	case DOWN:
	case DOWN_ARROW:
		nY += 1;
		break;
	case LEFT:
	case LEFT_ARROW:
		nX -= 1;
		break;
	case RIGHT:
	case RIGHT_ARROW:
		nX += 1;
		break;
	default:
		return;
	}
	flipPosAtWall(nX, nY, grid);
	//are these coordinates acceptable??
	if (IsLegalPosition(nX, nY, grid))
	{
		//erase previous map position and add the new one
		PlaceItem(x, y, FLOOR, grid);
		x = nX;
		y = nY;
		PlaceItem(x, y, BLOBBY, grid);
	}
}

void UpdateZomb(int& zXIn, int& zYIn, int bXIn, int bYIn, char grid[][SIZEX]) {
	// works out what direction zomb need to travel, then clamps it to the 1 tile to get the offset for the zomb to move, then just moves in that direct
	int nX = zXIn, nY = zYIn;
	int nXOffset, nYOffset;

	
	// work out direct to blob
	nXOffset = bXIn - zXIn;
	nYOffset = bYIn - zYIn;

	// limit to 1 tile mv
	nXOffset = max(-1, min(nXOffset, 1));
	nYOffset = max(-1, min(nYOffset, 1));

	// work out new pos
	nX += nXOffset;
	nY += nYOffset;


	// limit to grid confines 
	max(1, min(nX, SIZEX - 1));
	max(1, min(nY, SIZEY - 1));


	// debug print
	//cout << "ZOMB pos, orig: " << zXIn << "," << zYIn << " new: " << nX << "," << nY << " offset: " << nXOffset << "," << nYOffset << "         " << endl;



	//are these coordinates acceptable??
	if (IsLegalPosition(nX, nY, grid))
	{
		//erase previous map position and add the new one
		PlaceItem(zXIn, zYIn, FLOOR, grid);
		zXIn = nX;
		zYIn = nY;
		PlaceItem(zXIn, zYIn, ZOMB, grid);
	}
}


void ShowMessages(int score, int bombs)
{
	string scoreString = "Score = " + to_string(score);
	string bombsString = "Bombs = " + to_string(bombs);
	ShowMessage(clBlack, clYellow, 36, 3, "___BLOB___");
	ShowMessage(clBlack, clBlue, 36, 5, scoreString);
	ShowMessage(clBlack, clBlue, 36, 6, bombsString);
	ShowMessage(clWhite, clRed, 36, 9, "W A S D or arrows to move the blob(@)");
	ShowMessage(clWhite, clRed, 36, 10, "Escape to quit");

}


bool checkIfDead(int zXIn, int zYIn, int bXIn, int bYIn) {
	return ((zXIn == bXIn) && (zYIn == bYIn));
}

//this is the end
void ReadyToQuit(bool plrDiedBool, int score)
{

	Clrscr();
	if (plrDiedBool) {
		string scoreString = "Score = " + to_string(score);
		ShowMessage(clBlack, clRed, 24, 6, "You Died");
		ShowMessage(clBlack, clBlue, 20, 8, scoreString);
	}
	ShowMessage(clBlack, clYellow, 20, 10, "Any key to exit"); //15
	_getch();
}

void pickRandomEmptyPointOnGrid(int& xIn, int& yIn, char grid[][SIZEX]) {
	bool spaceFound = false;
	while (!spaceFound) {
		xIn = rand() % SIZEX - 2;
		yIn = rand() % SIZEY - 2;
		++xIn; ++yIn;
		if (grid[yIn][xIn] == ' ') {
			spaceFound = true;
		}
	}
}

//---------------------------------------------------------------------------
//----- run game
// This is just the starter code for a simple game and is not finished
//---------------------------------------------------------------------------

int main() 
{
	srand(time(0));
	int score = 0;
	int bombs = 9;
	bool dedBool = false;
	//initialise
	char grid[SIZEY][SIZEX];
	InitialiseGrid(grid);
	int bX=0, bY=0;
	pickRandomEmptyPointOnGrid(bX, bY, grid);
	PlaceItem(bX, bY, BLOBBY, grid);
	int zX = 0, zY = 0;
	pickRandomEmptyPointOnGrid(zX, zY, grid);
	PlaceItem(zX,zY,ZOMB,grid);
	SetConsoleTitle("Blob!!");

	//game update and render loop
	char key = 0;
	do {
		//render
		ShowMessages(score, bombs);
		PaintGrid(grid);
		//update
		key = GetKeyPress();
		UpdateBlob(bX, bY, grid, key);
		UpdateZomb(zX, zY, bX, bY, grid);
		dedBool = checkIfDead(zX, zY, bX, bY);
		if (dedBool) { ReadyToQuit(true, score); };
		++score;
	} while ((key != ESC) && !dedBool);
	if (!dedBool) { ReadyToQuit(false, 0); }
	return 0;
}


