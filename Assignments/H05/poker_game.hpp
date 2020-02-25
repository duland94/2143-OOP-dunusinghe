#include "termio.h"

#include <algorithm> // std::random_shuffle

#include "PlayingCard.hpp"



using namespace std;

/*
  ██████╗ █████╗ ██████╗ ██████╗  ██████╗ ██████╗ ███╗   ██╗████████╗ █████╗ ██╗███╗   ██╗███████╗██████╗
 ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝██╔══██╗
 ██║     ███████║██████╔╝██║  ██║██║     ██║   ██║██╔██╗ ██║   ██║   ███████║██║██╔██╗ ██║█████╗  ██████╔╝
 ██║     ██╔══██║██╔══██╗██║  ██║██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██║██║██║╚██╗██║██╔══╝  ██╔══██╗
 ╚██████╗██║  ██║██║  ██║██████╔╝╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║██║██║ ╚████║███████╗██║  ██║
  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝
*/



class CardContainer {

protected:

	Term::IO io;

	vector<Card *> Cards;

	int RandomIndex();

	struct CardCompare {

		bool operator()(Card *l, Card *r) {

			return *l < *r;

		}

	};



public:

	CardContainer(int);

	void Add(Card *);

	bool isEmpty();

	void Order();

	Card *Remove();

	void Reset();

	void Shuffle();

	int Size();

};



CardContainer::CardContainer(int numCards) {

	for (int i = 0; i < numCards; i++) {

		Cards.push_back(new Card(i));

	}

}



void CardContainer::Add(Card *card) {

	// check if card already in container?

	// allow go over 52 ??



	Cards.push_back(card);

	//currentCount = Cards.size();

}



bool CardContainer::isEmpty() {

	return Cards.empty();

}



void CardContainer::Order() {

	sort(Cards.begin(), Cards.end(), CardCompare());

}



Card *CardContainer::Remove() {

	Card *temp = Cards.back();

	Cards.pop_back();

	return temp;

}



void CardContainer::Reset() {

	for (int i = 0; i < Cards.size() - 1; i++) {

		delete Cards[i];

		Cards[i] = new Card(i);

	}

}



void CardContainer::Shuffle() {

	for (int i = 0; i < Cards.size() - 1; i++) {

		int j = i + rand() % (Cards.size() - i);

		swap(Cards[i], Cards[j]);

	}

}



int CardContainer::Size() {

	return Cards.size();

}



/*
 ██████╗ ███████╗ ██████╗██╗  ██╗
 ██╔══██╗██╔════╝██╔════╝██║ ██╔╝
 ██║  ██║█████╗  ██║     █████╔╝
 ██║  ██║██╔══╝  ██║     ██╔═██╗
 ██████╔╝███████╗╚██████╗██║  ██╗
 ╚═════╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝
*/



class Deck : public CardContainer {

protected:

	int deckSize;



public:

	Deck(int);

	Card *Draw();

	void Print(int, bool);

};



Deck::Deck(int size) : CardContainer(size) {

	deckSize = size;

}



Card *Deck::Draw() {

	Card *temp = Cards.back();

	Cards.pop_back();

	return temp;

}



void Deck::Print(int columns = 1, bool clear = false) {

	int i = 0;

	vector<string> cards;



	if (clear) {

		io << Term::clear;

	}



	for (auto c : Cards) {

		cards.push_back(c->Repr());



		i++;

		if (i == columns) {

			io << Term::fuse(cards) << "\n";

			i = 0;

			cards.clear();

		}

	}



	// any cards left in the vector should be

	// printed out.

	if (cards.size() > 0) {

		io << Term::fuse(cards) << "\n";

	}

}



/*
 ██╗  ██╗ █████╗ ███╗   ██╗██████╗
 ██║  ██║██╔══██╗████╗  ██║██╔══██╗
 ███████║███████║██╔██╗ ██║██║  ██║
 ██╔══██║██╔══██║██║╚██╗██║██║  ██║
 ██║  ██║██║  ██║██║ ╚████║██████╔╝
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝
*/



class Hand {

protected:

public:

	Hand();

	void Print();

};



void Hand::Print() {

	return;

}



/*
  ██████╗  █████╗ ███╗   ███╗███████╗
 ██╔════╝ ██╔══██╗████╗ ████║██╔════╝
 ██║  ███╗███████║██╔████╔██║█████╗
 ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝
 ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝
*/



class Game {

protected:

public:

};