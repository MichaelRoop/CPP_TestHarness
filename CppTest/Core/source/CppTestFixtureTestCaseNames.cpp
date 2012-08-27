

#include "CppTestFixtureTestCaseNames.h"

namespace CppTest {


FixutureTestCaseNames::FixutureTestCaseNames(const mr_utils::mr_string& name) 
	: m_name(name) {
}


FixutureTestCaseNames::FixutureTestCaseNames(const FixutureTestCaseNames& obj) {
	this->m_name = obj.m_name;
	this->m_testCaseNames = obj.m_testCaseNames;
}


const mr_utils::mr_string& FixutureTestCaseNames::FixtureName() const {
	return this->m_name;
}


const std::vector<mr_utils::mr_string>& FixutureTestCaseNames::TestCaseNames() const {
	return this->m_testCaseNames;
}


void FixutureTestCaseNames::AddTestCaseName(const mr_utils::mr_string& name) {
	this->m_testCaseNames.push_back(name);
}


} // end namespace