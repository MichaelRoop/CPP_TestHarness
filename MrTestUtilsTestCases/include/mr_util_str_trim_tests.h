

#include "MrTestFixture.h"
#include "MrTestMacros.h"
#include "MrTestCompareFunctions.h"
#include "MrTestAsserts.h"
#include "mr_string.h"
#include "mr_iostream.h"
#include "mr_sstream.h"


class UtilStrTrimTests : public MrTest::Fixture {
public:

	UtilStrTrimTests(const mr_utils::mr_string& name) 
		: MrTest::Fixture(name) {

		ADD_TEST_FIXTURE(this);
		REGISTER_TEST(this, &UtilStrTrimTests::UTL_STR_RTRIM_1, "Right trim removes all white space characters");
		REGISTER_TEST(this, &UtilStrTrimTests::UTL_STR_RTRIM_2, "Right trim on empty string");
		REGISTER_TEST(this, &UtilStrTrimTests::UTL_STR_LTRIM_1, "Left trim removes all white space characters");
		REGISTER_TEST(this, &UtilStrTrimTests::UTL_STR_LTRIM_2, "Left trim on empty string");
		REGISTER_TEST(this, &UtilStrTrimTests::UTL_STR_TRIM_1, "Two sided trim removes all white space characters");
		REGISTER_TEST(this, &UtilStrTrimTests::UTL_STR_TRIM_2, "Two sided trim on empty string");
	}

	void UTL_STR_RTRIM_1() {  
		TEST_EQUAL(this, mr_utils::mr_string(L("This is a str")), mr_utils::TrimRight(L("This is a str  \t\n\r\0")));
	}

	void UTL_STR_RTRIM_2() {  
		TEST_EQUAL(this, mr_utils::mr_string(L("")), mr_utils::TrimLeft(L("")));
	}


	void UTL_STR_LTRIM_1() {  
		TEST_EQUAL(this, mr_utils::mr_string(L("This is a str")), mr_utils::TrimLeft(L("  \t\n\rThis is a str")));
	}


	void UTL_STR_LTRIM_2() {  
		TEST_EQUAL(this, mr_utils::mr_string(L("")), mr_utils::TrimLeft(L("")));
	}


	void UTL_STR_TRIM_1() {  
		TEST_EQUAL(this, mr_utils::mr_string(L("This is a str")), mr_utils::Trim(L("  \t\n\r  This is a str  \t\n\r  ")));
	}


	void UTL_STR_TRIM_2() {  
		TEST_EQUAL(this, mr_utils::mr_string(L("")), mr_utils::Trim(L("")));
	}

};
REGISTER_FIXTURE(UtilStrTrimTests)

