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
#include <iostream>
#include <fstream>


#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>

using namespace std;

namespace winHome {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public __gc class windowHome : public System::Windows::Forms::Form
	{
	public:
		windowHome(void)
		{
			InitializeComponent();
		}

	protected:
		~windowHome()
		{
			//if (components)
			//{
			//	delete components;
			//}
		}

	public:
		System::ComponentModel::Container*		components;
		System::Windows::Forms::Button*			btAddAccount;
		System::Windows::Forms::PictureBox*		imageLogo;
		System::Windows::Forms::ListBox*		consoleFooter;
		System::Windows::Forms::TextBox*		tbAccount;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// main form settings
				this->components = new System::ComponentModel::Container();
				this->Size = System::Drawing::Size(800,600);
				this->BackColor = System::Drawing::Color::LightSkyBlue;
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				this->Text = "Easy Twitter Manager | Home";

			// button settings
				this->btAddAccount = new System::Windows::Forms::Button();
				this->btAddAccount->Location = System::Drawing::Point(120, 200);
				this->btAddAccount->Name = L"btAddAccount";
				this->btAddAccount->Size = System::Drawing::Size(50, 20);
				this->btAddAccount->TabIndex = 0;
				this->btAddAccount->Text = L"Ajouter";
				this->btAddAccount->UseVisualStyleBackColor = true;
				this->btAddAccount->Click += new System::EventHandler(this, &windowHome::btAddAccount_Click);

			// logo on the top of window
				this->imageLogo = new System::Windows::Forms::PictureBox();
				this->imageLogo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->imageLogo->Location = System::Drawing::Point(10, 10);
				this->imageLogo->Name = L"imageLogo";
				this->imageLogo->Size = System::Drawing::Size(770, 120);
				this->imageLogo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
				this->imageLogo->Image = System::Drawing::Image::FromFile("../img/logo_home_window.png");
				this->imageLogo->TabIndex = 0;
				this->imageLogo->TabStop = false;

			// textbox account for add someone to the list of people to follow
				this->tbAccount = new System::Windows::Forms::TextBox();
				this->tbAccount->Location = System::Drawing::Point(10, 200);
				this->tbAccount->Name = L"tbAccount";
				this->tbAccount->Size = System::Drawing::Size(100, 20);
				this->tbAccount->Text = L"Initialisation";
				this->tbAccount->TabIndex = 3;

			// console footer
				this->consoleFooter = new System::Windows::Forms::ListBox();
				this->consoleFooter->FormattingEnabled = true;
				this->consoleFooter->Location = System::Drawing::Point(10, 460);
				this->consoleFooter->Name = L"consoleFooter";
				this->consoleFooter->Size = System::Drawing::Size(770, 100);
				this->consoleFooter->Sorted = true;
				this->consoleFooter->TabIndex = 2;
				/* initializing with the current hour and date */
				time_t	now		=	time(0); 
				tm*		lt		=	localtime(&now);
				/* day */
				int jour = lt->tm_mday;
				String* Sjour;
				if (jour<10) { Sjour = String::Concat("0",jour.ToString()); } else { Sjour = jour.ToString(); } 
				/* month */
				int mois = lt->tm_mon + 1;
				String* Smois;
				if (mois<10) { Smois = String::Concat("0",mois.ToString()); } else { Smois = mois.ToString(); } 
				/* year */
				int anne = lt->tm_year + 1900;
				/* concat */
				String* currentDate =	String::Concat(Sjour,"/",Smois,"/");
				currentDate = String::Concat(currentDate,anne.ToString()," - ");
				String* initMsg = String::Concat(currentDate,"Initialisation de la fenêtre d'accueil.");
				this->consoleFooter->Items->Add(initMsg);

			// adding the controls to the window
				this->SuspendLayout();
				this->Controls->Add(this->btAddAccount);
				this->Controls->Add(this->imageLogo);
				this->Controls->Add(this->consoleFooter);
				this->Controls->Add(this->tbAccount);
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion
	public: System::Void btAddAccount_Click(System::Object* sender, System::EventArgs* e)
			{
				// get the tb value
				String* toAdd = this->tbAccount->Text;

				// adding value to the file
				ofstream myfile ("../files/tofollow.txt");
				if (myfile.is_open())
				{
					myfile << "Ce que contient test (depuis winForm) : " << toAdd << "\n";
					myfile.close();
				}
				MessageBox::Show("Utilisateur ajouté avec succès à la file d'attente.");
				
				// deleting the value in textbox
				this->tbAccount->Text = "";
			}
	};
}