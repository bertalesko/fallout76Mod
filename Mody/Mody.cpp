#include <iostream>
#include <windows.h>
#include "ini.h"



using namespace std;
HWND okno = NULL;
//string coJest = NULL;
//string tekstCoJest[2] = { "Mody wlaczone", "Mody wylaczone" };

int wlaczMody(LPCSTR newName)
{
	char oldname[] = "mody.ini";
	
	if (!CopyFileA(oldname, newName, FALSE))
	{
		cout << "Blad Przenoszenia Pliku : " << GetLastError() << endl;

	}

	else
	{
		cout << "Mody Wlaczone" << endl;
	}
	return 0;
}

int wylaczMody(LPCSTR newName)
{

	char oldname[] = "czysty.ini";
	

	if (!CopyFileA(oldname, newName, FALSE))
	{
		cout << "Blad Przenoszenia Pliku : " << GetLastError() <<endl;
	
	}
	else
	{
		cout << "Mody Wylaczone" << endl;
	}

	return 0;

	
}


bool SingleKeyToggle(DWORD KeyCode, bool* KeyToggle)
{
	if (GetAsyncKeyState(KeyCode))
	{
		if (!*KeyToggle)
		{
			*KeyToggle = true;
			return true;
		}
	}
	else
	{
		if (*KeyToggle)
		{
			*KeyToggle = false;
			return false;
		}
	}

	return false;
}

bool DoubleKeyToggle(DWORD KeyCodeA, DWORD KeyCodeB, bool* KeyToggle)
{
	if (GetAsyncKeyState(KeyCodeA))
	{
		return SingleKeyToggle(KeyCodeB, KeyToggle);
	}

	if (GetAsyncKeyState(KeyCodeB))
	{
		return SingleKeyToggle(KeyCodeA, KeyToggle);
	}

	return false;
}

bool sprawdz(HWND ok, char* nazwa)
{
	//funkcja sprawdza czy jest okno gry aby nie robic nic z wlaczona gra
	if(ok) 
	{
		cout << "Wylacz " << nazwa << " aby kontynowac.\nZamykam."<< endl;
		
		cin.get();
		return true;
	}
	return false;
}

string GetDirectory()
{

	// first, create a file instance
	mINI::INIFile file("myfile.ini");

	// next, create a structure that will hold data
	mINI::INIStructure ini;

	// now we can read the file
	file.read(ini);
	string gameDirectory = ini.get("GdzieGra").get("Directory");
	//coJest = ini.get("GdzieGra").get("Aktualnie");


	// finally we are returning read value
	return gameDirectory;
	
}
/*
void wypiszCoJest(string coJest)
{

	if (coJest == "0")
	{
		printf("%s \n", tekstCoJest[0]);
	}
	if (coJest == "1")
	{
		printf("%s \n", tekstCoJest[1]);
	}
}*/

int main()

{

	bool OneKeyToggle = false;
	bool TwoKeyToggle = false;
	bool ThreeKeyToggle = false;
	char nazwaOkna[] = "Fallout76";


	string newName = GetDirectory();
	LPCSTR direc = newName.c_str();

	okno = FindWindowA(0, (LPCSTR)(nazwaOkna)); // nazwa okna

	cout << "Shift + 1. Wylacz mody" << endl;
	cout << "Shift + 2. Wlacz mody" << endl;
	cout << "END. aby zakonczyc\n" << endl;
	cout << "====================\n" << endl;
	//wypiszCoJest(coJest);


	if (sprawdz(okno, nazwaOkna))
	{
		return 0;
	}
	
	while (!GetAsyncKeyState(VK_END))
	{





		if (DoubleKeyToggle(VK_SHIFT, '1', &ThreeKeyToggle))
		{
			wylaczMody(direc);

			Sleep(666);

		}
		if (DoubleKeyToggle(VK_SHIFT, '2', &ThreeKeyToggle))
		{
			wlaczMody(direc);

			Sleep(666);

		}
	}
	cout << "Wylaczam" << endl;
	cin.get();
}
