#ifndef SOURCE_CPP
#define SOURCE_CPP
#include "TicTacToe.h"

using std::string;
using TicTakToe::Core;

static const int Length = 9;
static Core Game;

BOOL CALLBACK MenuEventHandler (HWND DialogDescriptor, UINT Message, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain (HINSTANCE ApplicationDescriptor, HINSTANCE PreviousDescriptor, LPSTR CommandLine, int CmdShow)
{
	DialogBox (ApplicationDescriptor, MAKEINTRESOURCE (IDD_MENU), NULL, MenuEventHandler);
	return 0;
}
BOOL CALLBACK MenuEventHandler (HWND DialogDescriptor, UINT Message, WPARAM wParam, LPARAM lParam)
{
	static bool PC = false;
	static HICON hIcon;
	static HBITMAP X = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_X)); 
	static HBITMAP O = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_O));
	static DWORD BUTTONS [Length] = {IDC_BUTTON1, IDC_BUTTON2, IDC_BUTTON3, IDC_BUTTON4,
									IDC_BUTTON5, IDC_BUTTON6, IDC_BUTTON7, IDC_BUTTON8, IDC_BUTTON9};
	switch (Message)
	{
	case WM_INITDIALOG:
		SetClassLong (DialogDescriptor, GCL_HICON, LONG(hIcon));
		CheckDlgButton (DialogDescriptor, IDC_RADIO_O, BST_CHECKED);
		Game.ClearMap();
		SetDlgItemText (DialogDescriptor, IDC_GROUP, (string ()+"Current: \""+Game.GetCurrentSymbol()+"\"").c_str());
		return TRUE;
	case WM_TIMER:
		{
			if (PC == true && !IsWindowEnabled (GetDlgItem (DialogDescriptor, IDC_BUTTON_MODE))) {
				PC = false;
				KillTimer (DialogDescriptor, 1);
				int i =	Game.GetMove();
				if (i == -1)
					MessageBox (DialogDescriptor, "Internal core error", "ERROR", MB_ICONERROR | MB_OK);
				if (Game.GetCurrentSymbol() == 'X')
					SendMessage (GetDlgItem (DialogDescriptor, BUTTONS[i]), BM_SETIMAGE, WPARAM(IMAGE_BITMAP),LPARAM(X));
				else
					SendMessage (GetDlgItem (DialogDescriptor, BUTTONS[i]), BM_SETIMAGE, WPARAM(IMAGE_BITMAP),LPARAM(O));
				if (Game.CheckWin () || Game.CheckDraw ())
				{
					if (Game.CheckWin ())
						MessageBox (DialogDescriptor, (string ("Won player: \"") + Game.GetCurrentSymbol() +"\"").c_str(), "End of Game", MB_ICONINFORMATION | MB_OK);
					else
						MessageBox (DialogDescriptor, "Draw", "End of Game", MB_ICONINFORMATION | MB_OK);
					for (int i = 0; i < Length; i++)
					{
						SendMessage (GetDlgItem (DialogDescriptor, BUTTONS[i]), BM_SETIMAGE, WPARAM(IMAGE_BITMAP),NULL);
					}
					EnableWindow (GetDlgItem (DialogDescriptor, IDC_RADIO_X), TRUE);
					EnableWindow (GetDlgItem (DialogDescriptor, IDC_RADIO_O), TRUE);
					EnableWindow (GetDlgItem (DialogDescriptor, IDC_BUTTON_MODE), TRUE);
					Game.ClearMap ();
					return TRUE;
				}
				Game.SetCurrentSymbol(Game.Next ());
				SetDlgItemText (DialogDescriptor, IDC_GROUP, (string ()+"Current: \""+Game.GetCurrentSymbol()+"\"").c_str());
			}
			return TRUE;
		}
	case WM_CLOSE:
		EndDialog (DialogDescriptor, NULL);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD (wParam) == IDC_RADIO_X && IsDlgButtonChecked (DialogDescriptor, IDC_RADIO_X))
		{
			Game.SetCurrentSymbol('X');
			SetDlgItemText (DialogDescriptor, IDC_GROUP, (string ()+"Current: \""+Game.GetCurrentSymbol()+"\"").c_str());
			return TRUE;
		}
		if (LOWORD (wParam) == IDC_RADIO_O && IsDlgButtonChecked (DialogDescriptor, IDC_RADIO_O))
		{
			Game.SetCurrentSymbol('O');
			SetDlgItemText (DialogDescriptor, IDC_GROUP, (string ()+"Current: \""+Game.GetCurrentSymbol()+"\"").c_str());
			return TRUE;
		}
		if (LOWORD (wParam) == IDC_BUTTON_MODE)
		{
			if (PC == true)
			{
				PC = false;
				SetDlgItemText (DialogDescriptor, IDC_BUTTON_MODE, "User");
			}
			else 
			{
				PC = true;
				SetDlgItemText (DialogDescriptor, IDC_BUTTON_MODE, "PC");
				SetTimer (DialogDescriptor, 1, 2000, NULL);
			}
			return TRUE;
		}
		if (PC == false)
		{
			for (int i = 0; i < Length; i++)
			{
				if (LOWORD (wParam) == BUTTONS[i])
				{
					if (SendMessage (GetDlgItem (DialogDescriptor, BUTTONS[i]), BM_GETIMAGE, NULL, NULL) == NULL)
					{
						if (Game.GetCurrentSymbol() == 'X')
							SendMessage (GetDlgItem (DialogDescriptor, BUTTONS[i]), BM_SETIMAGE, WPARAM(IMAGE_BITMAP),LPARAM(X));
						else
							SendMessage (GetDlgItem (DialogDescriptor, BUTTONS[i]), BM_SETIMAGE, WPARAM(IMAGE_BITMAP),LPARAM(O));
					Game.SetMap (i, Game.GetCurrentSymbol());
					}
				}
			}
			if (Game.CheckWin () || Game.CheckDraw ())
			{
				if (Game.CheckWin ())
					MessageBox (DialogDescriptor, (string ("Won player: \"") + Game.GetCurrentSymbol() +"\"").c_str(), "End of Game", MB_ICONINFORMATION | MB_OK);
				else
					MessageBox (DialogDescriptor, "Draw", "End of Game", MB_ICONINFORMATION | MB_OK);
				for (int i = 0; i < Length; i++)
				{
					SendMessage (GetDlgItem (DialogDescriptor, BUTTONS[i]), BM_SETIMAGE, WPARAM(IMAGE_BITMAP),NULL);
				}
				EnableWindow (GetDlgItem (DialogDescriptor, IDC_RADIO_X), TRUE);
				EnableWindow (GetDlgItem (DialogDescriptor, IDC_RADIO_O), TRUE);
				EnableWindow (GetDlgItem (DialogDescriptor, IDC_BUTTON_MODE), TRUE);
				Game.ClearMap ();
				return TRUE;
			}
			Game.SetCurrentSymbol(Game.Next ());
			SetDlgItemText (DialogDescriptor, IDC_GROUP, (string ()+"Current: \""+Game.GetCurrentSymbol()+"\"").c_str());
		}
		if (IsWindowEnabled (GetDlgItem (DialogDescriptor, IDC_BUTTON_MODE)))
		{
			EnableWindow (GetDlgItem (DialogDescriptor, IDC_BUTTON_MODE), FALSE);
			EnableWindow (GetDlgItem (DialogDescriptor, IDC_RADIO_X), FALSE);
			EnableWindow (GetDlgItem (DialogDescriptor, IDC_RADIO_O), FALSE);
		}
		PC = true;
		SetTimer (DialogDescriptor, 1, 2000, NULL);
		return TRUE;
	}
	return FALSE;
}
#endif