
#include "mr_case.h"
#include "mr_testMacros.h"
#include "mr_string.h"
#include "mr_iostream.h"
#include "mr_compareFunctions.h"
#include "mr_Assert.h"

// temp
#include <exception>


class TokenizerTests1 : public mr_test::testCase
{
public:

	TokenizerTests1() 
		: mr_test::testCase( _L_("testName"), _L_("argStr") ) {

		// This will add the test fixture to the test engine list when it is constructed
		// The Register Fixture macro at the end of the class creates an instance which
		// fires the contructor. However, this only works if the test case is compiled in
		// to a test app.  TODO - secondary step - register contructor with a method
		// that could be called from a DLL when the engine loads that DLL with the tests
		_ADD_TEST_FIXTURE_( this );

		// Optional Fixture setup and teardown. Executed once for series of test cases
		_FIXTURE_SETUP_(this, &TokenizerTests1::FixtureSetup );
		_FIXTURE_TEARDOWN_(this, &TokenizerTests1::FixtureTeardown );

		// Optional Test case setup and teardown. executed for each test case
		_TEST_SETUP_(this, &TokenizerTests1::TestSetup);
		_TEST_TEARDOWN_(this, &TokenizerTests1::TestTeardown);

		// Register test case methods
		_REGISTER_TEST_(this, &TokenizerTests1::UTL_TOK_1_1, _L_( "Normal tokenize string" ));
		_REGISTER_TEST_(this, &TokenizerTests1::UTL_TOK_1_2, _L_( "Tokenize with multiple mid delimiters"));
		_REGISTER_TEST_(this, &TokenizerTests1::UTL_TOK_1_3, _L_( "Tokenize test leading delimiters" ));
		_REGISTER_TEST_(this, &TokenizerTests1::UTL_TOK_1_4, _L_( "Tokenize test following delimiters" ));
		_REGISTER_TEST_(this, &TokenizerTests1::UTL_TOK_1_5, _L_("Tokenize test leading and following delimiters"));
		_REGISTER_TEST_(this, &TokenizerTests1::UTL_TOK_1_6, _L_("Tokenize test multiple leading mid and following delimiters"));
	}

	void TestSetup()	{ 
		printf("**** Registered Test Setup Executed ****\n");
		//_ARE_EQUAL(this, 1, 99);

		//_ARE_NOT_EQUAL(this, 1, 1);

	//	_DOES_THROW(this, Exception, { this->ThrowTest());

		//_IS_TRUE_(this, false, "Totaly false msg");
	}

	void TestTeardown()	{ 
		printf("**** Registered Test Teardown Executed ****\n");
		//_ARE_EQUAL(this, 1, 99);
	}
	
	void FixtureSetup()	
	{ 
		printf("++++ Registered Fixture Setup Executed ++++\n");
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
		printf("++++ Registered Fixture Teardown Executed ++++\n");
		//_ARE_EQUAL(this, 1, 99);
	}

	// Example test case
	void UTL_TOK_1_1() { 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|tokens") );
		this->DoIt( str );
	}

	void UTL_TOK_1_2() { 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|||||tokens") );
		this->DoIt( str );
	}
	
	void UTL_TOK_1_3() { 
		mr_utils::mr_string str( _L_("||||||||This|is|a|test|string|with|some|tokens") );
		this->DoIt( str );
	}

	void UTL_TOK_1_4() { 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|tokens||||||||") );
		this->DoIt( str );
	}
	
	void UTL_TOK_1_5() { 
		mr_utils::mr_string str( _L_("||||||||This|is|a|test|string|with|some|tokens||||||||") );
		this->DoIt( str );
	}

	void UTL_TOK_1_6()	{ 
		//_ARE_EQUAL(this, 1, 99);

		mr_utils::mr_string str( _L_("||||||||This|is|a|test||||||string|with||||||some|tokens||||||||") );
		this->DoIt( str );
	}
	
protected:
	void ThrowTest() {
		//throw Exception("blah");
	}


	std::vector<mr_utils::mr_string> m_tokens;

	bool CompareToken( std::vector<mr_utils::mr_string>::size_type index, const mr_utils::mr_string& token )
	{
//		ASSERT_TRUE(__FILE__, __LINE__, false, this->getMsgBuffer(), ( L( "index of:" ) << index << L( " exceeds token count of :" ) << m_tokens.size() ));
//		ASSERT_TRUE(__FILE__, __LINE__, false, this->getMsgBuffer(), ( L( "index of:" ) << L( "Woof" )  ));

		// compare index range.
		if (index >= m_tokens.size())
		{
			this->getMsgBuffer() << L( "index of:" ) << index << L( " exceeds token count of :" ) << m_tokens.size() << std::endl;
			return false;
		}
		//mr_assert::AreEqual(_FL_, m_tokens[index], token, this->getMsgBuffer());
		_ARE_EQUAL(this, m_tokens[index], token);
		//mr_cout << _L_("At Index:") << this->m_tokens[index] << _L_(" Compared:") << token << std::endl;
		return true;
	}

	bool DoIt( const mr_utils::mr_string& str )
	{
		mr_utils::mr_string token;
		mr_utils::mr_string::size_type pos = 0;
		std::vector<mr_utils::mr_string>::size_type index;

		for (index = 0; mr_utils::MrTokenize( pos, str, token, L('|') ); index++)
		{
			if (!this->CompareToken( index, token ))
			{
				return false;
			}
		}

		// The index is incremented before the tokenize so it will be one high.
		//return mr_test::VerbCompareEqual( FL, m_tokens.size(), index, *this, L("Total tokens number mismatch") );
		//mr_assert::AreEqual(_FL_, this->m_tokens.size(), index, this->getMsgBuffer());
		_ARE_EQUAL(this, this->m_tokens.size(), index);

		//mr_assert::AreEqual(_FL_, 1, 99, this->getMsgBuffer());
		//_ARE_EQUAL(this, 1, 99);

		return true;
	}

};
_REGISTER_FIXTURE_(TokenizerTests1)


// Test tokenize of string with only token delimiters.
class TokenizerTests2 : public mr_test::testCase {

public:
	TokenizerTests2()
		: mr_test::testCase( _L_( "Ziffle" ), _L_( "Pig" ) )	{
		_ADD_TEST_FIXTURE_( this );

		_FIXTURE_SETUP_(this, &TokenizerTests2::FixtureSetup );
		_FIXTURE_TEARDOWN_(this, &TokenizerTests2::FixtureTeardown );
		_TEST_SETUP_(this, &TokenizerTests2::TestSetup);
		_TEST_TEARDOWN_(this, &TokenizerTests2::TestTeardown);

		_REGISTER_TEST_(this, &TokenizerTests2::UTL_TOK_1_7, _L_( "Tokenize delimiters only" ));
	}																				

	void TestSetup()	{ 
		printf("**** 2 Registered Test Setup Executed ****\n");
	}

	void TestTeardown()	{ 
		printf("**** 2 Registered Test Teardown Executed ****\n");
	}
	
	void FixtureSetup()		{ 
		printf("++++ 2 Registered Fixture Setup Executed ++++\n");
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
		printf("++++ 2 Registered Fixture Teardown Executed ++++\n");
	}

	void UTL_TOK_1_7() { 
		mr_utils::mr_string str( _L_("||||||||") );
		mr_utils::mr_string token;

		mr_utils::mr_string::size_type pos = 0;
		int count;
		for (count = 0; mr_utils::MrTokenize( pos, str, token, _L_('|') ); count++)
		{
		}
		mr_test::VerbCompareEqual( _FL_, 0, count, this->getVerboseBuffer() );
	}

private:
	std::vector<mr_utils::mr_string> m_tokens;
};
_REGISTER_FIXTURE_(TokenizerTests2);



