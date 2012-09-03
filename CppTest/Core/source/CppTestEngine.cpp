///--------------------------------------------------------------------------------------
/// @file	CppTestEngine.cpp
/// @brief	Class that drives the testing architecture.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestEngine.h"

#include "MrTestEngineImplementation.h"
#include "ICppTestFixtureTestCaseNames.h"


namespace MrTest {

// Declaration of static instance
Engine* Engine::m_instance = 0; 


Engine& Engine::Instance() {
	if (m_instance == 0) {
		m_instance = new Engine();
	}
	return *m_instance;
}


Engine::Engine() {
	this->m_implementation = new MrTest::EngineImplementation();
}


Engine::~Engine() {
	// singleton so do not bother to clear anything
}


void Engine::RegisterCase(MrTest::IFixture* fixture) {
	this->m_implementation->RegisterCase(fixture);
}


void Engine::LoadTests(const mr_utils::mr_string& dllName) {
	this->m_implementation->LoadTests(dllName);
}


void Engine::UnloadTests() {
	this->m_implementation->UnloadTests();
}


void Engine::ProcessTestList(std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> >& list) {
	this->m_implementation->ProcessTestList(list);
}


mr_utils::mr_string Engine::GetRunId() {
	return this->m_implementation->GetRunId();
}


std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > Engine::GetTestNames() {
	return this->m_implementation->GetTestNames();
}


void Engine::RegisterLoggedEvent(MrTest::DataLoggedEvent loggedCallbackEvent) {
	this->m_implementation->RegisterLoggedEvent(loggedCallbackEvent);
}


void Engine::RegisterSummaryEvent(MrTest::TestRunSummaryData summrayCallbackEvent) {
	this->m_implementation->RegisterSummaryEvent(summrayCallbackEvent);
}


void Engine::LoadLoggersByFileDefinition(const std::string& fileName, const mr_utils::mr_string& fileType) {
	this->m_implementation->LoadLoggersByFileDefinition(fileName, fileType);
}

} // end namespace

