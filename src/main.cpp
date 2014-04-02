// main.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "..\include\twitcurl.h"
#include "affichage.h"
#include "windows.h"
#include "tchar.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>


#define APIENTRY WINAPI

using namespace System;
using namespace System::Windows::Forms;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;


public __gc class fenetreAccueil : public System::Windows::Forms::Form
{  
	public:
	fenetreAccueil(void)
	{
		InitializeComponent();
	}

	private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container * components;
	System::Windows::Forms::Button *  button1;

	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
			// main form settings
			this->components = new System::ComponentModel::Container();
			this->Size = System::Drawing::Size(800,600);
			this->Text = "Accueil";


			// button settings
			this->button1 = new System::Windows::Forms::Button();
			//this->SuspendLayout();
			this->button1->Location = System::Drawing::Point(109, 113);
			this->button1->Name = L"Test";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Test";
			this->button1->UseVisualStyleBackColor = true;

			// adding the controls to the window
			this->Controls->Add(this->button1);
	}  
};



//void __stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,long lpCmdLine,int nCmdShow)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PWSTR pCmdLine, int nCmdShow)
{
	/* Instanciation de twitCurl */
	twitCurl twitterObj;
    std::string tmpStr, tmpStr2;
    std::string replyMsg;
    char tmpBuf[1024];

	//http://msdn.microsoft.com/en-us/library/aa290064(VS.71).aspx
	//System::Windows::Forms::MessageBox::Show("Hello, Windows Forms");
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;Application::Run(new fenetreAccueil());
	return 0;
}

/*

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

  MSG  msg;    
  HWND hwnd;
  WNDCLASSW wc;
	
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.lpszClassName = L"Window";
  wc.hInstance     = hInstance;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpszMenuName  = NULL;
  wc.lpfnWndProc   = WndProc;
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);



	/* Démarrage de la console */

/*
	AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;

	

	printf("Demarrage de la console...\n\n");
	system("PAUSE");
/*
	HWND CreateWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, 
	int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, 
	HINSTANCE hInstance, LPVOID lpParam);
*/
	//MessageBox::Show( "Working", "Info",    MessageBoxButtons::OK, MessageBoxIcon::Exclamation );

   //return 0;
//}