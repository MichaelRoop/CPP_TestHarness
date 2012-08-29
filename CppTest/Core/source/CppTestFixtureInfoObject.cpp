///--------------------------------------------------------------------------------------
/// @file	CppTestFixtureInfoObject.cpp
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------

#include "CppTestFixtureInfoObject.h"


namespace CppTest {

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

