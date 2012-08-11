
#include "mr_case.h"
#include "mr_testMacros.h"
#include "mr_string.h"
#include "mr_iostream.h"
#include "mr_compareFunctions.h"
#include "mr_Assert.h"


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
		//printf("**** Registered Teardown Executed ****\n");
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
		mr_assert::AreEqual(_FL_, m_tokens[index], token, this->getMsgBuffer());
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
		mr_assert::AreEqual(_FL_, this->m_tokens.size(), index, this->getMsgBuffer());

		return true;
	}

};

class blah : public TokTestBase {
public:
	blah() : TokTestBase( _L_( "blah" ), _L_( "Blah class" ) )	{
		_ADD_TEST_FIXTURE_( this );
		_REGISTER_TEST_(this, &blah::UTL_TOK_1_1, _L_( "Normal tokenize string" ));
		_REGISTER_TEST_(this, &blah::UTL_TOK_1_2, _L_( "Tokenize with multiple mid delimiters"));
		_REGISTER_TEST_(this, &blah::UTL_TOK_1_3, _L_( "Tokenize test leading delimiters" ));
		_REGISTER_TEST_(this, &blah::UTL_TOK_1_4, _L_( "Tokenize test following delimiters" ));
		_REGISTER_TEST_(this, &blah::UTL_TOK_1_5, _L_("Tokenize test leading and following delimiters"));
	}

	// just to satisfy compiler with old code
	bool test()	{ return false;}

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



};
_REGISTER_FIXTURE_(blah);

#ifdef erotiuertiou

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
class mrTokTestMidMultipleDel : public TokTestBase {
public:
	mrTokTestMidMultipleDel() : TokTestBase(_L_("UTL_TOK_1_2"), _L_( "Tokenize with multiple mid delimiters")) {
		_ADD_TEST_FIXTURE_( this );
	}

	bool test()	{ 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|||||tokens") );
		return this->DoIt( str );
	}
};
_REGISTER_FIXTURE_(mrTokTestMidMultipleDel);


// Test tokenize of string with leading token delimiters.
class mrTokTestLeadDel : public TokTestBase {
public:
	mrTokTestLeadDel() : TokTestBase(_L_("UTL_TOK_1_3"), _L_( "Tokenize test leading delimiters" )) {
		_ADD_TEST_FIXTURE_( this );
	}

	bool test()		
	{ 
		mr_utils::mr_string str( _L_("||||||||This|is|a|test|string|with|some|tokens") );
		return this->DoIt( str );
	}
};
_REGISTER_FIXTURE_(mrTokTestLeadDel);


// Test tokenize of string with following token delimiters.
class mrTokTestFollowDel : public TokTestBase {
public:
	mrTokTestFollowDel() : TokTestBase(_L_("UTL_TOK_1_4"), _L_( "Tokenize test following delimiters" )) {
		_ADD_TEST_FIXTURE_( this );
	}

	bool test()		
	{ 
		mr_utils::mr_string str( _L_("This|is|a|test|string|with|some|tokens||||||||") );
		return this->DoIt( str );
	}
};
_REGISTER_FIXTURE_(mrTokTestFollowDel);


// Test tokenize of string with leading and following token delimiters.
class mrTokTestLeadFollowDel : public TokTestBase {
public:
	mrTokTestLeadFollowDel() : TokTestBase(_L_("UTL_TOK_1_5"), _L_( "Tokenize test leading and following delimiters" )) {
		_ADD_TEST_FIXTURE_( this );
	}
							 
	bool test()		
	{ 
		mr_utils::mr_string str( _L_("||||||||This|is|a|test|string|with|some|tokens||||||||") );
		return this->DoIt( str );
	}
};
_REGISTER_FIXTURE_(mrTokTestLeadFollowDel);

#endif

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
		return mr_test::VerbCompareEqual( _FL_, 0, count, this->getVerboseBuffer() );
	}
};
_REGISTER_FIXTURE_(mrTokTestDelOnly2);



