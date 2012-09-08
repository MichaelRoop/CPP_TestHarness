#pragma once

#include "CppTestEngine.h"
//#include "MrTestParamParser.h"
#include "mr_fileException.h"
#include "CppTestScriptException.h"
#include "MrTestListBuilderFactory.h"
#include "mr_string.h"



#include < vcclr.h >

namespace MrTestGuiRunner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;


/// @brief Event handler to push log data for individual test cases to console
//#pragma managed(push, off)
//	//static void MyLoggedEventHandler(const MrTest::ICase& testCase) {
//	//	MessageBox::Show("Test log callback");
//	//}
//
//	static void MyLoggedEventHandler(MrTest::DataLoggedEvent ev) {
//		MessageBox::Show("Test log callback");
//	}
//
//
//#pragma managed(pop)

//		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate void LogEventDelegate(const MrTest::ICase& testCase);


		void DataLogEventHandler2(const MrTest::ICase& testCase) {
			//MessageBox::Show("Test log callback");
			String^ msg = gcnew String(testCase.FixtureName.c_str());
			MessageBox::Show(msg);

			MessageBox::Show("Direct Blah");
		}


#ifdef skgjsalkdjfgksjf
		public ref class Listner {
		public:
			delegate void LogEventDelegate(const MrTest::ICase& testCase);

			Listner() {
				caseLog = gcnew LogEventDelegate(this, &Listner::DataLogEventHandler);
				pin_ptr<MrTest::Engine> pEng = &(MrTest::Engine::Instance());
				_caseLog = Marshal::GetFunctionPointerForDelegate(caseLog);
				pEng->RegisterLoggedEvent((MrTest::DataLoggedEvent)(void*) _caseLog);
				GC::KeepAlive(caseLog);
			}

			void DataLogEventHandler(const MrTest::ICase& testCase) {
				String^ msg = gcnew String(testCase.FixtureName.c_str());
				MessageBox::Show(msg, "Listner class");
			}

			LogEventDelegate^ caseLog;
			IntPtr _caseLog;
			
		};
#endif

	/// <summary>
	/// Summary for Form1
	/// </summary>
//[AttributeUsageAttribute(AttributeTargets::Delegate, AllowMultiple = false, Inherited = false)]
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		//[UnmanagedFunctionPointer(CallingConvention.Cdecl)]

		//[DllImport("CppTest.dll",CharSet=CharSet::Unicode, CallingConvention=CallingConvention::Cdecl)]
//		delegate void __cdecl LogEventDelegate(const MrTest::ICase& testCase);

		//[DllImport("TestDLL.dll", CallingConvention=CallingConvention.StdCall)]
		void DataLogEventHandler(const MrTest::ICase& testCase) {
			//MessageBox::Show("Test log callback");
			String^ msg = gcnew String(testCase.FixtureName.c_str());
			MessageBox::Show(msg, "Internal forced to Cdecl");

			MessageBox::Show("Blah");
		}


		//void DataLogEventHandler2(const MrTest::ICase& testCase) {
		//	//MessageBox::Show("Test log callback");
		//	//String^ msg = gcnew String(testCase.FixtureName.c_str());
		//	//MessageBox::Show(msg);

		//	MessageBox::Show("Direct Blah");
		//}



		MainForm(array<System::String ^> ^args)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			//int i = args->Length;

		 //  String^ s = gcnew String("sample string");
		 //  IntPtr ip = Marshal::StringToHGlobalAnsi(s);
		 //  const wchar_t* str = static_cast<wchar_t*>(ip.ToPointer());
		 //  Console::WriteLine("(managed) passing string...");
		 //  //NativeTakesAString( str );
		 //  Marshal::FreeHGlobal( ip );



		   //std::vector<mr_utils::mr_string> myArgs;


			//MrTest::Engine& eng = MrTest::Engine::Instance();
			mr_utils::mr_string mrs;


			try {
				//MrTest::ParamParser argParser;
				//argParser.Parse(argc, argv);

				pin_ptr<MrTest::Engine> pEng = &(MrTest::Engine::Instance());
				//pEng->LoadTests(argParser.GetArg(MrTest::ParamParser::TEST_CASE_DLL));
				pEng->LoadTests(L("..\\Debug\\CppTestUtilsTestCases.dll"));
			

				//MyLoggedEventHandler

				LogEventDelegate^ caseLog = gcnew LogEventDelegate(this, &MrTestGuiRunner::MainForm::DataLogEventHandler);
				IntPtr _caseLog = Marshal::GetFunctionPointerForDelegate(caseLog);
				pEng->RegisterLoggedEvent((MrTest::DataLoggedEvent)(void*) _caseLog);
				GC::KeepAlive(caseLog);

				//LogEventDelegate^ caseLog = gcnew LogEventDelegate(this, &DataLogEventHandler2);
				//IntPtr _caseLog = Marshal::GetFunctionPointerForDelegate(caseLog);
				//pEng->RegisterLoggedEvent((MrTest::DataLoggedEvent)(void*) _caseLog);
				//GC::KeepAlive(caseLog);

				//pEng->RegisterLoggedEvent(&DataLogEventHandler2);

			//	Listner l();


				//pEng->RegisterLoggedEvent(MyLoggedEventHandler);
				//pEng->RegisterSummaryEvent(MySummaryEventHandler);

				//if (argParser.HasArg(MrTest::ParamParser::TEST_CASE_LINE)) {
				//	pEng->ProcessTestList(
				//		MrTest::ListBuilderFactory::FromLine(
				//			argParser.GetArg(MrTest::ParamParser::TEST_CASE_LINE)));
				//}
				//else if (argParser.HasArg(MrTest::ParamParser::TEST_CASE_LIST)) {
				//	pEng->ProcessTestList(
				//		MrTest::ListBuilderFactory::FromFile(
				//			argParser.GetArg(MrTest::ParamParser::TEST_CASE_LIST)));
				//}

				pEng->ProcessTestList(
					MrTest::ListBuilderFactory::FromLine(L("TokenizerTests1.UTL_TOK_1_1")));

				MessageBox::Show("Before unload");

				pEng->UnloadTests();

				MessageBox::Show("After unload");
			} 
			catch( const MrTest::ScriptException e ) {
				// TODO - make sure not getting char* by define
				String^ msg = gcnew String(e.longMsg().c_str());
				MessageBox::Show(msg);
			}
			catch( const mr_utils::fileException e ) {
				String^ msg = gcnew String(e.longMsg().c_str());
				MessageBox::Show(msg);
			}
			catch( const mr_utils::mr_exception e ) {
				String^ msg = gcnew String(e.longMsg().c_str());
				MessageBox::Show(msg);
			}
			catch( const std::exception e ) {
			   String^ msg = Marshal::PtrToStringAnsi(static_cast<IntPtr>( const_cast<char*>( e.what() )  ));
				MessageBox::Show(msg);
			}
			catch( ... ) {
				MessageBox::Show("Unknown Exception");
			}
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

