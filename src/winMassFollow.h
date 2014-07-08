#pragma once

#include "stdafx.h"
#include "windows.h"
#include "tchar.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>     
#include <string>
#include <ctime>
#include <time.h>
#include "..\include\sqlite3.h"
#include "twitterGet.h"

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>
#using <mscorlib.dll>

using namespace std;

namespace winMassFollow {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public __gc class windowMassFollow : public System::Windows::Forms::Form
	{ 

	public:
		windowMassFollow()
		{
			InitializeComponent();
		}


	protected:
		~windowMassFollow()
		{
			//if (components)
			//{
			//	delete components;
			//}
		}

	public:
		System::ComponentModel::Container*		components;
		System::Windows::Forms::Button*			btValidateChanges;
		System::Windows::Forms::TextBox*		tbAccountName;
		System::Windows::Forms::Button*			btLoadListFollowers;
		

#pragma region Windows Form Designer generated code


		void InitializeComponent(void)
		{
			// main form settings
				this->components = new System::ComponentModel::Container();
				this->Size = System::Drawing::Size(350,180);
				this->BackColor = System::Drawing::Color::LightSkyBlue;
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
				this->Text = "Follow en masse";
				Bitmap* imgIcon = new Bitmap( "../img/EasyTwitterManager.ico" );
				IntPtr Hicon = imgIcon->GetHicon();
				System::Drawing::Icon* iconETM = System::Drawing::Icon::FromHandle( Hicon );
				this->Icon = iconETM;

			// text box used to set up the pin auth
				this->tbAccountName = new System::Windows::Forms::TextBox();
				this->tbAccountName->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->tbAccountName->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->tbAccountName->Location = System::Drawing::Point(10, 55);
				this->tbAccountName->Name = L"tbAccountName";
				this->tbAccountName->Size = System::Drawing::Size(100, 40);
				this->tbAccountName->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;

			// btLoadListFollowers, general app settings
				this->btLoadListFollowers = new System::Windows::Forms::Button();
				this->btLoadListFollowers->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btLoadListFollowers->Location = System::Drawing::Point(115, 55);
				this->btLoadListFollowers->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btLoadListFollowers->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btLoadListFollowers->FlatAppearance->MouseOverBackColor = System::Drawing::Color::SteelBlue;
				this->btLoadListFollowers->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
				this->btLoadListFollowers->FlatAppearance->BorderSize = 0;
				this->btLoadListFollowers->Name = L"btLoadListFollowers";
				this->btLoadListFollowers->Text = L"Ajouter!";
				this->btLoadListFollowers->Size = System::Drawing::Size(90, 25);
				this->btLoadListFollowers->TabIndex = 3;
				this->btLoadListFollowers->UseVisualStyleBackColor = false;
				this->btLoadListFollowers->Click += new System::EventHandler(this, &windowMassFollow::btLoadListFollowers_Click);


			// bt validateChanges
				this->btValidateChanges = new System::Windows::Forms::Button();
				this->btValidateChanges->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btValidateChanges->Image = System::Drawing::Image::FromFile("../img/ic_submit.png");
				this->btValidateChanges->Location = System::Drawing::Point(250, 25);
				this->btValidateChanges->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btValidateChanges->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btValidateChanges->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSkyBlue;
				this->btValidateChanges->FlatAppearance->BorderSize = 0;
				this->btValidateChanges->Name = L"btValidateChanges";
				this->btValidateChanges->Size = System::Drawing::Size(90, 90);
				this->btValidateChanges->TabIndex = 0;
				this->btValidateChanges->UseVisualStyleBackColor = false;
				this->btValidateChanges->Click += new System::EventHandler(this, &windowMassFollow::btValidateChanges_Click);

			// adding the controls to the window
				this->SuspendLayout();
				this->Controls->Add(this->btValidateChanges);
				this->Controls->Add(this->tbAccountName);
				this->Controls->Add(this->btLoadListFollowers);
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion

	/* VALIDATE
	*
	* Method used to close this window
	*
	**/
	public: System::Void btValidateChanges_Click(System::Object* sender, System::EventArgs* e)
		{			
			this->Close();
		}

	/* LOAD LIST FOLLOWERS
	*
	* Method used to load all the followers from another twitter account (textbox content)
	*
	**/
	public: System::Void btLoadListFollowers_Click(System::Object* sender, System::EventArgs* e)
			{

				// get the tb value
				String* tbValue = this->tbAccountName->Text;

				if (tbValue->Length < 1)
				{
					MessageBox::Show("Veuillez compléter le champ correspondant");
				}
				else
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
						MessageBox::Show("Erreur de connexion à la base de données locale");
					}
					else
					{
						/* get all the followers */
						twitterGet twiGet;
						string tbval;
						MarshalString(tbValue,tbval);
						string flw;
						flw = twiGet.getAllFollowers(tbval);
						
						/* spliting string */
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
						/* insert values in database (table: TOFOLLOW) */
						for(vector<string>::size_type i=0;i < tabToInsert.size();i++)
						{

							if (cpt > 50)
							{
								break;
							}

							// now
							time_t time = 0x3DE43B0C;
							string username;
							username = twiGet.getUserUsername(tabToInsert[i].c_str());

							String* req;
							String* req2;
							req = String::Concat("INSERT INTO TOFOLLOW (IDuser, ToFollowID, ToFollowUN) VALUES (1,'", tabToInsert[i].c_str(),"','");
							req2 = String::Concat(req, username.c_str(),"')");
							string r;
							MarshalString(req2,r);
							const char* requeteInsert = r.c_str();
 

							int rc;
							rc = sqlite3_exec(db, requeteInsert, 0, 0, &zErrMsg);
							if( rc != SQLITE_OK )
							{
								/* error */
								sqlite3_free(zErrMsg);
							}
							else
							{
							   /* ok */
								cpt = cpt + 1;
							}
						} 
						sqlite3_close(db);

					}
						this->tbAccountName->Text = "";
				}
				
			}

	/* MARSHAL STRING
	*
	* Method used to cast system String* into standart string
	*
	**/
	void MarshalString ( String* s, string& os )
			{
			   using namespace Runtime::InteropServices;
			   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			   os = chars;
			   Marshal::FreeHGlobal(IntPtr((void*)chars));
			}

	};
}