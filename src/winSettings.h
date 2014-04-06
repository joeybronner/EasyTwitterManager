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
				//icon
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
				//this->lbReglages->TabIndex = 4;
				this->lbReglages->Text = L"Reglages";

			// IP proxy's address (label)
				this->lbIPproxy = new System::Windows::Forms::Label();
				this->lbIPproxy->AutoSize = true;
				this->lbIPproxy->Font = new System::Drawing::Font(L"Open Sans", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
				this->lbIPproxy->ForeColor = System::Drawing::Color::White;
				this->lbIPproxy->Location = System::Drawing::Point(10, 100);
				this->lbIPproxy->Name = L"lbIPproxy";
				this->lbIPproxy->Size = System::Drawing::Size(94, 27);
				//this->lbIPproxy->TabIndex = 4;
				this->lbIPproxy->Text = L"Adresse IP du proxy";

			// textbox used to set up the proxy's IP address
				this->tbIPproxy = new System::Windows::Forms::TextBox();
				this->tbIPproxy->Location = System::Drawing::Point(180, 100);
				this->tbIPproxy->Name = L"tbIPproxy";
				this->tbIPproxy->Size = System::Drawing::Size(150, 20);
				this->tbIPproxy->TabIndex = 3;

			// button to save changes
				this->btValidateChanges = new System::Windows::Forms::Button();
				this->btValidateChanges->Location = System::Drawing::Point(130, 330);
				this->btValidateChanges->Name = L"btValidateChanges";
				this->btValidateChanges->Size = System::Drawing::Size(120, 30);
				this->btValidateChanges->TabIndex = 0;
				this->btValidateChanges->Text = L"Appliquer";
				this->btValidateChanges->UseVisualStyleBackColor = true;
				this->btValidateChanges->Click += new System::EventHandler(this, &windowSettings::btValidateChanges_Click);


			// adding the controls to the window
				this->Controls->Add(this->lbReglages);
				this->Controls->Add(this->lbIPproxy);
				this->Controls->Add(this->tbIPproxy);
				this->Controls->Add(this->btValidateChanges);
				this->SuspendLayout();
				this->ResumeLayout(false);
				this->PerformLayout();
		}
#pragma endregion

	public: System::Void btValidateChanges_Click(System::Object* sender, System::EventArgs* e)
		{
			// here, the treatment for save all the user's changes 
			// ...
			this->Close();
		}
	};
}