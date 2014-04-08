#pragma once

#include "stdafx.h"
#include "windows.h"
#include "tchar.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>

using namespace std;

namespace winPin {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public __gc class windowPin : public System::Windows::Forms::Form
	{
	public:
		windowPin(void)
		{
			InitializeComponent();
		}

	protected:
		~windowPin()
		{
			//if (components)
			//{
			//	delete components;
			//}
		}

	public:
		System::ComponentModel::Container*		components;
		System::Windows::Forms::Button*			btOK;
		System::Windows::Forms::TextBox*		tbPin;
		System::Windows::Forms::Label*			lbTexte;
		

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// main form settings
				this->components = new System::ComponentModel::Container();
				this->Size = System::Drawing::Size(200,200);
				this->BackColor = System::Drawing::Color::LightSkyBlue;
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
				this->Text = "Pin";
				//icon
				Bitmap* imgIcon = new Bitmap( "../img/EasyTwitterManager.ico" );
				IntPtr Hicon = imgIcon->GetHicon();
				System::Drawing::Icon* iconETM = System::Drawing::Icon::FromHandle(Hicon);
				this->Icon = iconETM;

			// enter your pin..... title (label)
				this->lbTexte = new System::Windows::Forms::Label();
				this->lbTexte->AutoSize = true;
				this->lbTexte->Font = new System::Drawing::Font(L"Open Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbTexte->ForeColor = System::Drawing::Color::White;
				this->lbTexte->Location = System::Drawing::Point(10, 10);
				this->lbTexte->Name = L"lbTexte";
				this->lbTexte->Size = System::Drawing::Size(94, 27);
				//this->lbTexte->TabIndex = 4;
				this->lbTexte->Text = L"Entrez le PIN généré :";

			// text box used to set up the pin auth
				this->tbPin = new System::Windows::Forms::TextBox();
				this->tbPin->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->tbPin->Font = new System::Drawing::Font(L"Open Sans", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->tbPin->Location = System::Drawing::Point(5, 40);
				this->tbPin->Name = L"tbPin";
				this->tbPin->Size = System::Drawing::Size(185, 40);
				this->tbPin->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				this->tbPin->TabIndex = 5;

			// btOK, to log in twitter using twitcurl
				this->btOK = new System::Windows::Forms::Button();
				//this->btOK->BackColor = System::Drawing::Color::LightSkyBlue;	
				//this->btOK->Image = System::Drawing::Image::FromFile("../img/ic_login.png");
				this->btOK->Text = "OK";
				this->btOK->Location = System::Drawing::Point(75, 130);
				this->btOK->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btOK->ForeColor = System::Drawing::Color::White;
				this->btOK->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btOK->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btOK->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btOK->FlatAppearance->BorderSize = 0;
				this->btOK->Name = L"btOK";
				this->btOK->Size = System::Drawing::Size(50, 30);
				this->btOK->TabIndex = 3;
				this->btOK->UseVisualStyleBackColor = false;
				this->btOK->Click += new System::EventHandler(this, &windowPin::btOK_Click);

			// adding the controls to the window
				this->Controls->Add(this->tbPin);
				this->Controls->Add(this->btOK);
				this->Controls->Add(this->lbTexte);
				this->SuspendLayout();
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion
	public: System::Void btOK_Click(System::Object* sender, System::EventArgs* e)
			{
				extern string tmpStr;
				String* pin = this->tbPin->Text;
				MarshalString(pin, tmpStr);
				this->Close();
			}

void MarshalString ( String* s, string& os )
			{
			   using namespace Runtime::InteropServices;
			   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			   os = chars;
			   Marshal::FreeHGlobal(IntPtr((void*)chars));
			}
	};
}