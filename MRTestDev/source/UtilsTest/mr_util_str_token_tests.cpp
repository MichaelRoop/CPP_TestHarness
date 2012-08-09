
#include "mr_case.h"
#include "mr_testMacros.h"
#include "mr_string.h"
#include "mr_iostream.h"
#include "mr_compareFunctions.h"


class TokTestBase : public mr_test::testCase
{
public:

	TokTestBase( const mr_utils::mr_string& testName, const mr_utils::mr_string& argStr ) 
		: mr_test::testCase( testName, argStr ) {
		_FIXTURE_SETUP_(this, &TokTestBase::FixtureSetup );
		_FIXTURE_TEARDOWN_(this, &TokTestBase::FixtureTeardown );
	}


	void FixtureSetup()	
	{ 
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
		printf("**** Registered Teardown Executed ****\n");
	}

protected:

	std::vector<mr_utils::mr_string> m_tokens;

	bool CompareToken( std::vector<mr_utils::mr_string>::size_type index, const mr_utils::mr_string& token )
	{
		// compare index range.
		if (index >= m_tokens.size())
		{
			this->getMsgBuffer() << L( "index of:" ) << index << L( " exceeds token count of :" ) << m_tokens.size() << std::endl;
			return false;
		}
		return mr_test::VerbCompareEqual( FL, m_tokens[index], token, *this, L("Token value mismatch") );
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
			//mr_cout << L( "str:" ) << str << L( ", token:" ) << token.c_str() << std::endl;
		}

		// The index is incremented before the tokenize so it will be one high.
		return mr_test::VerbCompareEqual( FL, m_tokens.size(), index, *this, L("Total tokens number mismatch") );
	}

};


// Test tokenize of string with multiple token delimiters.
class mrTokTestNormal : public TokTestBase {
public:
	mrTokTestNormal() : TokTestBase( _L_( "UTL_TOK_1_1" ), _L_( "Normal tokenize string" ) )	{
		_ADD_TEST_FIXTURE_( this );
	}

	bool test()	{ 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|tokens") );
		return this->DoIt( str );
	}
};
_REGISTER_FIXTURE_(mrTokTestNormal);


// Test tokenize of string with multiple token delimiters and mid extras.
_DECL_TEST_( mrTokTestMidMultipleDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|||||tokens") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_2, instUTL_TOK_1_2, mrTokTestMidMultipleDel, _L_( "Tokenize with multiple mid delimiters" ) )


// Test tokenize of string with leading token delimiters.
_DECL_TEST_( mrTokTestLeadDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( _L_("||||||||This|is|a|test|string|with|some|tokens") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_3, instUTL_TOK_1_3, mrTokTestLeadDel, _L_( "Tokenize test leading delimiters" ) )


// Test tokenize of string with following token delimiters.
_DECL_TEST_( mrTokTestFollowDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|tokens||||||||") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_4, instUTL_TOK_1_4, mrTokTestFollowDel, _L_( "Tokenize test following delimiters" ) )


// Test tokenize of string with leading and following token delimiters.
_DECL_TEST_( mrTokTestLeadFollowDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( _L_("||||||||This|is|a|test|string|with|some|tokens||||||||") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_5, instUTL_TOK_1_5, mrTokTestLeadFollowDel, _L_( "Tokenize test leading and following delimiters" ) )


// Test tokenize of string with multiple mid and leading and following token delimiters.
class mrTokTestLeadMidFollowDel : public TokTestBase {
public:
	mrTokTestLeadMidFollowDel()
		: TokTestBase( L( "UTL_TOK_1_6" ), _L_( "Tokenize test multiple leading mid and following delimiters" ) )	{
		_ADD_TEST_FIXTURE_( this );
	}

	bool test()	{ 
		mr_utils::mr_string str( _L_("||||||||This|is|a|test||||||string|with||||||some|tokens||||||||") );
		return this->DoIt( str );
	}
};
_REGISTER_FIXTURE_(mrTokTestLeadMidFollowDel);


// Test tokenize of string with only token delimiters.
class mrTokTestDelOnly2 : public mr_test::testCase {

public:
	mrTokTestDelOnly2()
		: mr_test::testCase( _L_( "UTL_TOK_1_7" ), _L_( "Tokenize delimiters only" ) )	{
		_ADD_TEST_FIXTURE_( this );
	}																				

	bool test() { 
		mr_utils::mr_string str( _L_("||||||||") );
		mr_utils::mr_string token;

		mr_utils::mr_string::size_type pos = 0;
		int count;
		for (count = 0; mr_utils::MrTokenize( pos, str, token, _L_('|') ); count++)
		{
		}
		return mr_test::VerbCompareEqual( _FL_, 0, count, *this );
	}
};
_REGISTER_FIXTURE_(mrTokTestDelOnly2);



