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
			//extern int loggedIn;
			//writeConsole(String::Concat("test",loggedIn.ToString()));
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
		System::Windows::Forms::Button*			btConfig;
		System::Windows::Forms::Button*			btInfos;
		System::Windows::Forms::Button*			btLogin;


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

			// button add to follow
				this->btAddAccount = new System::Windows::Forms::Button();
				this->btAddAccount->Location = System::Drawing::Point(220, 200);
				this->btAddAccount->Name = L"btAddAccount";
				this->btAddAccount->Size = System::Drawing::Size(50, 20);
				this->btAddAccount->TabIndex = 0;
				this->btAddAccount->Text = L"Ajouter";
				this->btAddAccount->UseVisualStyleBackColor = true;
				this->btAddAccount->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btAddAccount->Click += new System::EventHandler(this, &windowHome::btAddAccount_Click);
				this->btAddAccount->ForeColor = System::Drawing::Color::White;
				this->btAddAccount->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btAddAccount->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btAddAccount->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btAddAccount->FlatAppearance->BorderSize = 0;


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

			// btLogin, to log in twitter using twitcurl
				this->btLogin = new System::Windows::Forms::Button();
				this->btLogin->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btLogin->Image = System::Drawing::Image::FromFile("../img/ic_login.png");
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
				//this->imageLogo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->imageLogo->Location = System::Drawing::Point(100, 10);
				this->imageLogo->Name = L"imageLogo";
				this->imageLogo->Size = System::Drawing::Size(680, 120);
				this->imageLogo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
				this->imageLogo->Image = System::Drawing::Image::FromFile("../img/logo_home_window.png");
				this->imageLogo->TabIndex = 0;
				this->imageLogo->TabStop = false;

			// textbox account for add someone to the list of people to follow
				this->tbAccount = new System::Windows::Forms::TextBox();
				this->tbAccount->Location = System::Drawing::Point(110, 200);
				this->tbAccount->Name = L"tbAccount";
				this->tbAccount->Size = System::Drawing::Size(100, 20);
				this->tbAccount->TabIndex = 3;

			// console footer
				this->consoleFooter = new System::Windows::Forms::ListBox();
				this->consoleFooter->FormattingEnabled = true;
				this->consoleFooter->Location = System::Drawing::Point(100, 460);
				this->consoleFooter->Name = L"consoleFooter";
				this->consoleFooter->Size = System::Drawing::Size(680, 100);
				this->consoleFooter->Sorted = true;
				this->consoleFooter->TabIndex = 2;
				writeConsole("Initialisation de la fenêtre d'accueil.");

			// adding the controls to the window
				this->SuspendLayout();
				this->Controls->Add(this->btAddAccount);
				this->Controls->Add(this->imageLogo);
				this->Controls->Add(this->consoleFooter);
				this->Controls->Add(this->tbAccount);
				this->Controls->Add(this->btConfig);
				this->Controls->Add(this->btInfos);
				this->Controls->Add(this->btLogin);
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
				try {
					/* ìnit message on console */
					writeConsole("Début de l'initialisation de l'API Twitter.");

					/* twitCurl initializing */
					twitCurl twitterObj;
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
						writeConsole("Récupération des clés d'authentification d'une ancienne connexion.");

						// get the key from file
						String* key = System::IO::File::ReadAllText("../txt/twitterClient_token_key.txt");
						MarshalString(key,myOAuthAccessTokenKey);

						// get the secret from file
						String* secret = System::IO::File::ReadAllText("../txt/twitterClient_token_secret.txt");
						MarshalString(secret,myOAuthAccessTokenSecret);

						if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
						{
							/* If we already have these keys, then no need to go through auth again */
							writeConsole(String::Concat("Key   : ", myOAuthAccessTokenKey.c_str()));
							writeConsole(String::Concat("Secret: ", myOAuthAccessTokenSecret.c_str()));
								
							twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
							twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
							writeConsole("Clés récupérées avec succès.");
						}
						
					}
					else {
						writeConsole("Aucune ancienne connexion détectée.");
						
						/* Step 2: Get request token key and secret */
						std::string authUrl;
						twitterObj.oAuthRequestToken( authUrl );

						if (MessageBox::Show(String::Concat("Vous devez être redirigé vers ",authUrl.c_str()," pour autoriser l'application."),"Authentification EasyTwitterManager", MessageBoxButtons::YesNo,MessageBoxIcon::Question)==::DialogResult::Yes)
						{
							writeConsole(String::Concat("Ouverture de la page web : ",authUrl.c_str()));
							System::Diagnostics::Process::Start(authUrl.c_str());

							// to get the pin value
							windowPin* wPin = new windowPin();
							wPin->ShowDialog();

							writeConsole(String::Concat("PIN entré : ",tmpStr.c_str()));

							// auth with the key entered by the user
							twitterObj.getOAuth().setOAuthPin( tmpStr );
							twitterObj.oAuthAccessToken();
							twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
							twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

							///* Step 6: Save these keys in a file or wherever */
							std::ofstream oAuthTokenKeyOut;
							std::ofstream oAuthTokenSecretOut;

							oAuthTokenKeyOut.open( "../txt/twitterClient_token_key.txt" );
							oAuthTokenSecretOut.open( "../txt/twitterClient_token_secret.txt" );

							oAuthTokenKeyOut.clear();
							oAuthTokenSecretOut.clear();

							// Mise a jour des cles d'acces (fichiers txt)
							oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
							oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

							// Fermeture des fichiers
							oAuthTokenKeyOut.close();
							oAuthTokenSecretOut.close();
						}
						else {
							writeConsole("L'initialisation recquiert une redirection vers internet.");
						}



						
					}


					
					/* ìnit message on console */
					writeConsole("Fin de l'initialisation de l'API Twitter.");
				}
				catch (int e) {
					/* error message */
					writeConsole("Erreur lors de l'initialisation de l'API Twitter.");
					writeConsole(e.ToString());
				}

				
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
	};
}