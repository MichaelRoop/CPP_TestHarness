#include "MrTestCaseHolder.h"
#include "MrTestCase.h"
#include <assert.h>


namespace MrTest {

TestCaseHolder::TestCaseHolder(
	IFixture::Ifixture_method_ptr testPtr, const mr_utils::mr_string& fixtureName,  const mr_utils::mr_string& name, const mr_utils::mr_string& description) 
	: 	m_test(testPtr),
		m_testData(new MrTest::Case(fixtureName, name, description)) {
}

	
TestCaseHolder::~TestCaseHolder() {
	if (this->m_testData != 0) {
		delete this->m_testData;
		this->m_testData = 0;
	}
}


IFixture::Ifixture_method_ptr TestCaseHolder::Pointer() const {
	return this->m_test;
}


ICase* TestCaseHolder::Data() const {
	return this->m_testData;
}


void TestCaseHolder::Reset() {
	assert(this->m_testData);
	this->m_testData->Reset();
}


} // end namespace

