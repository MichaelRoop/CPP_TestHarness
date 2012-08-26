///--------------------------------------------------------------------------------------
/// @file	CppTestInfoObject.cpp
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestInfoObject.h"


namespace CppTest {

TestInfoObject::TestInfoObject() 
:	m_isActive( false ),
	m_isNull( true ) {
}


bool TestInfoObject::IsActive() const {
	return this->m_isActive;
}


void TestInfoObject::SetActive(bool active) {
	this->m_isActive = active;
}


bool TestInfoObject::IsNull() const {
	return this->m_isNull;
}


void TestInfoObject::SetNull(bool isNull) {
	this->m_isNull = isNull;
}


const mr_utils::mr_string& TestInfoObject::GetName() const {
	return this->m_name;
}


void TestInfoObject::SetName(const mr_utils::mr_string& name) {
	this->m_name = name;
}


const std::vector<CppTest::ICaseArgument>& TestInfoObject::GetArguments() const {
	return this->m_arguments;
}


void TestInfoObject::AddArgument(const mr_utils::mr_string& name, const mr_utils::mr_string& value) {
	this->m_arguments.push_back(CppTest::ICaseArgument(name, value));
}


} // end namespace CppTest
