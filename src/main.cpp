// main.cpp : point d'entrée de l'application

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
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	windowHome* wHome = new windowHome();

	/* twitCurl initialization */
	twitCurl twitterObj;

	/* database initialization */
	String* sCon = "Provider=Microsoft.SQLSERVER.CE.OLEDB.3.5;Data Source=c:\temp\sqlcompact.sdf;";


	/* running app */
	Application::Run(wHome);

	return 0;
}

void connection_database()
{
	

}