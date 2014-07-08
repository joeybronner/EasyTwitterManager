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

namespace winSettings {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public __gc class windowSettings : public System::Windows::Forms::Form
	{
	public:
		windowSettings(void)
		{
			InitializeComponent();
		}

	protected:
		~windowSettings()
		{
			//if (components)
			//{
			//	delete components;
			//}
		}

	public:
		System::ComponentModel::Container*		components;
		System::Windows::Forms::Label*			lbReglages;
		System::Windows::Forms::Label*			lbIPproxy;
		System::Windows::Forms::TextBox*		tbIPproxy;
		System::Windows::Forms::Label*			lbPortProxy;
		System::Windows::Forms::TextBox*		tbPortProxy;
		System::Windows::Forms::Label*			lbUserProxy;
		System::Windows::Forms::TextBox*		tbUserProxy;
		System::Windows::Forms::Label*			lbPswdProxy;
		System::Windows::Forms::TextBox*		tbPswdProxy;
		System::Windows::Forms::Button*			btValidateChanges;
		

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// main form settings
				this->components = new System::ComponentModel::Container();
				this->Size = System::Drawing::Size(400,400);
				this->BackColor = System::Drawing::Color::LightSkyBlue;
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
				this->Text = "Reglages";
				Bitmap* imgIcon = new Bitmap( "../img/EasyTwitterManager.ico" );
				IntPtr Hicon = imgIcon->GetHicon();
				System::Drawing::Icon* iconETM = System::Drawing::Icon::FromHandle( Hicon );
				this->Icon = iconETM;

			// settings title (label)
				this->lbReglages = new System::Windows::Forms::Label();
				this->lbReglages->AutoSize = true;
				this->lbReglages->Font = new System::Drawing::Font(L"Open Sans", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbReglages->ForeColor = System::Drawing::Color::White;
				this->lbReglages->Location = System::Drawing::Point(10, 10);
				this->lbReglages->Name = L"lbReglages";
				this->lbReglages->Size = System::Drawing::Size(94, 27);
				this->lbReglages->Text = L"Reglages";

			// IP proxy's address (label)
				this->lbIPproxy = new System::Windows::Forms::Label();
				this->lbIPproxy->AutoSize = true;
				this->lbIPproxy->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbIPproxy->ForeColor = System::Drawing::Color::White;
				this->lbIPproxy->Location = System::Drawing::Point(10, 100);
				this->lbIPproxy->Name = L"lbIPproxy";
				this->lbIPproxy->Size = System::Drawing::Size(94, 27);
				this->lbIPproxy->Text = L"Adresse IP du proxy:";

			// textbox used to set up the proxy's IP address
				this->tbIPproxy = new System::Windows::Forms::TextBox();
				this->tbIPproxy->Location = System::Drawing::Point(180, 100);
				this->tbIPproxy->Name = L"tbIPproxy";
				this->tbIPproxy->Size = System::Drawing::Size(150, 20);
				this->tbIPproxy->TabIndex = 3;

			// proxy's port (label)
				this->lbPortProxy = new System::Windows::Forms::Label();
				this->lbPortProxy->AutoSize = true;
				this->lbPortProxy->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbPortProxy->ForeColor = System::Drawing::Color::White;
				this->lbPortProxy->Location = System::Drawing::Point(10, 150);
				this->lbPortProxy->Name = L"lbPortProxy";
				this->lbPortProxy->Size = System::Drawing::Size(94, 27);
				this->lbPortProxy->Text = L"Port du proxy:";

			// textbox used to set up the proxy's port
				this->tbPortProxy = new System::Windows::Forms::TextBox();
				this->tbPortProxy->Location = System::Drawing::Point(180, 150);
				this->tbPortProxy->Name = L"tbPortProxy";
				this->tbPortProxy->Size = System::Drawing::Size(70, 20);
				this->tbPortProxy->TabIndex = 3;

			// proxy's user (label)
				this->lbUserProxy = new System::Windows::Forms::Label();
				this->lbUserProxy->AutoSize = true;
				this->lbUserProxy->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbUserProxy->ForeColor = System::Drawing::Color::White;
				this->lbUserProxy->Location = System::Drawing::Point(10, 200);
				this->lbUserProxy->Name = L"lbUserProxy";
				this->lbUserProxy->Size = System::Drawing::Size(94, 27);
				this->lbUserProxy->Text = L"Nom d'utilisateur :";

			// textbox used to set up the proxy's user
				this->tbUserProxy = new System::Windows::Forms::TextBox();
				this->tbUserProxy->Location = System::Drawing::Point(180, 200);
				this->tbUserProxy->Name = L"tbUserProxy";
				this->tbUserProxy->Size = System::Drawing::Size(150, 20);
				this->tbUserProxy->TabIndex = 3;

			// proxy's password (label)
				this->lbPswdProxy = new System::Windows::Forms::Label();
				this->lbPswdProxy->AutoSize = true;
				this->lbPswdProxy->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbPswdProxy->ForeColor = System::Drawing::Color::White;
				this->lbPswdProxy->Location = System::Drawing::Point(10, 250);
				this->lbPswdProxy->Name = L"lbPswdProxy";
				this->lbPswdProxy->Size = System::Drawing::Size(94, 27);
				this->lbPswdProxy->Text = L"Mot de passe :";

			// textbox used to set up the proxy's password
				this->tbPswdProxy = new System::Windows::Forms::TextBox();
				this->tbPswdProxy->Location = System::Drawing::Point(180, 250);
				this->tbPswdProxy->Name = L"tbPswdProxy";
				this->tbPswdProxy->Size = System::Drawing::Size(150, 20);
				this->tbPswdProxy->PasswordChar = '*';
				this->tbPswdProxy->TabIndex = 3;

			// button to save changes
				this->btValidateChanges = new System::Windows::Forms::Button();
				this->btValidateChanges->BackColor = System::Drawing::Color::LightSkyBlue;	
				this->btValidateChanges->Image = System::Drawing::Image::FromFile("../img/ic_submit.png");
				this->btValidateChanges->Location = System::Drawing::Point(150, 280);
				this->btValidateChanges->Cursor = System::Windows::Forms::Cursors::Hand;
				this->btValidateChanges->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btValidateChanges->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSkyBlue;
				this->btValidateChanges->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSkyBlue;
				this->btValidateChanges->FlatAppearance->BorderSize = 0;
				this->btValidateChanges->Name = L"btValidateChanges";
				this->btValidateChanges->Size = System::Drawing::Size(90, 90);
				this->btValidateChanges->TabIndex = 0;
				this->btValidateChanges->UseVisualStyleBackColor = false;



			// adding the controls to the window
				this->Controls->Add(this->lbReglages);
				this->Controls->Add(this->lbIPproxy);
				this->Controls->Add(this->tbIPproxy);
				this->Controls->Add(this->lbPortProxy);
				this->Controls->Add(this->tbPortProxy);
				this->Controls->Add(this->lbUserProxy);
				this->Controls->Add(this->tbUserProxy);
				this->Controls->Add(this->lbPswdProxy);
				this->Controls->Add(this->tbPswdProxy);
				this->Controls->Add(this->btValidateChanges);
				this->SuspendLayout();
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion

	/* CLOSE
	*
	* Method used to close this window
	*
	**/
	public: System::Void btValidateChanges_Click(System::Object* sender, System::EventArgs* e)
		{			
			this->Close();
		}
	};
}