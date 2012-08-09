
#include "mr_case.h"
#include "mr_testMacros.h"
#include "mr_string.h"
#include "mr_iostream.h"
#include "mr_compareFunctions.h"


class TokTestBase : public mr_test::testCase
{
public:

	TokTestBase( const mr_utils::mr_string& testName, const mr_utils::mr_string& argStr ) 
		: mr_test::testCase( testName, argStr )
	{
	}

	bool setup()	
	{ 
		m_tokens.push_back( L("This" ) );
		m_tokens.push_back( L("is" ) );
		m_tokens.push_back( L("a" ) );
		m_tokens.push_back( L("test" ) );
		m_tokens.push_back( L("string" ) );
		m_tokens.push_back( L("with" ) );
		m_tokens.push_back( L("some" ) );
		m_tokens.push_back( L("tokens" ) );
		return true; 
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
	mrTokTestNormal() : TokTestBase( L( "UTL_TOK_1_1" ), L( "Normal tokenize string" ) )	{
		_REGISTER_TEST_CASE_( this );
	}

	bool test()	{ 
		mr_utils::mr_string str( L("This|is|a|test|string|with|some|tokens") );
		return this->DoIt( str );
	}
};
_REGISTER_FIXTURE_(mrTokTestNormal);


// Test tokenize of string with multiple token delimiters and mid extras.
_DECL_TEST_( mrTokTestMidMultipleDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( L("This|is|a|test|string|with|some|||||tokens") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_2, instUTL_TOK_1_2, mrTokTestMidMultipleDel, L( "Tokenize with multiple mid delimiters" ) )


// Test tokenize of string with leading token delimiters.
_DECL_TEST_( mrTokTestLeadDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( L("||||||||This|is|a|test|string|with|some|tokens") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_3, instUTL_TOK_1_3, mrTokTestLeadDel, L( "Tokenize test leading delimiters" ) )


// Test tokenize of string with following token delimiters.
_DECL_TEST_( mrTokTestFollowDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( L("This|is|a|test|string|with|some|tokens||||||||") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_4, instUTL_TOK_1_4, mrTokTestFollowDel, L( "Tokenize test following delimiters" ) )


// Test tokenize of string with leading and following token delimiters.
_DECL_TEST_( mrTokTestLeadFollowDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( L("||||||||This|is|a|test|string|with|some|tokens||||||||") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_5, instUTL_TOK_1_5, mrTokTestLeadFollowDel, L( "Tokenize test leading and following delimiters" ) )


// Test tokenize of string with multiple mid and leading and following token delimiters.
_DECL_TEST_( mrTokTestLeadMidFollowDel, TokTestBase )
	bool test()		
	{ 
		mr_utils::mr_string str( L("||||||||This|is|a|test||||||string|with||||||some|tokens||||||||") );
		return this->DoIt( str );
	}
_REG_TEST_( UTL_TOK_1_6, instUTL_TOK_1_6, mrTokTestLeadMidFollowDel, L( "Tokenize test multiple leading mid and following delimiters" ) )



// Test tokenize of string with only token delimiters.
class mrTokTestDelOnly2 : public mr_test::testCase {

public:
	mrTokTestDelOnly2()
		: mr_test::testCase( L( "UTL_TOK_1_7" ), L( "Tokenize delimiters only" ) )	{

			mr_cout << L("***** Constructor being invoked") << std::endl;

		_REGISTER_TEST_CASE_( this );
	}																				

	bool test() { 
		mr_utils::mr_string str( L("||||||||") );
		mr_utils::mr_string token;

		mr_utils::mr_string::size_type pos = 0;
		int count;
		for (count = 0; mr_utils::MrTokenize( pos, str, token, L('|') ); count++)
		{
		}
		return mr_test::VerbCompareEqual( FL, 0, count, *this );
	}
};
_REGISTER_FIXTURE_(mrTokTestDelOnly2);



