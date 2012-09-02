#if !defined(WIN32)
#	pragma unmanaged
#endif


#include "CppTestFixture.h"
#include "CppTestMacros.h"
#include "mr_string.h"
#include "mr_iostream.h"
#include "mr_sstream.h"
#include "CppTestCompareFunctions.h"
#include "CppTestAsserts.h"

// temp
#include <exception>


class TokenizerTests1 : public CppTest::Fixture {
public:

	TokenizerTests1(const mr_utils::mr_string& name) 
		: CppTest::Fixture(name) {

		// This will add the test fixture to the test engine list when it is constructed
		// The Register Fixture macro at the end of the class creates an instance which
		// fires the contructor. However, this only works if the test case is compiled in
		// to a test app.  TODO - secondary step - register contructor with a method
		// that could be called from a DLL when the engine loads that DLL with the tests
		ADD_TEST_FIXTURE(this);

		// Optional Fixture setup and teardown. Executed once for series of test cases
		FIXTURE_SETUP(this, &TokenizerTests1::FixtureSetup);
		FIXTURE_TEARDOWN(this, &TokenizerTests1::FixtureTeardown); 

		// Optional Test case setup and teardown. executed for each test case
		TEST_SETUP(this, &TokenizerTests1::TestSetup);
		TEST_TEARDOWN(this, &TokenizerTests1::TestTeardown);

		// Register test case methods
		REGISTER_TEST(this, &TokenizerTests1::UTL_TOK_1_1, "Normal tokenize string");
		REGISTER_TEST(this, &TokenizerTests1::UTL_TOK_1_2, "Tokenize with multiple mid delimiters");
		REGISTER_TEST(this, &TokenizerTests1::UTL_TOK_1_3, "Tokenize test leading delimiters");
		REGISTER_TEST(this, &TokenizerTests1::UTL_TOK_1_4, "Tokenize test following delimiters");
		REGISTER_TEST(this, &TokenizerTests1::UTL_TOK_1_5, "Tokenize test leading and following delimiters");
		REGISTER_TEST(this, &TokenizerTests1::UTL_TOK_1_6, "Tokenize test multiple leading mid and following delimiters");
	}
	
	void FixtureSetup()	{ 
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Fixture Setup Executed ****") << std::endl;
		//_ARE_EQUAL(this, 1, 99);
		m_tokens.push_back( _L_("This" ) );
		m_tokens.push_back( _L_("is" ) );
		m_tokens.push_back( _L_("a" ) );
		m_tokens.push_back( _L_("test" ) );
		m_tokens.push_back( _L_("string" ) );
		m_tokens.push_back( _L_("with" ) );
		m_tokens.push_back( _L_("some" ) );
		m_tokens.push_back( _L_("tokens" ) );
	}

	void FixtureTeardown() {
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Fixture Teardown Executed ****") << std::endl;
		//_ARE_EQUAL(this, 1, 99);
	}

	void TestSetup()	{ 
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Test Setup Executed ****") << std::endl;
		//TEST_EQUAL(this, 1, 99);
		//TEST_NOT_EQUAL(this, 1, 1);
		//TEST_THROWS(this, Exception, { this->ThrowTest());
		//TEST_TRUE_(this, false, "Totaly false msg");
		//TEST_FALSE_(this, true, "Totaly false msg");
	}

	void TestTeardown()	{ 
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Test Teardown Executed ****") << std::endl;
		//TEST_EQUAL(this, 1, 99);
	}
	

	// Example test case
	void UTL_TOK_1_1() { 
		//int x = 0;
		//int i = 10 / x;
		this->TokenizeString(_L_("This|is|a|test|string|with|some|tokens"));
	}

	void UTL_TOK_1_2() { 
		this->TokenizeString(_L_("This|is|a|test|string|with|some|||||tokens"));
	}
	
	void UTL_TOK_1_3() { 
		this->TokenizeString(_L_("||||||||This|is|a|test|string|with|some|tokens"));
	}

	void UTL_TOK_1_4() { 
		this->TokenizeString(_L_("This|is|a|test|string|with|some|tokens||||||||"));
	}
	
	void UTL_TOK_1_5() { 
		this->TokenizeString(_L_("||||||||This|is|a|test|string|with|some|tokens||||||||"));
	}

	void UTL_TOK_1_6()	{ 
		this->TokenizeString(_L_("||||||||This|is|a|test||||||string|with||||||some|tokens||||||||"));
	}
	
protected:
	void ThrowTest() {
		//throw Exception("blah");
	}
	
	std::vector<mr_utils::mr_string> m_tokens;

	void CompareToken( std::vector<mr_utils::mr_string>::size_type index, const mr_utils::mr_string& token ) {
		// compare index range.
		if (index >= m_tokens.size()) {
			TEST_TRUE(this, false, L( "index of:" ) << index << L( " exceeds token count of :" ) << m_tokens.size());
		}
		TEST_EQUAL(this, m_tokens[index], token);
	}

	void TokenizeString(const mr_utils::mr_string& str) {
		mr_utils::mr_string token;
		mr_utils::mr_string::size_type pos = 0;
		std::vector<mr_utils::mr_string>::size_type index;

		for (index = 0; mr_utils::MrTokenize( pos, str, token, L('|') ); index++) {
			this->CompareToken( index, token );
		}

		// The index is incremented before the tokenize so it will be one high.
		TEST_EQUAL(this, this->m_tokens.size(), index);
	}

};
REGISTER_FIXTURE(TokenizerTests1)


// Test tokenize of string with only token delimiters.
class TokenizerTests2 : public CppTest::Fixture {

public:
	TokenizerTests2(const mr_utils::mr_string& name)
		: CppTest::Fixture(name)	{
		ADD_TEST_FIXTURE( this );

		FIXTURE_SETUP(this, &TokenizerTests2::FixtureSetup );
		FIXTURE_TEARDOWN(this, &TokenizerTests2::FixtureTeardown );
		TEST_SETUP(this, &TokenizerTests2::TestSetup);
		TEST_TEARDOWN(this, &TokenizerTests2::TestTeardown);

		REGISTER_TEST(this, &TokenizerTests2::UTL_TOK_1_7, "Tokenize delimiters only");
	}																				

	void TestSetup()	{ 
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Test Setup Executed ****") << std::endl;
	}

	void TestTeardown()	{ 
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Test Teardown Executed ****") << std::endl;
	}
	
	void FixtureSetup()		{ 
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Fixture Setup Executed ****") << std::endl;
		this->m_tokens.push_back( _L_("This" ) );
		this->m_tokens.push_back( _L_("is" ) );
		this->m_tokens.push_back( _L_("a" ) );
		this->m_tokens.push_back( _L_("test" ) );
		this->m_tokens.push_back( _L_("string" ) );
		this->m_tokens.push_back( _L_("with" ) );
		this->m_tokens.push_back( _L_("some" ) );
		this->m_tokens.push_back( _L_("tokens" ) );
	}

	void FixtureTeardown() {
		mr_cout << _L_("**** ") << this->Name() << _L_(" Registered Fixture Teardown Executed ****") << std::endl;
	}

	void UTL_TOK_1_7() { 
		mr_utils::mr_string token;
		mr_utils::mr_string::size_type pos = 0;
		int count;
		for (count = 0; mr_utils::MrTokenize( pos,  _L_("||||||||"), token, _L_('|') ); count++) {
		}
		TEST_EQUAL(this, 0, count);
	}

private:
	std::vector<mr_utils::mr_string> m_tokens;
};
REGISTER_FIXTURE(TokenizerTests2);


