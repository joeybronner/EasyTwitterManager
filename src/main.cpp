// main.cpp�: point d'entr�e de l'application

#include "stdafx.h"
#include "..\include\twitcurl.h"
#include "affichage.h"
#include "windows.h"
#include "tchar.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include "winHome.h"
#include <iostream>
#include <fstream>

#define APIENTRY WINAPI

using namespace winHome;
using namespace std;



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PWSTR pCmdLine, int nCmdShow)
{
	/* Instanciation de twitCurl */
	twitCurl twitterObj;
    string tmpStr, tmpStr2;
    string replyMsg;
    char tmpBuf[1024];

	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	windowHome* wHome = new windowHome();
	Application::Run(wHome);

	return 0;
}