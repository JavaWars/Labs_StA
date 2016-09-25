#ifndef _CARD_DECK_
#define _CARD_DECK_

#include "card.h"
#include "template_queue.h"
#include <ctime>
struct CardDeck
{
	TemplateQueue<Card> *m_pDeck;
};

CardDeck* CreateCardDeck();

CardDeck* CreateEmptyCardDeck();

void Mix(CardDeck & _deck);

void DivFor2Players(CardDeck & _mainDeck, CardDeck & _deckPlayer1, CardDeck & _deckPlayer2,bool isEqualCountForPlayer);

void PrintCardDeckToFIle(CardDeck _deck, std::wofstream & _wofstream);

Card GetFirsCard(CardDeck & _deck);

void AddCards(CardDeck &_deck, Card &card1, Card &card2);

void AddCards(CardDeck &_mainDeck, CardDeck &_bufDeck);

int CardsCount(const CardDeck _deck);
#endif//_CARD_DECK_
