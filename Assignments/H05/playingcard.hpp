/*
 ___  ___          ________          ________
|\  \|\  \        |\   __  \        |\   ____\
\ \  \\\  \       \ \  \|\  \       \ \  \___|_
 \ \   __  \       \ \  \\\  \       \ \_____  \
  \ \  \ \  \       \ \  \\\  \       \|____|\  \
   \ \__\ \__\       \ \_______\        ____\_\  \
	\|__|\|__|        \|_______|       |\_________\
									   \|_________|


  _______           _____          ___   ___          ________
 /  ___  \         / __  \        |\  \ |\  \        |\_____  \
/__/|_/  /|       |\/_|\  \       \ \  \\_\  \       \|____|\ /_
|__|//  / /       \|/ \ \  \       \ \______  \            \|\  \
	/  /_/__           \ \  \       \|_____|\  \          __\_\  \
   |\________\          \ \__\             \ \__\        |\_______\
	\|_______|           \|__|              \|__|        \|_______|



 ________  ___  ___  ________   ___  ___  ________  ___  ________   ________  ___  ___  _______
|\   ___ \|\  \|\  \|\   ___  \|\  \|\  \|\   ____\|\  \|\   ___  \|\   ____\|\  \|\  \|\  ___ \
\ \  \_|\ \ \  \\\  \ \  \\ \  \ \  \\\  \ \  \___|\ \  \ \  \\ \  \ \  \___|\ \  \\\  \ \   __/|
 \ \  \ \\ \ \  \\\  \ \  \\ \  \ \  \\\  \ \_____  \ \  \ \  \\ \  \ \  \  __\ \   __  \ \  \_|/__
  \ \  \_\\ \ \  \\\  \ \  \\ \  \ \  \\\  \|____|\  \ \  \ \  \\ \  \ \  \|\  \ \  \ \  \ \  \_|\ \
   \ \_______\ \_______\ \__\\ \__\ \_______\____\_\  \ \__\ \__\\ \__\ \_______\ \__\ \__\ \_______\
	\|_______|\|_______|\|__| \|__|\|_______|\_________\|__|\|__| \|__|\|_______|\|__|\|__|\|_______|
											\|_________|





*/

///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Dulan Dunusinghe
// Label:            H05
// Title:            Playing Card Class
// Course:           CMPS 2143
// Semester:         Spring 2020
//
// Description:
//       This program will create playing cards that can be used for a variety
//       of card games.
//
// Usage:
//       This program will create playing cards for the game of goldfish.
// Files: 
//
//      PlayingCard.hpp    : Implements a playing card
//
/////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>

#include <string>

#include <vector>



using namespace std;


/*
  ██████╗ █████╗ ██████╗ ██████╗
 ██╔════╝██╔══██╗██╔══██╗██╔══██╗
 ██║     ███████║██████╔╝██║  ██║
 ██║     ██╔══██║██╔══██╗██║  ██║
 ╚██████╗██║  ██║██║  ██║██████╔╝
  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/



 
class Card {

private:

	const string spade = "♠";

	const string diamond = "♦";

	const string heart = "♥";

	const string club = "♣";

	const string suits[4] = { "♠", "♦", "♣", "♥" };

	// Colored background      black  , red  , black , red

	const string colors[4] = { "&18", "&28", "&18", "&28" };

	// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)

	const string ranks[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

	int suitNum;     // value 0-3 : num index of suit

	int rank;        // 0-13      : num value of rank

	int number;      // 1-52      : unique value determines card

	int value;       // 1-14      : numeric value used for comparison

	string suitChar; // "♠", "♦", "♣", "♥"

	string rankChar; // Ace, 1 ,2 ,3 ... Q, K

	string color;    // Spade=black, Diamond=red, etc.



public:

	friend ostream;



	Card(int);

	string Repr();

	bool operator<(const Card &);

	bool operator>(const Card &);

	bool operator==(const Card &);

	bool operator!=(const Card &);

	bool operator()(const Card &);

};



/**
	 * Public : Card
	 *
	 * Description:
	 *      Represents a single card in a deck of cards to include a
	 *      value along with rank and suit. We are assuming a standard
	 *      card type in a deck of playing cards.
	 
	 */

Card::Card(int num) {                               // Overloaded Constructor

	number = num;

	suitNum = number / 13;

	suitChar = suits[suitNum];

	color = colors[suitNum];

	rank = number % 13;

	rankChar = ranks[rank];

}



/**
	 * Description:
	 *      Returns a string representation of the card class with
	 *      colors embedded.
	 *
	 */

string Card::Repr() {

	// string "s" acts as an accumulator to create an
	// image of a card

	string s = "";

	s += color + "┌────┐&00 \n";    // "&00" means the default color of a card

	s += color + "│";

	if (rank != 9) {

		s += color + " ";

	}

	s += color + rankChar + " " + suitChar + "│&00 \n";

	s += color + "└────┘&00 ";

	return s;               // return the card

}



/**

 * Description:
 *      Overload ostream and send the string representation "Repr"
 *      of the card.
 
 */

ostream &operator<<(ostream &os, Card obj) {

	// An os object that contains the string
	// representation of a card.

	os << obj.Repr();



	return os;

}



/**

 * Description:
 *      Overloads the "<" operator to compare two cards and returns

 */

bool Card::operator<(const Card &rhs) {

	return this->rank < rhs.rank;

}



/**
 
 * Description:
 *      Overloads the ">" operator to compare two cards and returns
 *      true if "this->rank" is greater than rhs.rank.

 */

bool Card::operator>(const Card &rhs) {

	return this->rank > rhs.rank;

}



/**

 * Description:
 *      Overloads the "==" operator to compare two cards and returns
 *      true if the cards' ranks are eqaul.
 
 */

bool Card::operator==(const Card &rhs) {

	return this->rank == rhs.rank;

}



/**

 * Description:
 *      Overloads the "!=" operator to compare two cards and returns
 *      true if the cards' ranks are not equal.
 
 */

bool Card::operator!=(const Card &rhs) {

	return this->rank != rhs.rank;

}



/**
 
 * Description:
 *      Overloads the "()" operator to compare two Cards witout
 *      using the "<" operator. Returns true if "this->rank" is
 *      less than "rhs.rank".

 */

bool Card::operator()(const Card &rhs) {

	return (this->rank < rhs.rank);

}
