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

namespace winLog {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public __gc class windowLog : public System::Windows::Forms::Form
	{
	public:
		windowLog(void)
		{
			InitializeComponent();
		}

	protected:
		~windowLog()
		{
			//if (components)
			//{
			//	delete components;
			//}
		}

	public:
		System::ComponentModel::Container*		components;
		System::Windows::Forms::Label*			lbWelcome;
		System::Windows::Forms::Button*			btLogin;
		System::Windows::Forms::Button*			btExit;
		

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// main form settings
				this->components = new System::ComponentModel::Container();
				this->Size = System::Drawing::Size(250,250);
				this->BackColor = System::Drawing::Color::LightSkyBlue;
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				this->ControlBox = false;
				this->Text = "Easy Twitter Manager | Welcome";
				//icon
				Bitmap* imgIcon = new Bitmap( "../img/EasyTwitterManager.ico" );
				IntPtr Hicon = imgIcon->GetHicon();
				System::Drawing::Icon* iconETM = System::Drawing::Icon::FromHandle( Hicon );
				this->Icon = iconETM;

			// btLogin, to log in twitter using twitcurl
				this->btLogin = new System::Windows::Forms::Button();
				this->btLogin->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btLogin->Image = System::Drawing::Image::FromFile("../img/ic_login.png");
				this->btLogin->Location = System::Drawing::Point(60, 50);
				this->btLogin->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btLogin->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btLogin->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btLogin->FlatAppearance->BorderSize = 0;
				this->btLogin->Name = L"btLogin";
				this->btLogin->Size = System::Drawing::Size(120, 120);
				this->btLogin->TabIndex = 3;
				this->btLogin->UseVisualStyleBackColor = false;
				this->btLogin->Click += new System::EventHandler(this, &windowLog::btLogin_Click);

			// btExit --> closing app
				this->btExit = new System::Windows::Forms::Button();
				this->btExit->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btExit->Image = System::Drawing::Image::FromFile("../img/ic_exit.png");
				this->btExit->Location = System::Drawing::Point(60, 180);
				this->btExit->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btExit->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btExit->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btExit->FlatAppearance->BorderSize = 0;
				this->btExit->Name = L"btExit";
				this->btExit->Size = System::Drawing::Size(120, 30);
				this->btExit->TabIndex = 3;
				this->btExit->UseVisualStyleBackColor = false;
				this->btExit->Click += new System::EventHandler(this, &windowLog::btExit_Click);

			// settings title (label)
				this->lbWelcome = new System::Windows::Forms::Label();
				this->lbWelcome->AutoSize = true;
				this->lbWelcome->Font = new System::Drawing::Font(L"Open Sans", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbWelcome->ForeColor = System::Drawing::Color::White;
				this->lbWelcome->Location = System::Drawing::Point(10, 10);
				this->lbWelcome->Name = L"lbWelcome";
				this->lbWelcome->Size = System::Drawing::Size(94, 27);
				//this->lbWelcome->TabIndex = 4;
				this->lbWelcome->Text = L"Welcome,";

			// adding the controls to the window
				this->Controls->Add(this->lbWelcome);
				this->Controls->Add(this->btLogin);
				this->Controls->Add(this->btExit);
				this->SuspendLayout();
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion
	public: System::Void btExit_Click(System::Object* sender, System::EventArgs* e)
			{
				Application::Exit();
			}
	public: System::Void btLogin_Click(System::Object* sender, System::EventArgs* e)
			{
				try {
					/* ìnit message on console */
					//writeConsole("Début de l'initialisation de l'API Twitter.");

					/* twitCurl initializing */
					extern twitCurl twitterObj;
					extern string tmpStr, tmpStr2;
					extern string replyMsg;
					extern char tmpBuf[1024];

					/* OAuth flow begins */
					twitterObj.getOAuth().setConsumerKey(	 std::string( "vlC5S1NCMHHg8mD1ghPRkA" ) );
					twitterObj.getOAuth().setConsumerSecret( std::string( "3w4cIrHyI3IYUZW5O2ppcFXmsACDaENzFdLIKmEU84" ) );

					/* check if we alredy have OAuth access token from a previous run */

					std::ifstream oAuthTokenKeyIn("../txt/twitterClient_token_key.txt");
					std::ifstream oAuthTokenSecretIn("../txt/twitterClient_token_secret.txt");

					string myOAuthAccessTokenKey("");
					string myOAuthAccessTokenSecret("");

					if (oAuthTokenKeyIn && oAuthTokenSecretIn)
					{
						//writeConsole("Récupération des clés d'authentification d'une ancienne connexion.");

						// get the key from file
						String* key = System::IO::File::ReadAllText("../txt/twitterClient_token_key.txt");
						MarshalString(key,myOAuthAccessTokenKey);

						// get the secret from file
						String* secret = System::IO::File::ReadAllText("../txt/twitterClient_token_secret.txt");
						MarshalString(secret,myOAuthAccessTokenSecret);

						if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
						{
							/* If we already have these keys, then no need to go through auth again */
							//writeConsole("Clés récupérées avec succès.");
							//writeConsole(String::Concat("Key   : ", myOAuthAccessTokenKey.c_str()));
							//writeConsole(String::Concat("Secret: ", myOAuthAccessTokenSecret.c_str()));
							
							/* authentification */
							twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
							twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
						}
						
					}
					else {
						//writeConsole("Aucune ancienne connexion détectée.");
						
						/* get request token key and secret */
						std::string authUrl;
						twitterObj.oAuthRequestToken( authUrl );

						if (MessageBox::Show(String::Concat("Vous devez être redirigé vers ",authUrl.c_str()," pour autoriser l'application."),"Authentification EasyTwitterManager", MessageBoxButtons::YesNo,MessageBoxIcon::Question)==::DialogResult::Yes)
						{
							//writeConsole(String::Concat("Ouverture de la page web : ",authUrl.c_str()));
							System::Diagnostics::Process::Start(authUrl.c_str());

							// to get the pin value
							windowPin* wPin = new windowPin();
							wPin->ShowDialog();

							//writeConsole(String::Concat("PIN entré : ",tmpStr.c_str()));

							// auth with the key entered by the user
							twitterObj.getOAuth().setOAuthPin( tmpStr );
							twitterObj.oAuthAccessToken();

							/* authentification */
							twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
							twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

							/* Saving these keys in a text file */
							std::ofstream oAuthTokenKeyOut;
							std::ofstream oAuthTokenSecretOut;

							oAuthTokenKeyOut.open( "../txt/twitterClient_token_key.txt" );
							oAuthTokenSecretOut.open( "../txt/twitterClient_token_secret.txt" );

							// deleting data who are already in this file
							oAuthTokenKeyOut.clear();
							oAuthTokenSecretOut.clear();

							// adding the new keys
							oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
							oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

							// closing files
							oAuthTokenKeyOut.close();
							oAuthTokenSecretOut.close();
						}
						else {
							//writeConsole("L'initialisation requiert une redirection vers internet.");
							return;
						}

					}

					// check if connection if ok

					if( twitterObj.accountVerifyCredGet() )
					{
						//twitterObj.getLastWebResponse( replyMsg );
						
						//replyMsg = twitterObj.timelineUserGet(true,false,1,"", false);
						//writeConsole("Vous êtes connecté!");
						//activeDesactiveElements(true, "logout");
					}
					else
					{
						twitterObj.getLastCurlError( replyMsg );
						//writeConsole(replyMsg.c_str());
					}

					/*
						CONNECTION ESTABLISHED !!! 
						ìnit message on console
					*/
					//writeConsole("Fin de l'initialisation de l'API Twitter.");
					extern bool loggedIn;
					loggedIn = true;
					this->Close();

				}
				catch (int e) {
					/* error message */
					//writeConsole("Erreur lors de l'initialisation de l'API Twitter.");
					//writeConsole(e.ToString());
				}
				
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