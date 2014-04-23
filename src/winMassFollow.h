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
		windowMassFollow(void)
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
		

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			// main form settings
				this->components = new System::ComponentModel::Container();
				this->Size = System::Drawing::Size(400,400);
				this->BackColor = System::Drawing::Color::LightSkyBlue;
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
				this->Text = "Follow en masse";
				//icon
				Bitmap* imgIcon = new Bitmap( "../img/EasyTwitterManager.ico" );
				IntPtr Hicon = imgIcon->GetHicon();
				System::Drawing::Icon* iconETM = System::Drawing::Icon::FromHandle( Hicon );
				this->Icon = iconETM;

			// adding the controls to the window
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