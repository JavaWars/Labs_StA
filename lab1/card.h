#ifndef _CARD_
#define _CARD_

#include <fstream>

static const char* CardNumber[] = { "6","7","8","9","10","J","D","K","A" };
static const wchar_t CardColor[] = { L'♠', L'♥', L'♣', L'♦' };

struct Card
{
	wchar_t m_colorCard;//♠ ♥ ♣ ♦ = Unicode
	const char *m_pNumberCard;
};

bool isFirstCardBigger(const Card & _card1, const Card & _card2);

bool isCardPowerSame(const Card & _card1, const Card & _card2);

std::wofstream & operator<<(std::wofstream & os, const Card & _card);

void test(std::wofstream & _wofstream);

#endif // _CARD_