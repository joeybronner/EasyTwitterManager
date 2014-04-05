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

namespace winHome {

	using namespace System;
	using namespace System::IO;
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
				//icon
				Bitmap* imgIcon = new Bitmap( "../img/EasyTwitterManager.ico" );
				IntPtr Hicon = imgIcon->GetHicon();
				System::Drawing::Icon* iconETM = System::Drawing::Icon::FromHandle( Hicon );
				this->Icon = iconETM;

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
				String* currentDate = getDateTime();
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

				if (this->tbAccount->Text->Length > 0)
				{
					String* actualContent;

					// adding value to the file
					String* fileName = "../files/tofollow.txt";
					String* line;
					int count = 0;
					try 
					{
						// reading file
						StreamReader* sr = new StreamReader(fileName);
						while (line = sr->ReadLine())
						{
							actualContent = line;
						}
						sr->Close();

						// writing file
						StreamWriter* sw = new StreamWriter(fileName);
						sw->Write(actualContent);
						sw->Write("|");
						sw->Write(toAdd);
						sw->Close();

						// logs and msgbox 
						String* msgAjout = getDateTime();
						msgAjout = String::Concat(msgAjout,"Ajout de ",toAdd," à la file d'attente.");
						this->consoleFooter->Items->Add(msgAjout);
						//MessageBox::Show("Mise à jour du fichier effectuée avec succès.");
					}
					catch (Exception* e)
					{
						MessageBox::Show("Erreur lors de l'ajout.");
					}
					
					// deleting the value in textbox
					this->tbAccount->Text = "";
				}
			}

	public: System::String* getDateTime()
			{
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
				/* hour */
				int heur = lt->tm_hour;
				String* Sheur;
				if (heur<10) { Sheur = String::Concat("0",heur.ToString()); } else { Sheur = heur.ToString(); } 
				/* minutes */
				int minu = lt->tm_min;
				String* Sminu;
				if (minu<10) { Sminu = String::Concat("0",minu.ToString()); } else { Sminu = minu.ToString(); } 
				/* secondes */
				int seco = lt->tm_sec;
				String* Sseco;
				if (seco<10) { Sseco = String::Concat("0",seco.ToString()); } else { Sseco = seco.ToString(); } 
				/* concat */
				String* retour =	String::Concat(Sjour,"/",Smois,"/");
				retour = String::Concat(retour,anne.ToString()," - ");
				retour = String::Concat(retour,Sheur,":");
				retour = String::Concat(retour,Sminu,":");
				retour = String::Concat(retour,Sseco," - ");
				return retour;
			}
	};
}