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

//#using <mscorlib.dll>
//#using <System.dll>
//#using <System.Windows.Forms.dll>
//#using <System.Data.dll>
//#using <System.Drawing.dll>

#define APIENTRY WINAPI

//using namespace System;
//using namespace System::Windows::Forms;
//using namespace System::ComponentModel;
//using namespace System::Collections;
//using namespace System::Data;
//using namespace System::Drawing;
using namespace winHome;



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PWSTR pCmdLine, int nCmdShow)
{
	/* Instanciation de twitCurl */
	twitCurl twitterObj;
    std::string tmpStr, tmpStr2;
    std::string replyMsg;
    char tmpBuf[1024];

	//System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(new windowHome());
	return 0;
}