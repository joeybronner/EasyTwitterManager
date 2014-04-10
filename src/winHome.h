#pragma once

#include "stdafx.h"
#include "windows.h"
#include "tchar.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>     
#include <string>
#include <ctime>
#include <time.h>
#include "winSettings.h"
#include "winLog.h"
#include "winPin.h"

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>
#using <mscorlib.dll>

using namespace std;
using namespace winSettings;
using namespace winPin;
using namespace winLog;

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
			this->Show();
			extern bool loggedIn;
			windowLog* wLog = new windowLog();
			if (!loggedIn)
			{
				windowLog* wLog = new windowLog();
				wLog->ShowDialog();
			}
	
			/* set username */
			setUsername();

			/* get username */
			extern twitCurl twitterObj;
			extern string user;
			user = twitterObj.getTwitterUsername();
			writeConsole(String::Concat("Connecté en tant que : @", user.c_str()));

			this->lbWelcome->Text = String::Concat("Bonjour @",user.c_str(),"!");
			
			string joeybr = getUserID("joeybr");
			writeConsole(joeybr.c_str());


			string replyMsg;
			if (twitterObj.friendshipCreate(joeybr, true))
			{
				twitterObj.getLastWebResponse(replyMsg);
				writeConsole(replyMsg.c_str());
			}
			else
			{
				twitterObj.getLastCurlError( replyMsg );
				writeConsole(replyMsg.c_str());
			}




			//string replyMsg;
			//if (twitterObj.followersGet())
			//{
			//	twitterObj.getLastWebResponse( replyMsg );
			//	writeConsole(replyMsg.c_str());
			//}
			//else
			//{
			//	writeConsole("erreur");
			//}

			

			
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
		System::Windows::Forms::PictureBox*		imageLogo;
		System::Windows::Forms::ListBox*		consoleFooter;
		System::Windows::Forms::Button*			btConfig;
		System::Windows::Forms::Button*			btInfos;
		System::Windows::Forms::Button*			btLogin;
		System::Windows::Forms::TextBox*		tbNewTweet;
		System::Windows::Forms::Button*			btAddTweet;
		System::Windows::Forms::Label*			lbWelcome;
		System::Windows::Forms::Label*			lbNewTweet;


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

			// btConfig, general app settings
				this->btConfig = new System::Windows::Forms::Button();
				this->btConfig->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btConfig->Image = System::Drawing::Image::FromFile("../img/ic_settings.png");
				this->btConfig->Location = System::Drawing::Point(5, 365);
				this->btConfig->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btConfig->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btConfig->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btConfig->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btConfig->FlatAppearance->BorderSize = 0;
				this->btConfig->Name = L"btConfig";
				this->btConfig->Size = System::Drawing::Size(90, 90);
				this->btConfig->TabIndex = 3;
				this->btConfig->UseVisualStyleBackColor = false;
				this->btConfig->Click += new System::EventHandler(this, &windowHome::btConfig_Click);

			// welcome label message (label)
				this->lbWelcome = new System::Windows::Forms::Label();
				this->lbWelcome->AutoSize = true;
				this->lbWelcome->Font = new System::Drawing::Font(L"Open Sans", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbWelcome->ForeColor = System::Drawing::Color::White;
				this->lbWelcome->Location = System::Drawing::Point(100, 140);
				this->lbWelcome->Name = L"lbWelcome";
				this->lbWelcome->Size = System::Drawing::Size(94, 27);
				this->lbWelcome->BackColor = System::Drawing::Color::SteelBlue;
				//this->lbWelcome->TabIndex = 4;
				//this->lbWelcome->Text = L"Hello @Joeybr";

			// btLogin, to log in twitter using twitcurl
				this->btLogin = new System::Windows::Forms::Button();
				this->btLogin->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btLogin->Image = System::Drawing::Image::FromFile("../img/ic_logout.png");
				this->btLogin->Location = System::Drawing::Point(5, 5);
				this->btLogin->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btLogin->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btLogin->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btLogin->FlatAppearance->BorderSize = 0;
				this->btLogin->Name = L"btLogin";
				this->btLogin->Size = System::Drawing::Size(90, 90);
				this->btLogin->TabIndex = 3;
				this->btLogin->UseVisualStyleBackColor = false;
				this->btLogin->Click += new System::EventHandler(this, &windowHome::btLogin_Click);

			// btInfos, why this app has been devlopped ? who ? etc.. 
				this->btInfos = new System::Windows::Forms::Button();
				this->btInfos->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btInfos->Image = System::Drawing::Image::FromFile("../img/ic_infos.png");
				this->btInfos->Location = System::Drawing::Point(5, 465);
				this->btInfos->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btInfos->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btInfos->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btInfos->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btInfos->FlatAppearance->BorderSize = 0;
				this->btInfos->Name = L"btInfos";
				this->btInfos->Size = System::Drawing::Size(90, 90);
				this->btInfos->TabIndex = 3;
				this->btInfos->UseVisualStyleBackColor = false;

			// logo on the top of window
				this->imageLogo = new System::Windows::Forms::PictureBox();
				this->imageLogo->BackColor = System::Drawing::Color::PowderBlue;
				//this->imageLogo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->imageLogo->Location = System::Drawing::Point(100, 10);
				this->imageLogo->Name = L"imageLogo";
				this->imageLogo->Size = System::Drawing::Size(680, 120);
				this->imageLogo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
				this->imageLogo->Image = System::Drawing::Image::FromFile("../img/logo_home_window.png");
				this->imageLogo->TabIndex = 0;
				this->imageLogo->TabStop = false;

			// text box used to set up the pin auth
				this->tbNewTweet = new System::Windows::Forms::TextBox();
				this->tbNewTweet->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->tbNewTweet->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->tbNewTweet->Location = System::Drawing::Point(200, 185);
				this->tbNewTweet->Name = L"tbNewTweet";
				this->tbNewTweet->Size = System::Drawing::Size(500, 40);
				this->tbNewTweet->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
				this->tbNewTweet->MaxLength = 140;
				//this->tbNewTweet->TabIndex = 5;

			// button add tweet
				this->btAddTweet = new System::Windows::Forms::Button();
				this->btAddTweet->Location = System::Drawing::Point(710, 185);
				this->btAddTweet->Name = L"btAddTweet";
				this->btAddTweet->Size = System::Drawing::Size(70, 20);
				this->btAddTweet->TabIndex = 0;
				this->btAddTweet->Text = L"Tweeter!";
				this->btAddTweet->UseVisualStyleBackColor = true;
				this->btAddTweet->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btAddTweet->Click += new System::EventHandler(this, &windowHome::btAddTweet_Click);
				this->btAddTweet->ForeColor = System::Drawing::Color::White;
				this->btAddTweet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btAddTweet->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btAddTweet->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btAddTweet->FlatAppearance->BorderSize = 0;

			// welcome label message (label)
				this->lbNewTweet = new System::Windows::Forms::Label();
				this->lbNewTweet->AutoSize = true;
				this->lbNewTweet->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbNewTweet->ForeColor = System::Drawing::Color::White;
				this->lbNewTweet->Location = System::Drawing::Point(100, 185);
				this->lbNewTweet->Name = L"lbNewTweet";
				this->lbNewTweet->Size = System::Drawing::Size(94, 27);
				//this->lbNewTweet->BackColor = System::Drawing::Color::SteelBlue;
				//this->lbNewTweet->TabIndex = 4;
				this->lbNewTweet->Text = L"Quoi de neuf ?";

			// console footer
				this->consoleFooter = new System::Windows::Forms::ListBox();
				this->consoleFooter->FormattingEnabled = true;
				this->consoleFooter->Location = System::Drawing::Point(100, 460);
				this->consoleFooter->Name = L"consoleFooter";
				this->consoleFooter->Size = System::Drawing::Size(680, 100);
				this->consoleFooter->Sorted = true;
				this->consoleFooter->TabIndex = 2;
				this->consoleFooter->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->consoleFooter->ScrollAlwaysVisible = true;

			// adding the controls to the window
				this->SuspendLayout();
				this->Controls->Add(this->imageLogo);
				this->Controls->Add(this->btAddTweet);
				this->Controls->Add(this->consoleFooter);
				this->Controls->Add(this->tbNewTweet);
				this->Controls->Add(this->btConfig);
				this->Controls->Add(this->btInfos);
				this->Controls->Add(this->lbWelcome);
				this->Controls->Add(this->btLogin);
				this->Controls->Add(this->lbNewTweet);
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion
	public: System::Void btAddTweet_Click(System::Object* sender, System::EventArgs* e)
			{
				extern twitCurl twitterObj;
				String* test = this->tbNewTweet->Text;
				string ajout;
				MarshalString(test,ajout);
				if (twitterObj.statusUpdate(ajout))
				{
					extern string replyMsg;
					twitterObj.getLastWebResponse( replyMsg );
					writeConsole(String::Concat("ajouté : ",replyMsg.c_str()));
					tbNewTweet->Text = "";
				} else {
					writeConsole("erreur");
				}
			}


	public: System::Void btConfig_Click(System::Object* sender, System::EventArgs* e)
			{
				windowSettings* wSettings = new windowSettings();
				wSettings->ShowDialog();
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
	public: System::Void btLogin_Click(System::Object* sender, System::EventArgs* e)
			{
				windowLog* wLog = new windowLog();
				wLog->ShowDialog();
			}

	public: void writeConsole(String* msg)
			{
				String* currentDate = getDateTime();
				String* initMsg = String::Concat(currentDate,msg);
				this->consoleFooter->Items->Add(initMsg);
			}

	void MarshalString ( String* s, string& os )
			{
			   using namespace Runtime::InteropServices;
			   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			   os = chars;
			   Marshal::FreeHGlobal(IntPtr((void*)chars));
			}

	private: string ExtractString( std::string source, std::string start, std::string end )
			{
				std::string::size_type startIndex = source.find( start );

				 if( startIndex == std::string::npos )
				 {
					string emptyString = "";
	 				return emptyString;
				 }
				
				 startIndex += start.length();

				 std::string::size_type endIndex = source.find( end, startIndex );

				 return source.substr( startIndex, endIndex - startIndex );
			}

	public: void setUsername()
			{
				extern twitCurl twitterObj;
				string response;
				twitterObj.getLastWebResponse(response);
				unsigned pos = response.find("screen_name"); 
				string aftername = response.substr(pos+12); 
				string username = ExtractString(aftername, "\"", "\"" );
				twitterObj.setTwitterUsername(username);
			}

	public: std::string getUserID(string nom)
			{
				extern twitCurl twitterObj; 
				string replyMsg;
				if(twitterObj.userGet(nom, false))
				{
					twitterObj.getLastWebResponse( replyMsg );
				}
				else
				{
					replyMsg = "erreur";
				}
				
				unsigned pos = replyMsg.find("id_str"); 
				string afterid = replyMsg.substr(pos+7);
				replyMsg = ExtractString(afterid, "\"", "\"" );
				return replyMsg;
			}
/* 
-------------------
      RESERVE 
-------------------

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
						String* msgAjout = String::Concat("Ajout de ",toAdd," à la file d'attente.");
						writeConsole(msgAjout);
					}
					catch (Exception* e)
					{
						MessageBox::Show("Erreur lors de l'ajout.");
					}
					
					// deleting the value in textbox
					this->tbAccount->Text = "";
				}
			}



*/

	};
}