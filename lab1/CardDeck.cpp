#include "CardDeck.h"

CardDeck * CreateCardDeck()
{
	CardDeck *result = CreateEmptyCardDeck();
	for (int i = 0; i < sizeof(CardColor) / sizeof(wchar_t); i++)
	{
		for (int j = 0; j < sizeof(CardNumber) / sizeof(char*); j++)
		{
			Card buf;
			buf.m_colorCard = CardColor[i];
			buf.m_pNumberCard = CardNumber[j];
			TemplateQueuePush<Card>(*result->m_pDeck, buf);
		}
	}
	return result;
}

CardDeck * CreateEmptyCardDeck()
{
	CardDeck *result = new CardDeck;
	result->m_pDeck = TemplateQueueCreate<Card>(sizeof(CardColor) / sizeof(wchar_t) * sizeof(CardNumber) / sizeof(char*));;
	return result;
}

void Mix(CardDeck & _deck)
{
	int cardDeckSize = (sizeof(CardColor) / sizeof(wchar_t))*(sizeof(CardNumber) / sizeof(char*));
	int sizeArr = 10;
	srand(time(0));
	CardDeck * bufArr = new CardDeck[sizeArr];//несколько кучек

	for (int i = 0; i < sizeArr; i++)
	{
		bufArr[i].m_pDeck = TemplateQueueCreate<Card>(cardDeckSize);
	}

	for (int i = 0; i < (sizeof(CardColor) / sizeof(wchar_t))*(sizeof(CardNumber) / sizeof(char*)); i++)
	{
		TemplateQueuePush<Card>(*bufArr[(rand() % sizeArr)].m_pDeck, TemplateQueueFront<Card>(*_deck.m_pDeck));
		TemplateQueuePop<>(*_deck.m_pDeck);
		//кладем в случайную кучку из колоды
	}
	for (int i = 0; i < sizeArr; i++)
	{
		//переложить кучку за кучкой в главную колоду
		TemplateQueuePush<>(*_deck.m_pDeck, *bufArr[i].m_pDeck);
	}
	delete bufArr;
}

void DivFor2Players(CardDeck & _mainDeck, CardDeck & _deckPlayer1, CardDeck & _deckPlayer2, bool isEqualCountForPlayer)
{
	if (!isEqualCountForPlayer)
	{
		srand(time(0));
		for (int i = 0; i < (sizeof(CardColor) / sizeof(wchar_t))*(sizeof(CardNumber) / sizeof(char*)); i++)
		{
			if (rand() % 2 == 0)
			{
				TemplateQueuePush<Card>(*_deckPlayer1.m_pDeck, TemplateQueueFront<Card>(*_mainDeck.m_pDeck));
			}
			else
			{
				TemplateQueuePush<Card>(*_deckPlayer2.m_pDeck, TemplateQueueFront<Card>(*_mainDeck.m_pDeck));
			}
			TemplateQueuePop<>(*_mainDeck.m_pDeck);
		}
	}
}

void PrintCardDeckToFIle(CardDeck _deck, std::wofstream & _wofstream)
{
	_wofstream << TemplateQueueCountOfElements<>(*_deck.m_pDeck);
	while (!TemplateQueueIsEmpty<>(*_deck.m_pDeck))
	{
		_wofstream << TemplateQueueFront<>(*_deck.m_pDeck) << '\n';
		TemplateQueuePop<>(*_deck.m_pDeck);
	}
	_wofstream << "\n";
}

Card GetFirsCard(CardDeck & _deck)
{
	Card result = TemplateQueueFront<>(*_deck.m_pDeck);
	TemplateQueuePop<>(*_deck.m_pDeck);
	return result;
}

void AddCards(CardDeck & _deck, Card & card1, Card & card2)
{
	TemplateQueuePush<>(*_deck.m_pDeck,card1);
	TemplateQueuePush<>(*_deck.m_pDeck, card2);
}

void AddCards(CardDeck & _mainDeck, CardDeck & _bufDeck)
{
	TemplateQueuePush<>(*_mainDeck.m_pDeck, *_bufDeck.m_pDeck);
}

int CardsCount(const CardDeck _deck)
{
	return TemplateQueueCountOfElements<>(*_deck.m_pDeck);
}
