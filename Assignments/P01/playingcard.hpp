﻿///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Paige Champagne
// Title:            game of war
// Course:           CMPS 2143
// Semester:         Spring 2020
//
// Description:
//          this is the playing card implenetation file
//          and the cards that make up the whole game
//

//
// Files:           main.cpp
//                  termio.h
//                  playingcard.hpp
//                  poker_game.hpp
//             
/////////////////////////////////////////////////////////////////////////////////
#include "termio.h"
#include <algorithm> // std::random_shuffle
#include <iostream>
#include <string>
#include <vector>

using namespace std;

 //    color struct that holds data about the foreground color of cards
 
struct ForeColor {
	string base;
	string black;
	string red;
	string yellow;
	string green;
	string blue;
	string cyan;
	string magenta;
	string white;

	//constructor that initializes every color
		
	ForeColor() {
		base = "&00";
		black = "&10";
		red = "&20";
		yellow = "&30";
		green = "&40";
		blue = "&50";
		cyan = "&60";
		magenta = "&70";
		white = "&80";
	}
};

 //     color struct that holds data about the background color of cards
 

struct BackColor {
	string base;
	string black;
	string red;
	string yellow;
	string green;
	string blue;
	string cyan;
	string magenta;
	string white;
	
// constructor that initializes every color
		
	BackColor() {
		base = "&10";
		black = "&11";
		red = "&12";
		yellow = "&13";
		green = "&14";
		blue = "&15";
		cyan = "&16";
		magenta = "&17";
		white = "&18";
	}
};
/**
 * class Card
 *
 * Description:
 *      represents the cards for the game
 * Private
 *      -i'm not listing all of these variables they're right there
 * Public Methods:
 *
 *   Card(int);
	string Repr();
	bool operator<(const Card &);
	bool operator>(const Card &);
	bool operator==(const Card &);
	bool operator!=(const Card &);
	bool operator()(const Card &);
	void setForegroundColor(string color);       // set foreground color of card
	void setBackgroundColor(string color);      // set background color of card
	void setColors(string fore,string back);      // set fore and back
	void setCharacterColor(string color);        // set symbol color
	void setNumberColor(string color);          // set number color
	void setColors(string fore, string back, string symbol, string number);
	void baseColors();
 *
 *
 *
 */
class Card {
private:
	const string ranks[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	const string suits[4] = { "♠", "♦", "♣", "♥" };
	int suitNum;     // value 0-3 : num index of suit
	int rank;        // 0-13      : num value of rank
	int number;      // 1-52      : unique value determines card
	int value;       // 1-14      : numeric value used for comparison
	string suitChar; // "♠", "♦", "♣", "♥" also this isn't working for some reason and idk why?
	string rankChar; // Ace, 1 ,2 ,3 ... Q, K
	string color;    // Spade=blue, Diamond=red, etc.
	// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)


public:
	friend ostream;

	Card(int);
	string Repr();
	bool operator<(const Card &);
	bool operator>(const Card &);
	bool operator==(const Card &);
	bool operator!=(const Card &);
	bool operator()(const Card &);
	void setForegroundColor(string color);       // set foreground color of card
	void setBackgroundColor(string color);      // set background color of card
	void setColors(string fore, string back);      // set fore and back
	void setCharacterColor(string color);        // set symbol color 
	void setNumberColor(string color);          // set number color
	void setColors(string fore, string back, string symbol, string number);
	void baseColors();
	// and any other overloaded convenience methods you want to add. 

};



	   //    Represents a single card in a deck of cards to include a
	   //    value along with rank and suit. We are assuming a standard
	 
Card::Card(int num) {
	number = num;
	suitNum = number / 13;
	suitChar = suits[suitNum];
	baseColors();
	rank = number % 13;
	rankChar = ranks[rank];
}



//     Returns a string representation of the card class with
//      colors embedded.
	
string Card::Repr() {
	string s = "";
	s += color + "┌──────────┐&00 \n";
	if (rank == 9) {
		s += color + "│ " + suitChar + " " + rankChar + "&00      " + "|&00 \n";
	}
	else {
		s += color + "│ " + suitChar + " " + rankChar + "&00       " + "|&00 \n";
	}
	s += color + "|          |&00 \n";
	s += color + "|          |&00 \n";
	if (rank == 9) {
		s += color + "│    " + suitChar + " " + rankChar + "&00   " + "|&00 \n";
	}
	else {
		s += color + "│    " + suitChar + " " + rankChar + "&00    " + "|&00 \n";
	}
	s += color + "|          |&00 \n";
	s += color + "|          |&00 \n";
	if (rank == 9) {
		s += color + "│       " + suitChar + " " + rankChar + "&00" + "|&00 \n";
	}
	else {
		s += color + "│       " + suitChar + " " + rankChar + "&00 " + "|&00 \n";
	}
	s += color + "└──────────┘&00 \n";
	/*if (rank != 9) {
		s += color + " ";
	}*/

	return s;
}

 // Overload ostream and send the string representation "Repr"
 //   of the card.

  //   We don't need the scope resolution operator (Card::) since
  //    this is a "friend" of card.
 
 

ostream &operator<<(ostream &os, Card obj) {

	os << obj.Repr();

	return os;
}

	 
//  overloads < to compares cards correctly
	
bool Card::operator<(const Card &rhs) {
	return this->rank < rhs.rank;
}

	//   overloads  to compares cards correctly
	 
bool Card::operator>(const Card &rhs) {
	return this->rank > rhs.rank;
}
/**
	 * Public : operator ==
	 *
	 * Description:
	 *      overloads == to see if cards are ==
	 *
	 * Params:
	 *      const Card &rhs
	 *          card to the right of this one
	 *
	 * Returns:
	 *      bool: if they are ==
	 */
bool Card::operator==(const Card &rhs) {
	return this->rank == rhs.rank;
}
/**
	 * Public : operator !=
	 *
	 * Description:
	 *      overloads != to see if cards are !=
	 *
	 * Params:
	 *      const Card &rhs
	 *          card to the right of this one
	 *
	 * Returns:
	 *      bool: if they are !=
	 */
bool Card::operator!=(const Card &rhs) {
	return this->rank != rhs.rank;
}

	   //    overloads () to compares cards correctly
	
bool Card::operator()(const Card &rhs) {
	return (this->rank < rhs.rank);
}

	     // initializes the base colors depending on the suit
	 
void Card::baseColors() {
	if (suitNum == 0 || suitNum == 2) {
		setColors("green", "white", "green", "green");
	}
	else if (suitNum == 1 || suitNum == 3) {
		setColors("red", "white", "red", "red");
	}
}

	//    sets every color using individual color functions
	 
	 
	 
void Card::setColors(string main, string back, string symbol, string number) {
	setForegroundColor(main);       // set foreground color of card
	setBackgroundColor(back);
	setCharacterColor(symbol);        // set symbol color 
	setNumberColor(number);
}


	  //    sets number color
	
void Card::setNumberColor(string color) {
	if (color == "base") {
		rankChar = ForeColor().base;
	}
	if (color == "black") {
		rankChar = ForeColor().black;
	}
	if (color == "red") {
		rankChar = ForeColor().red;
	}
	if (color == "yellow") {
		rankChar = ForeColor().yellow;
	}
	if (color == "green") {
		rankChar = ForeColor().green;
	}
	if (color == "blue") {
		rankChar = ForeColor().blue;
	}
	if (color == "cyan") {
		rankChar = ForeColor().cyan;
	}
	if (color == "magenta") {
		rankChar = ForeColor().magenta;
	}
	if (color == "white") {
		rankChar = ForeColor().white;
	}
}


	    //   sets Character color
	 
void Card::setCharacterColor(string color) {
	if (color == "base") {
		suitChar = ForeColor().base;
	}
	if (color == "black") {
		suitChar = ForeColor().black;
	}
	if (color == "red") {
		suitChar = ForeColor().red;
	}
	if (color == "yellow") {
		suitChar = ForeColor().yellow;
	}
	if (color == "green") {
		suitChar = ForeColor().green;
	}
	if (color == "blue") {
		suitChar = ForeColor().blue;
	}
	if (color == "cyan") {
		suitChar = ForeColor().cyan;
	}
	if (color == "magenta") {
		suitChar = ForeColor().magenta;
	}
	if (color == "white") {
		suitChar = ForeColor().white;
	}
}

	//  sets fore and background colors
	 
void Card::setColors(string fore, string back) {
	setBackgroundColor(back);
	setForegroundColor(fore);

}

	 //     sets Background color
	
void Card::setBackgroundColor(string color) {
	if (color == "base") {
		color = BackColor().base;
	}
	if (color == "black") {
		color = BackColor().black;
	}
	if (color == "red") {
		color = BackColor().red;
	}
	if (color == "yellow") {
		color = BackColor().yellow;
	}
	if (color == "green") {
		color = BackColor().green;
	}
	if (color == "blue") {
		color = BackColor().blue;
	}
	if (color == "cyan") {
		color = BackColor().cyan;
	}
	if (color == "magenta") {
		color = BackColor().magenta;
	}
	if (color == "white") {
		color = BackColor().white;
	}
}

	  //  sets Foreground color
	
void Card::setForegroundColor(string color) {
	if (color == "base") {
		color = ForeColor().base;
	}
	if (color == "black") {
		color = ForeColor().black;
	}
	if (color == "red") {
		color = ForeColor().red;
	}
	if (color == "yellow") {
		color = ForeColor().yellow;
	}
	if (color == "green") {
		color = ForeColor().green;
	}
	if (color == "blue") {
		color = ForeColor().blue;
	}
	if (color == "cyan") {
		color = ForeColor().cyan;
	}
	if (color == "magenta") {
		color = ForeColor().magenta;
	}
	if (color == "white") {
		color = ForeColor().white;
	}
}