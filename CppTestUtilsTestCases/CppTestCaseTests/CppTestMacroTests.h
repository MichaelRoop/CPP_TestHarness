#include "CppTestFixture.h"
#include "CppTestMacros.h"
#include "mr_exception.h"


class MrTestMacroTests : public MrTest::Fixture {
public:

	MrTestMacroTests(const mr_utils::mr_string& name) 
		: MrTest::Fixture(name) {

		ADD_TEST_FIXTURE(this);

		// Register test case methods
		REGISTER_TEST(this, &MrTestMacroTests::UserFail, "Forced fail by TEST_FAIL macro");
		REGISTER_TEST(this, &MrTestMacroTests::TestThrowsNoThrow, "TEST_THROWS fails when expected exception not thrown");
		REGISTER_TEST(this, &MrTestMacroTests::TestThrowsWithThrow, "TEST_THROWS does not fail when expected exception thrown");
		REGISTER_TEST(this, &MrTestMacroTests::TestNotThrowsNoThrow, "TEST_NOT_THROWS does not fail when not exception thrown");
		REGISTER_TEST(this, &MrTestMacroTests::TestNotThrowsWithThrow, "TEST_NOT_THROWS fails on unexpected exception thrown");
		REGISTER_TEST(this, &MrTestMacroTests::TestEqual_NotEqual, "TEST_EQUAL signals error on unequal values");
		REGISTER_TEST(this, &MrTestMacroTests::TestEqual_Equal, "TEST_EQUAL no error on nequal values");
		REGISTER_TEST(this, &MrTestMacroTests::TestNotEqual_Equal, "TEST_NOT_EQUAL signals error on equal values");
		REGISTER_TEST(this, &MrTestMacroTests::TestNotEqual_NotEqual, "TEST_NOT_EQUAL no error on unequal values");
	}
	


	// TEST_EQUAL test with unequal values
	void TestEqual_NotEqual() { 
		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_EQUAL(this, 1,2);
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_TRUE(this, thrown, L("The TEST_EQUALS macro did not throw"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("but actual is")), L("'Values are blah' not contained in msg:") << msg);
	}


	// TEST_EQUAL test with equal values
	void TestEqual_Equal() { 

		//TEST_FALSE(this, true, L("Blaaaaaah"));

		int x = 0;
		int i = 10 / x;


		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_EQUAL(this, 1,1);
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_FALSE(this, thrown, L("The TEST_EQUALS macro did not throw"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("")), L("'Values are blah' not contained in msg:") << msg);
	}



	// TEST_NOT_EQUAL with equal values
	void TestNotEqual_Equal() { 
		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_NOT_EQUAL(this, 1,1);
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_TRUE(this, thrown, L("The TEST_EQUALS macro did not throw"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("Did not Expected")), L("'Values are blah' not contained in msg:") << msg);
	}


	// TEST_NOT_EQUAL with equal values
	void TestNotEqual_NotEqual() { 
		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_NOT_EQUAL(this, 1,5);
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_FALSE(this, thrown, L("The TEST_EQUALS macro did not throw"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("")), L("'Values are blah' not contained in msg:") << msg);
	}



	// TEST_FAIL test
	void UserFail() { 
		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_FAIL(this, L("Purposely failing this test"));
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_TRUE(this, thrown, L("The fail macro did not throw"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("Purposely failing this test")), L("'Purposely failing this test' not contained in msg:") << msg);
	}

	
	// The wrapped code does not throw an exception so the wrapper macro should not signal an error
	void TestThrowsNoThrow() {

		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_THROWS(this, {
				int i = 10;
				double j = 20;
				this->DummyThatDoesNotThrow();
			});
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_TRUE(this, thrown, L("The TEST_THROWS did not throw on a lack of expected throw"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("Test Expected Exception to be Thrown")), L("Not thrown message not returned"));
	}


	// The wrapped code throws an exception so the wrapper macro should signal an error
	void TestThrowsWithThrow() {
		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_THROWS(this, {
				int i = 10;
				double j = 20;
				this->DummyThatThrows();
			});
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_FALSE(this, thrown, L("The TEST_THROWS did not throw on a lack of expected throw"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("")), L("Should not have a thrown message"));
	}


	// The wrapped code throws an expected exception so the wrapper macro should not signal an error
	void TestNotThrowsNoThrow() {
		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_NOT_THROWS(this, {
				int i = 10;
				double j = 20;
				this->DummyThatDoesNotThrow();
			});
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}
		TEST_FALSE(this, thrown, L("The TEST_NOT_THROWS shoul not have signaled - no exception"));
		TEST_TRUE(this, mr_utils::Contains(msg, L("")), L("Should not have a thrown message"));
	}


	// The wrapped code does not throw an exception so the wrapper macro should signal an error
	void TestNotThrowsWithThrow() {
		bool thrown = false;
		mr_utils::mr_string msg;
		try {
			TEST_NOT_THROWS(this, {
				int i = 10;
				double j = 20;
				this->DummyThatThrows();
			});
		}
		catch (mr_utils::mr_exception& e) {
			thrown = true;
			msg = e.msg();
		}

		TEST_TRUE(this, thrown, L("The TEST_NOT_THROWS did not detect unexpected exception thrown"));
		//TEST_TRUE(this, mr_utils::Contains(msg, L("Test Expected Exception to be Thrown")), L("Not thrown message not returned"));

	}


private:
	void DummyThatThrows() {
		throw mr_utils::mr_exception(__FILE__,__LINE__,L("This is a thrown exception")); 
	}


	int DummyThatDoesNotThrow() {
		int i = 10;
		return i < 11;
	}


};
REGISTER_FIXTURE(MrTestMacroTests)


