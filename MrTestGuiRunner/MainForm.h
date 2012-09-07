#pragma once

#include "CppTestEngine.h"
//
#include "mr_string.h"

namespace MrTestGuiRunner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(array<System::String ^> ^args)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			int i = args->Length;

		   String^ s = gcnew String("sample string");
		   IntPtr ip = Marshal::StringToHGlobalAnsi(s);
		   const wchar_t* str = static_cast<wchar_t*>(ip.ToPointer());
		   Console::WriteLine("(managed) passing string...");
		   //NativeTakesAString( str );
		   Marshal::FreeHGlobal( ip );



		   //std::vector<mr_utils::mr_string> myArgs;


			//MrTest::Engine& eng = MrTest::Engine::Instance();
			mr_utils::mr_string mrs;

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(912, 468);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &MainForm::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	};
}

