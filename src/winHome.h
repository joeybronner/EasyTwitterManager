#pragma once

#include "stdafx.h"
#include "windows.h"
#include "tchar.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>


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

	private:
		System::ComponentModel::Container* components;
		System::Windows::Forms::Button*  button1;
		System::Windows::Forms::PictureBox*  imageLogo;


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
			this->button1 = new System::Windows::Forms::Button();
			this->button1->Location = System::Drawing::Point(100, 100);
			this->button1->Name = L"buttonStart";
			this->button1->Size = System::Drawing::Size(100, 100);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;

			// logo on the top of window
			this->imageLogo = new System::Windows::Forms::PictureBox();
			//this->imageLogo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->imageLogo->Location = System::Drawing::Point(10, 10);
			this->imageLogo->Name = L"imageLogo";
			this->imageLogo->Size = System::Drawing::Size(770, 120);
			this->imageLogo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->imageLogo->Image = System::Drawing::Image::FromFile("../img/logo_home_window.png");
			this->imageLogo->TabIndex = 0;
			this->imageLogo->TabStop = false;
			
			// adding the controls to the window
			this->SuspendLayout();
			this->Controls->Add(this->button1);
			this->Controls->Add(this->imageLogo);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	};
}