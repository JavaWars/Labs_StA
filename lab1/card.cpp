#include "card.h"
bool isFirstCardBigger(const Card & _card1, const Card & _card2)
{
	if (_card1.m_pNumberCard == CardNumber[0] && _card2.m_pNumberCard == CardNumber[8]) return true;
	else
	{
		int powerFirst, powerSecond;
		for (int i = 0; i < sizeof(CardNumber) / sizeof(char*); i++)
		{
			if (_card1.m_pNumberCard == CardNumber[i]) powerFirst = i;
			if (_card2.m_pNumberCard == CardNumber[i]) powerSecond = i;
		}
		if (powerFirst > powerSecond) return true;
	}
	return false;
}

bool isCardPowerSame(const Card & _card1, const Card & _card2)
{
	if (_card1.m_pNumberCard == _card2.m_pNumberCard) return true;
	return false;
}

std::wofstream & operator<<(std::wofstream & os, const Card & _card)
{
	os << _card.m_pNumberCard << ' ' << _card.m_colorCard;
	return os;
}

void test(std::wofstream & _wofstream)
{

	Card c1, c2, c3,c4;
	c1.m_pNumberCard = CardNumber[4];
	c1.m_colorCard = CardColor[2];

	c2.m_pNumberCard = CardNumber[4];
	c2.m_colorCard = CardColor[3];

	c3.m_pNumberCard = CardNumber[8];//A
	c3.m_colorCard = CardColor[0];

	c4.m_pNumberCard = CardNumber[0];//6
	c4.m_colorCard = CardColor[0];

	_wofstream <<c1<< c2 << isFirstCardBigger(c1, c2) << std::endl;
	_wofstream << c2<<c3 << isFirstCardBigger(c1, c2) << std::endl;
	_wofstream << c3<<c1 << isFirstCardBigger(c3, c2) << std::endl;
	_wofstream << c4 << c3 << isFirstCardBigger(c4, c3) << std::endl;
	_wofstream << c1 << c2 << isCardPowerSame(c1, c2) << std::endl;
}
