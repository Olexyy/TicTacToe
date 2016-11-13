#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#ifdef UNICODE 
#undef UNICODE
#endif
#include <Windows.h>
#include <string>
#include "resource.h"
#include <random>
#include <ctime>

namespace TicTakToe
{
	struct Coordinates
	{
		int I, J;
	};
	class Core
	{
	private:
		char Map [3][3];
		char CurrentSymbol;
		Coordinates MoveAI;
		bool AI(char Symbol, int Number = 2);
		char GetEnemy();
	public:
		Core ();
		void ClearMap ();
		bool CheckWin ();	
		bool CheckDraw ();
		char Next ();
		char GetCurrentSymbol ();
		void SetCurrentSymbol (char Value);
		void SetMap (int Index, char Value);
		int GetMove();
	};
}
#endif