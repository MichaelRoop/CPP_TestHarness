#pragma once

#include "ManagedTestCaseData.h"
#include "ManagedSummaryData.h"

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

	
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate void LogEventDelegate(const MrTest::ICase& testCase);


	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate void TestRunSummaryDelegate(const MrTest::IRunSummary& summary);


	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		/// <summary>
		/// The managed handler for the unmanaged callback
		/// </summary>
		void DataLogEventHandler(const MrTest::ICase& testCase) {
			//String^ msg = gcnew String(testCase.FixtureName.c_str());
			//MessageBox::Show(msg, "Internal forced to Cdecl");
			//msg = gcnew String(testCase.MsgBuffer.str().c_str());
			//MessageBox::Show(msg, "Internal forced to Cdecl");

			MrTestGuiRunner::ManagedTestCaseData data;
			data.FixtureName = gcnew String(testCase.FixtureName.c_str());
			data.Name = gcnew String(testCase.Name.c_str());
			data.Status = static_cast<ManagedTestCaseData::TestCaseStatus>(testCase.Status);
			data.Description = gcnew String(testCase.Description.c_str());
			//data.m_args;	
			data.MsgBuffer  = gcnew String(testCase.MsgBuffer.str().c_str());	
			//data.EmbeddedMsgBuffer= gcnew String(testCase.EmbeddedMsgBuffer.str().c_str());	
			data.VerboseBuffer= gcnew String(testCase.EmbeddedMsgBuffer.str().c_str());			
			data.SetupTime = testCase.SetupTime;			
			data.ExecTime = testCase.ExecTime;
			data.CleanupTime = testCase.CleanupTime;


			//MrTestGuiRunner::ManagedTestCaseData::TestCaseStatus status = 
			//	static_cast<MrTestGuiRunner::ManagedTestCaseData::TestCaseStatus>(testCase.Status);

			MessageBox::Show(data.FixtureName, data.Status.ToString());
			MessageBox::Show(data.Name, data.Status.ToString());
			MessageBox::Show(data.Description, data.Status.ToString());

//			MessageBox::Show(status.ToString(), "Internal forced to Cdecl");
		}


		void TestRunSummaryHandler(const MrTest::IRunSummary& summary) {
			
			ManagedSummaryData data;
			data.Success = summary.Total(MrTest::ICase::ST_SUCCESS);
			data.FailFixtureSetup = summary.Total(MrTest::ICase::ST_FAIL_FIXTURE_SETUP);
			data.FailSetup = summary.Total(MrTest::ICase::ST_FAIL_SETUP);;
			data.FailTest = summary.Total(MrTest::ICase::ST_FAIL_TEST);;
			data.FailTeardown = summary.Total(MrTest::ICase::ST_FAIL_CLEANUP);;
			data.NotFound = summary.Total(MrTest::ICase::ST_NOT_EXISTS);;
			data.Disabled = summary.Total(MrTest::ICase::ST_DISABLED);;
			data.Total = summary.Total();

			MessageBox::Show(data.Total.ToString(), "Summary Total Tests");
		}





		MainForm(array<System::String ^> ^args)
		{
			InitializeComponent();

			//MrTest::Engine& eng = MrTest::Engine::Instance();

			try {
				//MrTest::ParamParser argParser;
				//argParser.Parse(argc, argv);

				pin_ptr<MrTest::Engine> pEng = &(MrTest::Engine::Instance());
				//pEng->LoadTests(argParser.GetArg(MrTest::ParamParser::TEST_CASE_DLL));
				pEng->LoadTests(L("..\\Debug\\CppTestUtilsTestCases.dll"));
			

				LogEventDelegate^ caseLog = gcnew LogEventDelegate(this, &MrTestGuiRunner::MainForm::DataLogEventHandler);
				IntPtr _caseLog = Marshal::GetFunctionPointerForDelegate(caseLog);
				pEng->RegisterLoggedEvent((MrTest::DataLoggedEvent)(void*) _caseLog);
				GC::KeepAlive(caseLog);


				//TestRunSummaryHandler

				TestRunSummaryDelegate^ summaryLog = gcnew TestRunSummaryDelegate(this, &MrTestGuiRunner::MainForm::TestRunSummaryHandler);
				IntPtr _summaryLog = Marshal::GetFunctionPointerForDelegate(summaryLog);
				pEng->RegisterSummaryEvent((MrTest::TestRunSummaryData)(void*) _summaryLog);
				GC::KeepAlive(summaryLog);




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

				pEng->UnloadTests();
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
				String^ msg = gcnew String(e.what());
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

