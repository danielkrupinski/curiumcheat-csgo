// Junk code
#include "JunkCode.h"

// General shit
#include "Utilities.h"

// Injection stuff
#include "INJ/ReflectiveLoader.h"

// Stuff to initialise
#include "Offsets.h"
#include "Interfaces.h"
#include "Hooks.h"
#include "RenderManager.h"
#include "Hacks.h"
#include "Menu.h"
#include "AntiAntiAim.h"


// Used as part of the reflective DLL injection
extern HINSTANCE hAppInstance;

// Our DLL Instance
HINSTANCE HThisModule;
bool DoUnload;

// Our thread we use to setup everything we need
// Everything appart from code in hooks get's called from inside 
// here.

int InitialThread()
{
	// Initialise all our shit
	Offsets::Initialise(); // Set our VMT offsets and do any pattern scans
	Interfaces::Initialise(); // Get pointers to the valve classes
	NetVar.RetrieveClasses(); // Setup our NetVar manager (thanks shad0w bby)
	NetvarManager::Instance()->CreateDatabase();
	Render::Initialise();
	Hacks::SetupHacks();
	Menu::SetupMenu();
	Hooks::Initialise();
	ApplyAAAHooks();

	// While our cheat is running
	// Junk code every 1 sec
	while (DoUnload == false)
	{
		yacA();
		Gqwk();
		Dilm();
		iPIf();
		CkIw();
		Ygsi();
		InSj();
		xIU();
		mhdg();
		QzOl();
		KzTL();
		GIjf();
		LCw();
		CUy();
		RYu();
		qyZ();
		ccdL();
		xke();
		GJi();
		niUD();
		Sleep(1000);
	}

	Hooks::UndoHooks();
	Sleep(2000); // Make sure none of our hooks are running
	FreeLibraryAndExitThread(HThisModule, 0);

	return 0;
}

// DllMain
// Entry point for our module
BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_QUERY_HMODULE:
		if (lpvReserved != NULL)
			*(HMODULE *)lpvReserved = hAppInstance;
		break;
	case DLL_PROCESS_ATTACH:
		HThisModule = hinstDLL;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitialThread, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
