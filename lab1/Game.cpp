#include "Game.h"

void emulatedRandomGame(char *fileName)
{

	CardDeck *pCardDeckPlayer1 = CreateEmptyCardDeck(),
		*pCardDeckPlayer2 = CreateEmptyCardDeck(),
		*pCardDeckTable = CreateCardDeck();

	Mix(*pCardDeckTable);
	DivFor2Players(*pCardDeckTable, *pCardDeckPlayer1, *pCardDeckPlayer2, false);
	
	std::cout << CardsCount(*pCardDeckTable)<<" ";
	std::cout << CardsCount(*pCardDeckPlayer1)<<" ";
	std::cout << CardsCount(*pCardDeckPlayer2)<<"\n";

	std::wofstream w = someMagic(fileName);
	titleToFile(w);

	int progress = 0;
	while ((progress < 5000) &&					//max 5000 step
		(CardsCount(*pCardDeckPlayer1) != 0) &&	//player 1 no cards
		(CardsCount(*pCardDeckPlayer2) != 0))	//player 2 no cards
	{
		progress++;
		std::cout << progress << "\t";

		Card *cardPlayer1 = &GetFirsCard(*pCardDeckPlayer1),
			*cardPlayer2 = &GetFirsCard(*pCardDeckPlayer2);

		//cards to the cardDeck
		AddCards(*pCardDeckTable, *cardPlayer1, *cardPlayer2);

		PrintStep(w, progress, CardsCount(*pCardDeckPlayer1), CardsCount(*pCardDeckPlayer2), *cardPlayer1, *cardPlayer2);
		if (!isCardPowerSame(*cardPlayer1, *cardPlayer2))
		{
			if (isFirstCardBigger(*cardPlayer1, *cardPlayer2))
			{
				//1 player take cards
				AddCards(*pCardDeckPlayer1, *pCardDeckTable);
				std::cout << "1>2";
			}
			else
			{
				//2 player take cards
				AddCards(*pCardDeckPlayer2, *pCardDeckTable);
				std::cout << "1<2";
			}
		}
		else
		{
			if ((CardsCount(*pCardDeckPlayer1) != 0) &&	//player 1 has cards
				(CardsCount(*pCardDeckPlayer2) != 0))
			{
				progress++;
				AddCards(*pCardDeckTable, GetFirsCard(*pCardDeckPlayer1), GetFirsCard(*pCardDeckPlayer2));
				w <<progress<<"\t"<<"unknown card\n";
			}
		}
		std::cout << std::endl;
	}//end game

	std::cout << "Game is Over see log file:" << fileName <<" for  more info"<< std::endl;

	if (progress == 5000)
	{
		gameIsTooLong(w);
	}
	else
	{
		if (CardsCount(*pCardDeckPlayer1) == 0 && CardsCount(*pCardDeckPlayer2) == 0) Winner(w,0);
		else
		{
			if (CardsCount(*pCardDeckPlayer1) != 0 && CardsCount(*pCardDeckPlayer2) == 0) Winner(w,1);
			if (CardsCount(*pCardDeckPlayer2) != 0 && CardsCount(*pCardDeckPlayer1) == 0) Winner(w, 2);
		}
	}
}

std::wofstream someMagic(char * fileName)
{
	//for unicode in file
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	std::wofstream f(fileName);
	f.imbue(utf8_locale);
	return f;
}

void titleToFile(std::wofstream & _wofstream)
{
	_wofstream << "step\t" << "cards\t" << "CardPl1\t" << "CardPl2\t" << "who take?\n";
}

void PrintStep(std::wofstream & _wofstream, int _step, int _countCardP1, int _countCardP2, const Card & _cardP1, const Card & _cardP2)
{
	_wofstream << _step << "\t" << _countCardP1 << "/" << _countCardP2 << "\t";
	_wofstream << _cardP1 << "\t";
	_wofstream << _cardP2 << "\t";
	_wofstream << (!isCardPowerSame(_cardP1, _cardP2)? ((isFirstCardBigger(_cardP1, _cardP2)) ? "1 take" : "2 take") :"nobody") ;
	_wofstream << "\n";
}

void gameIsTooLong(std::wofstream & _wofstream)
{
	_wofstream << "game is too long\n";
}

void Winner(std::wofstream & _wofstream, int playerNumber)
{
	if (playerNumber == 0)
	{
		_wofstream << " NO Winner =( \n";
	}
	else 
	{
		_wofstream << playerNumber << " Win!\n";
	}
}
