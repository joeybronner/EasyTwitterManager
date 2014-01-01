#pragma once
#include <msclr/marshal_cppstd.h>

namespace EasyTwitterManager
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Fenêtre d'accueil de l'application
	/// </summary>
	public ref class window_Accueil : public System::Windows::Forms::Form
	{
	public:
		window_Accueil(void)
		{
			InitializeComponent();
			// Constructeur
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~window_Accueil()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ToolStrip^  toolStrip1;

	protected: 

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(window_Accueil::typeid));
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->SuspendLayout();
			// 
			// toolStrip1
			// 
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(770, 25);
			this->toolStrip1->TabIndex = 0;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// window_Accueil
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SkyBlue;
			this->ClientSize = System::Drawing::Size(770, 342);
			this->Controls->Add(this->toolStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"window_Accueil";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Accueil - EasyTwitterManager";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void buttonTest_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				MessageBox::Show("CLR MessageBox", "MessageBox Test",
				MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			 }
	};
}

