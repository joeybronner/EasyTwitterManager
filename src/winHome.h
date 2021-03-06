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
#include "winMassFollow.h"
#include "../include/sqlite3.h"

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>
#using <mscorlib.dll>

using namespace std;
using namespace winSettings;
using namespace winPin;
using namespace winLog;
using namespace winMassFollow;

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

	public: windowHome(void)
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
			extern int followers;
			user = twitterObj.getTwitterUsername();
			writeConsole(String::Concat("Connect� en tant que : @", user.c_str()));
			this->lbWelcome->Text = String::Concat("Bonjour @",user.c_str(),"!");
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
		System::Windows::Forms::Button*			btRefresh;
		System::Windows::Forms::Button*			btUnfollow;
		System::Windows::Forms::Label*			lbWelcome;
		System::Windows::Forms::Label*			nbFollowers;
		System::Windows::Forms::Label*			nbFollowing;
		System::Windows::Forms::Label*			tendance;
		System::Windows::Forms::Label*			etatRatio;
		/* New tweet */
		System::Windows::Forms::Label*			lbNewTweet;
		System::Windows::Forms::TextBox*		tbNewTweet;
		System::Windows::Forms::Button*			btAddTweet;
		/* Load all ID followers */
		System::Windows::Forms::ListBox*		listToFollow;
		System::Windows::Forms::Label*			lbWaitingList;
		System::Windows::Forms::Button*			btFollowAll;
		System::Windows::Forms::Button*			btAddToFollow;
		System::Windows::Forms::Button*			btStopFollow;
		System::Threading::Thread*				t;
		System::Threading::Thread*				t2;
		System::String*							accountToFollow;
		/* Mass Message */
		System::Windows::Forms::Label*			lbMassMessage;
		System::Windows::Forms::RichTextBox*	rtbMassMessage;
		System::Windows::Forms::Button*			btSendMessage;


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

			// number of followers
				this->nbFollowers = new System::Windows::Forms::Label();
				this->nbFollowers->AutoSize = false;
				this->nbFollowers->Font = new System::Drawing::Font(L"Open Sans", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->nbFollowers->ForeColor = System::Drawing::Color::SteelBlue;
				this->nbFollowers->Location = System::Drawing::Point(100, 245);
				this->nbFollowers->Name = L"nbFollowers";
				this->nbFollowers->Text = L"- abonn�s";
				this->nbFollowers->Size = System::Drawing::Size(300, 50);
				this->nbFollowers->TextAlign = ContentAlignment::MiddleLeft;
				this->nbFollowers->BackColor = System::Drawing::Color::WhiteSmoke;

			// number of followings
				this->nbFollowing = new System::Windows::Forms::Label();
				this->nbFollowing->AutoSize = false;
				this->nbFollowing->Font = new System::Drawing::Font(L"Open Sans", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->nbFollowing->ForeColor = System::Drawing::Color::SteelBlue;
				this->nbFollowing->Location = System::Drawing::Point(100, 300);
				this->nbFollowing->Name = L"nbFollowing";
				this->nbFollowing->Text = L"- abonnements";
				this->nbFollowing->Size = System::Drawing::Size(300, 50);
				this->nbFollowing->TextAlign = ContentAlignment::MiddleLeft;
				this->nbFollowing->BackColor = System::Drawing::Color::WhiteSmoke;

			// etat ratio
				this->etatRatio = new System::Windows::Forms::Label();
				this->etatRatio->AutoSize = false;
				this->etatRatio->Font = new System::Drawing::Font(L"Open Sans", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->etatRatio->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->etatRatio->Location = System::Drawing::Point(190, 355);
				this->etatRatio->Name = L"etatRatio";
				this->etatRatio->Text = L"-";
				this->etatRatio->Size = System::Drawing::Size(210, 90);
				this->etatRatio->TextAlign = ContentAlignment::MiddleCenter;		

			// tendance
				this->tendance = new System::Windows::Forms::Label();
				this->tendance->AutoSize = false;
				this->tendance->Location = System::Drawing::Point(100, 355);
				this->tendance->Name = L"nbFollowing";
				this->tendance->Size = System::Drawing::Size(90, 90);
				this->tendance->BackgroundImage = System::Drawing::Image::FromFile("../img/ratiogris.png");

			// wainting list label message (label)
				this->lbWaitingList = new System::Windows::Forms::Label();
				this->lbWaitingList->AutoSize = true;
				this->lbWaitingList->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbWaitingList->ForeColor = System::Drawing::Color::White;
				this->lbWaitingList->Location = System::Drawing::Point(630, 220);
				this->lbWaitingList->Name = L"lbWaitingList";
				this->lbWaitingList->Size = System::Drawing::Size(94, 27);
				this->lbWaitingList->Text = L"Follow en masse";

			// label direct mass message (label)
				this->lbMassMessage = new System::Windows::Forms::Label();
				this->lbMassMessage->AutoSize = true;
				this->lbMassMessage->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbMassMessage->ForeColor = System::Drawing::Color::White;
				this->lbMassMessage->Location = System::Drawing::Point(430, 220);
				this->lbMassMessage->Name = L"lbMassMessage";
				this->lbMassMessage->Size = System::Drawing::Size(94, 27);
				this->lbMassMessage->Text = L"Message en masse";

			// rtbMassMessage
				this->rtbMassMessage = new System::Windows::Forms::RichTextBox();
				this->rtbMassMessage->Location = System::Drawing::Point(430, 245);
				this->rtbMassMessage->Name = L"rtbMassMessage";
				this->rtbMassMessage->Size = System::Drawing::Size(180, 195);
				this->rtbMassMessage->TabIndex = 6;
				this->rtbMassMessage->Text = L"Hello,\nVoil� un exemple de message.\nA bient�t :)";
				this->rtbMassMessage->MaxLength = 140;
				this->rtbMassMessage->BorderStyle = System::Windows::Forms::BorderStyle::None;

			// btFollowAll, start following all the list 
				this->btSendMessage = new System::Windows::Forms::Button();
				this->btSendMessage->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btSendMessage->Image = System::Drawing::Image::FromFile("../img/mini_logo/bull.png");
				this->btSendMessage->Location = System::Drawing::Point(510, 445);
				this->btSendMessage->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btSendMessage->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btSendMessage->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btSendMessage->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btSendMessage->FlatAppearance->BorderSize = 0;
				this->btSendMessage->Name = L"btSendMessage";
				this->btSendMessage->Size = System::Drawing::Size(20, 20);
				this->btSendMessage->TabIndex = 3;
				this->btSendMessage->UseVisualStyleBackColor = false;
				this->btSendMessage->Click += new System::EventHandler(this, &windowHome::btSendMessage_Click);

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


			// btRefresh, to refresh the screen
				this->btRefresh = new System::Windows::Forms::Button();
				this->btRefresh->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btRefresh->Image = System::Drawing::Image::FromFile("../img/ic_refresh.png");
				this->btRefresh->Location = System::Drawing::Point(5, 265);
				this->btRefresh->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btRefresh->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btRefresh->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btRefresh->FlatAppearance->BorderSize = 0;
				this->btRefresh->Name = L"btRefresh";
				this->btRefresh->Size = System::Drawing::Size(90, 90);
				this->btRefresh->TabIndex = 3;
				this->btRefresh->UseVisualStyleBackColor = false;
				this->btRefresh->Click += new System::EventHandler(this, &windowHome::btRefresh_Click);

			// btUnfollow, to refresh the screen
				this->btUnfollow = new System::Windows::Forms::Button();
				this->btUnfollow->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btUnfollow->Image = System::Drawing::Image::FromFile("../img/ic_unfollow.png");
				this->btUnfollow->Location = System::Drawing::Point(5, 165);
				this->btUnfollow->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btUnfollow->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btUnfollow->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btUnfollow->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btUnfollow->FlatAppearance->BorderSize = 0;
				this->btUnfollow->Name = L"btUnfollow";
				this->btUnfollow->Size = System::Drawing::Size(90, 90);
				this->btUnfollow->TabIndex = 3;
				this->btUnfollow->UseVisualStyleBackColor = false;
				this->btUnfollow->Click += new System::EventHandler(this, &windowHome::btUnfollow_Click);

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
				this->btInfos->Click += new System::EventHandler(this, &windowHome::btInfos_Click);

			// logo on the top of window
				this->imageLogo = new System::Windows::Forms::PictureBox();
				this->imageLogo->BackColor = System::Drawing::Color::PowderBlue;
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
				this->lbNewTweet->Text = L"Quoi de neuf ?";

			// console footer
				this->consoleFooter = new System::Windows::Forms::ListBox();
				this->consoleFooter->FormattingEnabled = true;
				this->consoleFooter->Location = System::Drawing::Point(100, 490);
				this->consoleFooter->Name = L"consoleFooter";
				this->consoleFooter->Size = System::Drawing::Size(680, 70);
				this->consoleFooter->Sorted = true;
				this->consoleFooter->TabIndex = 2;
				this->consoleFooter->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->consoleFooter->ScrollAlwaysVisible = true;
				

			// listBox who conain all the list to follow
				this->listToFollow = new System::Windows::Forms::ListBox();
				this->listToFollow->FormattingEnabled = true;
				this->listToFollow->Location = System::Drawing::Point(630, 245);
				this->listToFollow->Name = L"listToFollow";
				this->listToFollow->Size = System::Drawing::Size(150, 200);
				this->listToFollow->Sorted = false;
				this->listToFollow->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->listToFollow->ScrollAlwaysVisible = true;
				this->listToFollow->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;

			// btFollowAll, start following all the list 
				this->btFollowAll = new System::Windows::Forms::Button();
				this->btFollowAll->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btFollowAll->Image = System::Drawing::Image::FromFile("../img/mini_logo/play.png");
				this->btFollowAll->Location = System::Drawing::Point(725, 445);
				this->btFollowAll->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btFollowAll->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btFollowAll->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btFollowAll->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btFollowAll->FlatAppearance->BorderSize = 0;
				this->btFollowAll->Name = L"btFollowAll";
				this->btFollowAll->Size = System::Drawing::Size(20, 20);
				this->btFollowAll->TabIndex = 3;
				this->btFollowAll->UseVisualStyleBackColor = false;
				this->btFollowAll->Click += new System::EventHandler(this, &windowHome::btFollowAll_Click);

			// btStopFollow, to stop the thread used to mass following 
				this->btStopFollow = new System::Windows::Forms::Button();
				this->btStopFollow->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btStopFollow->Image = System::Drawing::Image::FromFile("../img/mini_logo/pause.png");
				this->btStopFollow->Location = System::Drawing::Point(695, 445);
				this->btStopFollow->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btStopFollow->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btStopFollow->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btStopFollow->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btStopFollow->FlatAppearance->BorderSize = 0;
				this->btStopFollow->Name = L"btFollowAll";
				this->btStopFollow->Size = System::Drawing::Size(20, 20);
				this->btStopFollow->TabIndex = 3;
				this->btStopFollow->UseVisualStyleBackColor = false;
				this->btStopFollow->Click += new System::EventHandler(this, &windowHome::btStopFollow_Click);

			// btAddToFollow, used to add some account on the waiting list
				this->btAddToFollow = new System::Windows::Forms::Button();
				this->btAddToFollow->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btAddToFollow->Image = System::Drawing::Image::FromFile("../img/mini_logo/add.png");
				this->btAddToFollow->Location = System::Drawing::Point(665, 445);
				this->btAddToFollow->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btAddToFollow->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btAddToFollow->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btAddToFollow->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btAddToFollow->FlatAppearance->BorderSize = 0;
				this->btAddToFollow->Name = L"btAddToFollow";
				this->btAddToFollow->Size = System::Drawing::Size(20, 20);
				this->btAddToFollow->TabIndex = 3;
				this->btAddToFollow->UseVisualStyleBackColor = false;
				this->btAddToFollow->Click += new System::EventHandler(this, &windowHome::btAddToFollow_Click);

			// adding the controls to the window
				this->SuspendLayout();
				this->Controls->Add(this->imageLogo);
				this->Controls->Add(this->btAddTweet);
				this->Controls->Add(this->consoleFooter);
				this->Controls->Add(this->tbNewTweet);
				this->Controls->Add(this->btConfig);
				this->Controls->Add(this->btInfos);
				this->Controls->Add(this->btFollowAll);
				this->Controls->Add(this->btUnfollow);
				this->Controls->Add(this->lbWelcome);
				this->Controls->Add(this->lbWaitingList);
				this->Controls->Add(this->nbFollowing);
				this->Controls->Add(this->listToFollow);
				this->Controls->Add(this->tendance);
				this->Controls->Add(this->btLogin);
				this->Controls->Add(this->btSendMessage);
				this->Controls->Add(this->etatRatio);
				this->Controls->Add(this->lbNewTweet);
				this->Controls->Add(this->btAddToFollow);
				this->Controls->Add(this->lbMassMessage);
				this->Controls->Add(this->btStopFollow);
				this->Controls->Add(this->rtbMassMessage);
				this->Controls->Add(this->nbFollowers);
				this->Controls->Add(this->btRefresh);
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion
	/* REFRESH MASS FOLLOWING LIST
	*
	* Method used to refresh the full list of potential following people
	*
	**/
	private: void refresh_ListFollow()
			 {
				extern bool loggedIn;
				if (loggedIn)
				{
					/* database connection */
					sqlite3* db;
					extern char* database;
					int co;	
					sqlite3_stmt* statement;
					
					co = sqlite3_open(database, &db);
					if(co)
					{
						writeConsole("Erreur de connexion � la base de donn�es locale");
					}
					else
					{
						if (sqlite3_prepare_v2(db, "SELECT * FROM TOFOLLOW", -1, &statement, 0) == SQLITE_OK)
						{
							listToFollow->Items->Clear();
							int cols = sqlite3_column_count(statement);
							int result = 0;
							int compt = 0;
							while(true)
							{
								result = sqlite3_step(statement);
								
								if(result == SQLITE_ROW)
								{
									int colonne = 2;
									string s = (char*)sqlite3_column_text(statement, colonne);
									String* ch = new String(s.c_str());
									listToFollow->Items->Add(ch);
									compt++;
								}
								else
								{
									break;   
								}
							}
							writeConsole(String::Concat(Convert::ToString(compt)," comptes en attente de follow"));
							sqlite3_finalize(statement);
							sqlite3_close(db);
						}
						else
						{
							// error gesture
						}
					}
				}
			 }
	
	/* FOLLOW ALL Pt 1
	*
	* Method used to start the following of people
	*
	**/
	private: System::Void btFollowAll_Click(System::Object* sender, System::EventArgs* e)
			{
				// here, the code to start the mass following thread
				if (this->listToFollow->SelectedItems->Count < 1)
				{
					writeConsole("Veuillez s�lectionner au moins un compte dans la liste.");
				}
				else
				{
					// get all the accounts
					int nbToFollow = this->listToFollow->SelectedItems->Count;

					if (MessageBox::Show(String::Concat("Cette action va lancer le traitement de ",nbToFollow.ToString()," comptes Twitter, �tes-vous s�r ?"),"Follow en masse", MessageBoxButtons::YesNo,MessageBoxIcon::Question)==::DialogResult::Yes)
					{
						for (int i = 0; i < nbToFollow ; i++)
						{
							Object* index = this->listToFollow->SelectedItems->Item[i];
							accountToFollow = index->ToString();
							string accountToFollowOld;

							MarshalString(accountToFollow,accountToFollowOld);

							twitterGet twiGet;
							string IDToFollow = twiGet.getUserID(accountToFollowOld);

							FollowBoucle(IDToFollow, accountToFollow);
						}
					}
				}

			}

	/* FOLLOW ALL Pt 2
	*
	* Method used to start the following of people
	*
	**/
	public:	void FollowBoucle(string IDToFollow, String* accountToFollow)
			{
				// wait 2 seconds between all following because of twitter security
				Sleep(2000);
				
				extern twitCurl twitterObj;
				twitterObj.friendshipCreate(IDToFollow, true);
				supprimerEntreeBDD(accountToFollow);
				writeConsole(String::Concat(accountToFollow, " a �t� suivi."));
			}			
		
	/* SEND MASS MESSAGE METHOD
	*
	* Method used to send a message to all your followers
	*
	**/
	private: System::Void btSendMessage_Click(System::Object* sender, System::EventArgs* e)
			 {
				if (MessageBox::Show("Etes-vous s�r de vouloir envoyer ce message � tous vos abonn�s ?","Message en masse", MessageBoxButtons::YesNo,MessageBoxIcon::Question)==::DialogResult::Yes)
				{
					extern twitCurl twitterObj;
					extern string user;
					twitterGet twiGet;

					/* spliting string */
					string flw;
					flw = twiGet.getAllFollowers(user);
					vector<string> tabToInsert; 
					string delimiter = ",";
					size_t pos = 0;
					string token;
					int vec =0;
							while ((pos = flw.find(delimiter)) != std::string::npos)
							{
								token = flw.substr(0, pos);
								tabToInsert.push_back(token);
								flw.erase(0, pos + delimiter.length());
							}
							int cpt = 0;

							for(vector<string>::size_type i=0;i < tabToInsert.size() ;i++)
							{		
								string username = twiGet.getUserUsername(tabToInsert[i].c_str());
								try
								{
									String* msgN = this->rtbMassMessage->Text;
									string msgO;
									MarshalString(msgN,msgO);
									twitterObj.directMessageSend(username, msgO, false);
									cpt++;
								}
								catch (Exception* e) {}
							} 

							writeConsole(String::Concat("Nombre de msg envoyes : ", cpt.ToString()));
				}
			 }

	/* UNFOLLOW
	*
	* Method used to unfollow all twitter account in your following and not followers
	*
	**/
 	private: System::Void btUnfollow_Click(System::Object* sender, System::EventArgs* e)
			{
				extern twitCurl twitterObj;
				extern string user;
				twitterGet twiGet;

				/* spliting string */
				string flw;
				flw = twiGet.getAllFollowing(user);
				vector<string> tabToInsert; 
				string delimiter = ",";
				size_t pos = 0;
				string token;
				int vec =0;
						while ((pos = flw.find(delimiter)) != std::string::npos)
						{
							token = flw.substr(0, pos);
							tabToInsert.push_back(token);
							flw.erase(0, pos + delimiter.length());
						}
						int cpt = 0;

						for(vector<string>::size_type i=0;i < tabToInsert.size() ;i++)
						{
							if (cpt > 50)
							{
								break;
							}
								
							//string username;
							string username = twiGet.getUserUsername(tabToInsert[i].c_str());
							string fback = twiGet.getFollowBackStatus(username);
							if (fback == "false")
							{
								twitterObj.friendshipDestroy(username, false);
								cpt++;
							}
						} 
			 }

	/* DELETE DATABASE ENTRY
	*
	* Method used to delete an entry in the database
	*
	**/
	public: void supprimerEntreeBDD(String* accountToFollow)
			{
					/* database connection */
					sqlite3* db;
					extern char* database;
					int co;	
					sqlite3_stmt* statement;
					char *zErrMsg = 0;
					
					co = sqlite3_open(database, &db);
					if(co)
					{
						writeConsole("Erreur de connexion � la base de donn�es locale");
					}
					else
					{		
						String* req;
						req = String::Concat("DELETE FROM TOFOLLOW WHERE ToFollowUN = '", accountToFollow,"'");
						string r;
						MarshalString(req,r);
						const char* requeteDelete = r.c_str();

						int rc;
						rc = sqlite3_exec(db, requeteDelete, 0, 0, &zErrMsg);
						
						sqlite3_close(db);
					}
			}


	/* STOP FOLLOWING EXECUTION
	*
	* Not used for the moment
	*
	**/
	private: System::Void btStopFollow_Click(System::Object* sender, System::EventArgs* e)
			{
				// here, the code to stop the mass following thread
			}
	
	/* OPEN MASS FOLLOW WINDOW
	*
	* Method used to open the "mass follow" window
	*
	**/
	private: System::Void btAddToFollow_Click(System::Object* sender, System::EventArgs* e)
			{
				windowMassFollow* wMassFollow = new windowMassFollow();
				wMassFollow->ShowDialog();
			}

	/* REFRESH / REPAINT METHOD
	*
	* Method used to refresh all the data on the main window
	*
	**/
	private: System::Void btRefresh_Click(System::Object* sender, System::EventArgs* e)
			{
				extern string 	user;
				extern int 		followers;
				extern int 		following;
				/* all the refresh methods are called here */

				/* 1st refresh : list to follow (database table: TOFOLLOW) */
				refresh_ListFollow();

				/* 2th refresh : number of followers */
				followers = getFollowersCount(user);
				this->nbFollowers->Text = String::Concat(followers.ToString(), " abonn�(s)");

				/* 3th refresh : number of followings */
				following = getFollowingCount(user);
				this->nbFollowing->Text = String::Concat(following.ToString(), " abonnement(s)");
	
				/* 4th refresh : graph image */
				if (followers > following)
				{
					this->tendance->BackgroundImage = System::Drawing::Image::FromFile("../img/ratiovert.png");
					this->etatRatio->ForeColor = System::Drawing::Color::DarkGreen;
					this->etatRatio->Text = L"Ratio en positif";
				}
				else
				{
					this->tendance->BackgroundImage = System::Drawing::Image::FromFile("../img/ratiorouge.png");
					this->etatRatio->ForeColor = System::Drawing::Color::DarkRed;
					this->etatRatio->Text = L"Ratio en n�gatif";
				}

				/* end message */
				writeConsole("Mise � jour effectu�e avec succ�s");
			}
		
	/* ADD NEW TWEET
	*
	* Method used to send a new tweet on the social network
	*
	**/		
	private: System::Void btAddTweet_Click(System::Object* sender, System::EventArgs* e)
			{
				extern twitCurl twitterObj;
				String* test = this->tbNewTweet->Text;
				string ajout;
				MarshalString(test,ajout);
				if (twitterObj.statusUpdate(ajout))
				{
					extern string replyMsg;
					twitterObj.getLastWebResponse( replyMsg );
					writeConsole(String::Concat("Tweet envoy�: <",ajout.c_str(),">"));
					tbNewTweet->Text = "";
				}
				else
				{
					writeConsole(String::Concat("Erreur: <",ajout.c_str(),"> n'a pas �t� tweet�"));
				}
			}

	/* OPEN SETTINGS WINDOW
	*
	* Method used to open the settings window
	*
	**/
	private: System::Void btConfig_Click(System::Object* sender, System::EventArgs* e)
			{
				windowSettings* wSettings = new windowSettings();
				wSettings->ShowDialog();
			}

	/* OPEN INFO WINDOW
	*
	* Method used to open the information window
	*
	**/
	private: System::Void btInfos_Click(System::Object* sender, System::EventArgs* e)
			 {
				 MessageBox::Show("D�velopp� par : Joey BRONNER\nEmail : joeybronner@gmail.com\nSources : https://github.com/joeybronner/EasyTwitterManager");
			 }
	
	/* GET DATETIME
	*
	* Method used to return the actual datetime
	*
	**/
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

	/* LOG IN / LOG OUT
	*
	* Method used to log in or out your twitter account
	*
	**/
	private: System::Void btLogin_Click(System::Object* sender, System::EventArgs* e)
			{
				removeAllFiles();
				windowLog* wLog = new windowLog();
				wLog->ShowDialog();
			}

	/* WRITE CONSOLE
	*
	* Method used to write some logs in the console
	*
	**/
	public: void writeConsole(String* msg)
			{
				String* currentDate = getDateTime();
				String* initMsg = String::Concat(currentDate,msg);
				this->consoleFooter->Items->Add(initMsg);
			}

	/* REMOVE FILES
	*
	* Method used to remove the token and secret from a user when he logout
	*
	**/
	private: void removeAllFiles()
			 {
				remove( "../txt/twitterClient_token_key.txt" );
				remove( "../txt/twitterClient_token_secret.txt" );
			 }
			 
	/* MARSHAL STRING
	*
	* Method used cast a String* into a string 
	*
	**/	 
	private: void MarshalString ( String* s, string& os )
			{
			   using namespace Runtime::InteropServices;
			   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			   os = chars;
			   Marshal::FreeHGlobal(IntPtr((void*)chars));
			}

	/* EXTRACT STRING
	*
	* Method used to extract some string from a large text
	*
	**/
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

	/* SET USERNAME
	*
	* Method used to set the logged in account into the twitter API
	*
	**/
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

	/* FOLLOWERS COUNT
	*
	* Method used to return the number of followers
	*
	**/
	public: int getFollowersCount(string nom)
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

				unsigned pos = replyMsg.find("followers_count"); 
				string afterid = replyMsg.substr(pos+16);
				replyMsg = ExtractString(afterid, ":", "," );
				int count;
				istringstream (replyMsg) >> count;
				return count;
			}

	/* FOLLOWING COUNT
	*
	* Method used to return the number of following
	*
	**/
	public: int getFollowingCount(string nom)
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
				
				unsigned pos = replyMsg.find("friends_count"); 
				string afterid = replyMsg.substr(pos+14);
				replyMsg = ExtractString(afterid, ":", "," );
				int count;
				istringstream (replyMsg) >> count;
				return count;
			}



/* Others methods (commented)
-------------------
      RESERVE 
-------------------

1. READING FILES
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
						String* msgAjout = String::Concat("Ajout de ",toAdd," � la file d'attente.");
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