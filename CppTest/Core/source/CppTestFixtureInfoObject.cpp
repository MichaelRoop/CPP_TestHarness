///--------------------------------------------------------------------------------------
/// @file	CppTestFixtureInfoObject.cpp
/// @brief	cross platform and char width holder for test fixture information.
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------

#include "CppTestFixtureInfoObject.h"


namespace CppTest {


TestFixtureInfoObject::TestFixtureInfoObject(const mr_utils::mr_string& name) 
	: m_name(name) {
}


TestFixtureInfoObject::~TestFixtureInfoObject() {
	// Nothing to do
}



const mr_utils::mr_string& TestFixtureInfoObject::GetName() const {
	return this->m_name;
}


const void TestFixtureInfoObject::SetName(mr_utils::mr_string& name) {
	this->m_name = name;
}


const std::vector<CppTest::TestInfoObject>& TestFixtureInfoObject::GetTestInfoVector() {
	return this->m_tests;
}


void TestFixtureInfoObject::AddTestInfo(const CppTest::TestInfoObject& info) {
	this->m_tests.push_back(info);
}


} // end namespace

