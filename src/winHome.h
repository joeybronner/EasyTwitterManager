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

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// main form settings
			this->components = new System::ComponentModel::Container();
			this->Size = System::Drawing::Size(800,600);
			this->Text = "winHome";


			// button settings
			this->button1 = new System::Windows::Forms::Button();
			//this->SuspendLayout();
			this->button1->Location = System::Drawing::Point(109, 113);
			this->button1->Name = L"WinHome";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"WinHome";
			this->button1->UseVisualStyleBackColor = true;

			// adding the controls to the window
			this->Controls->Add(this->button1);
		}
#pragma endregion
	};
}

