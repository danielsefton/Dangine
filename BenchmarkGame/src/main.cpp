//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// TODO: Refactor this file into the Engine class. This is not important for now.
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Input/Input.h"
#include "Game.h"
#include "Util/Helper/ConfigFile.h"
#include <RakNet/Kbhit.h>

using namespace Dangine;

//-----------------------------------------------------------------------------
Game* gGame = NULL;
bool gQuit = false;
//------------------------------------------------------------------------------
VOID Cleanup()
{
	if (gGame != NULL)
		delete gGame;
	gGame = NULL;
}
//------------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			Cleanup();
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//------------------------------------------------------------------------------
BOOL CtrlHandler(DWORD fdwCtrlType)
{
	(void)fdwCtrlType;
	gQuit = true;
	return TRUE;
}
//------------------------------------------------------------------------------
int main(int DG_UNUSED(argc), const char* DG_UNUSED(argv)) 
{
	Config config("config.ini");

	gGame = new Game(config);
	
	String networkMode = config.read<String>("network_mode");
	if (networkMode == "client")
	{
		// Register the window class
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			"Dangine", NULL
		};
		RegisterClassEx(&wc);

		RECT wr = {0, 0, 1024, 768};	// set the size, but not the position
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);	// adjust the size

		// Create the application's window
		HWND hWnd = CreateWindow( wc.lpszClassName, "Dangine",
								  WS_OVERLAPPEDWINDOW, 100, 100,  wr.right - wr.left, wr.bottom - wr.top,
								  NULL, NULL, wc.hInstance, NULL );

		if (gGame->initialiseClient(hWnd))
		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// Enter the message loop
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					gGame->updateClient();

					std::stringstream ss;
					ss << "Dangine - " << gGame->getStats().lastFPS << " FPS";
					SetWindowText(hWnd, ss.str().c_str());
				}
			}
		}

		UnregisterClass(wc.lpszClassName, wc.hInstance);
	}
	else if (networkMode == "server")
	{
		// Set the console title
		SetConsoleTitle("Dangine Server");

		// Handle to write to the console.
		HANDLE wHnd;

		// Set up the handles for reading/writing:
		wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

		// Set up the required window size:
		COORD windowBufferSize = {100, 300};

		WORD word = (FOREGROUND_RED | FOREGROUND_GREEN);

		SetConsoleScreenBufferSize(wHnd, windowBufferSize);
		SetConsoleTextAttribute(wHnd, word);
		SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandler, TRUE);

		if (gGame->initialiseServer())
		{
			while (!gQuit)
			{
				gGame->updateServer();

#if DANGINE_PLATFORM == DANGINE_PLATFORM_WIN32
				Sleep(10);
#else
				usleep(10 * 1000.0 );
#endif

				if (_kbhit())
				{
					int ch = _getch();
					if (ch == 'q')
						gQuit = true;
				}
			}
		}
	}

	LOG(logINFO) << "Shutting down...";

	delete gGame;
	
	return 0;
}