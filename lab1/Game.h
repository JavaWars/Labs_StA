#ifndef _GAME_
#define _GAME_

//for unicode support
#include <locale>
#include <codecvt>
#include <fcntl.h>
#include <io.h>

#include "CardDeck.h"

void emulatedRandomGame(char *fileName);

std::wofstream someMagic(char *fileName);

void titleToFile(std::wofstream & _wofstream);

void PrintStep(std::wofstream & _wofstream,int _step,int _countCardP1,int _countCardP2, const Card & _cardP1,const Card & _cardP2);

void gameIsTooLong(std::wofstream & _wofstream);

void  Winner(std::wofstream & _wofstream,int playerNumber);
#endif //_GAME_
