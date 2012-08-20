/////--------------------------------------------------------------------------------------
///// @file	mr_iniReaderTest.cpp
///// @brief	Test case file for the inFile object.
/////
///// @author		Michael Roop
///// @date		2010
///// @version	1.0
/////
///// Copyright 2010 Michael Roop
/////--------------------------------------------------------------------------------------
//
//
//#include "mr_case.h"
//#include "mr_testMacros.h"
//#include "mr_string.h"
//#include "mr_iostream.h"
//#include "mr_fstream.h"
//#include "mr_char.h"
//#include "mr_ini_file.h"
//
//static const char* IniTestFileName = "TestIniFile1.txt";
//
///// @brief	Base class for ini file reader tests.
//class IniReaderTests : public mr_test::testCase
//{
//public:
//
//	IniReaderTests( const mr_utils::mr_string& testName, const mr_utils::mr_string& argStr ) 
//		: mr_test::testCase( testName, argStr )
//	{
//	}
//
//	bool setup()	
//	{ 
//		mr_utils::mr_ofstream s( IniTestFileName );
//		this->addTopFileGarbage( s );
//
//		this->printSection( s, L( "Section1" ) );	
//		this->printNode( s, L( "node1.1" ), L( "value1.1" ) );	
//		this->printNode( s, L( "node1.2" ), L( "value1.2" ) );	
//		this->addPostSectionGarbage( s );
//
//		this->addSectionForEmpty( s );
//
//		this->printLine( s, L( "" ) );	
//		this->printSection( s, L( "Section2" ) );	
//		this->printNode( s, L( "node2.1" ), L( "value2.1" ) );	
//		this->addMidSectionGarbage( s );
//		this->printNode( s, L( "node2.2" ), L( "value2.2" ) );	
//		this->printNode( s, L( "node2.3" ), L( "value2.3" ) );	
//		this->addEndFileGarbage( s );
//
//		return true; 
//	}
//
//	bool test()	
//	{ 
//		mr_inireader::iniFile f;
//		f.load( IniTestFileName );
//		this->getVerboseBuffer() << f;
//
//		return true; 
//	}
//
//
//
//	void printSection( mr_utils::mr_ostream& os, const mr_utils::mr_string& str  )
//	{
//		os << L( "[" ) << str.c_str() << L( "]" ) << std::endl;
//	}
//
//	void printNode( mr_utils::mr_ostream& os, const mr_utils::mr_string& key, const mr_utils::mr_string& value )
//	{
//		os <<  key.c_str() << L( "=" ) << value.c_str() << std::endl;
//	}
//
//	void printLine( mr_utils::mr_ostream& os, const mr_utils::mr_string& str  )
//	{
//		os << str.c_str() << std::endl;
//	}
//
//	virtual void addTopFileGarbage( mr_utils::mr_ofstream& os  )		{ os; }
//	virtual void addMidSectionGarbage( mr_utils::mr_ofstream& os  )		{ os; }
//	virtual void addPostSectionGarbage( mr_utils::mr_ofstream& os  )	{ os; }
//	virtual void addSectionForEmpty( mr_utils::mr_ofstream& os  )		{ os; }
//	virtual void addEndFileGarbage( mr_utils::mr_ofstream& os  )		{ os; }
//protected:
//
//	mr_utils::mr_string m_strPre;
//	mr_utils::mr_string m_strPost;
//
//};
//
//
//_DECL_TEST_( CleanIniLoad, IniReaderTests )
//_REG_TEST_( INI_1, instINI_1, CleanIniLoad, L( "Load clean Ini file" ) )
//
//
///// @brief	INI_2 Put some garbage before the first section
/////
///// @param	PreSecGrbgIni	Class name for this test case.
///// @param	IniReaderTests	Base class for this test case.
//_DECL_TEST_( PreSecGrbgIni, IniReaderTests )
//	virtual void addTopFileGarbage( mr_utils::mr_ofstream& os  )
//	{
//		this->printLine( os, L( "#Comment line" ) );
//		this->printLine( os, L( "line without comment indicator - garbage" ) );
//	}
//_REG_TEST_( INI_2, instINI_2, PreSecGrbgIni, L( "Load Ini file garbage before first section" ) )
//
//
//// Put some garbage into the middle of a section
//_DECL_TEST_( MidSecGrbgIni, IniReaderTests )
//	virtual void addMidSectionGarbage( mr_utils::mr_ofstream& os  )
//	{
//		this->printLine( os, L( "#Comment line" ) );
//		this->printLine( os, L( "line without comment indicator - garbage" ) );
//	}
//_REG_TEST_( INI_3, instINI_3, MidSecGrbgIni, L( "Load Ini file garbage mid section" ) )
//
//
//// Put some garbage into the end of a section
//_DECL_TEST_( EndSecGrbgIni, IniReaderTests )
//	virtual void addPostSectionGarbage( mr_utils::mr_ofstream& os  )
//	{
//		this->printLine( os, L( "#Comment line" ) );
//		this->printLine( os, L( "line without comment indicator - garbage" ) );
//	}
//_REG_TEST_( INI_4, instINI_4, EndSecGrbgIni, L( "Load Ini file garbage after section" ) )
//
//
//
//// Create empty section
//_DECL_TEST_( EmptySectIni, IniReaderTests )
//	virtual void addSectionForEmpty( mr_utils::mr_ofstream& os  )
//	{
//		this->printLine( os, L( "" ) );	
//		this->printSection( os, L( "Empty Section Name" ) );
//	}
//_REG_TEST_( INI_5, instINI_5, EmptySectIni, L( "Load Ini file with empty section" ) )
//
//
//
//// Put some garbage into the end of last section
//_DECL_TEST_( EndFileGrbgIni, IniReaderTests )
//	virtual void addEndFileGarbage( mr_utils::mr_ofstream& os  )
//	{
//		this->printLine( os, L( "#End file Comment line" ) );
//		this->printLine( os, L( "End file line without comment indicator - garbage" ) );
//	}
//_REG_TEST_( INI_6, instINI_6, EndFileGrbgIni, L( "Load Ini file garbage after last section" ) )
//
//
//
//
//// Create and dump an ini file.
//_DECL_TEST_( IniFileCreate, mr_test::testCase )
//	void addHeaderComment( mr_inireader::iniFile& f, const mr_utils::mr_string& msg )
//	{
//		f.addSection( mr_inireader::section( mr_inireader::iniInputLine( msg ) ) );
//	}
//
//
//	void addNode( mr_inireader::section& s, const mr_utils::mr_string& data )
//	{
//		s.addNode( mr_inireader::iniInputLine( data ) );
//	}
//
//
//	bool test()	
//	{ 
//		mr_inireader::iniFile f;
//
//		// Add header info before first section.
//		this->addHeaderComment( f, L("#*************************************************************") );
//		this->addHeaderComment( f, L("#* This is a comment block created programmaticaly           *") );
//		this->addHeaderComment( f, L("#*                                                           *") );
//		this->addHeaderComment( f, L("#* This is not normally done but done here for testing       *") );
//		this->addHeaderComment( f, L("#*                                                           *") );
//		this->addHeaderComment( f, L("#*    -- Testing the concept --                              *") );
//		this->addHeaderComment( f, L("#*************************************************************") );
//
//		mr_inireader::section sec;
//		sec.setName( L( "Fred Section" ) );
//		this->addNode( sec, L("Max=23") );
//		this->addNode( sec, L("Min=.01") );
//		this->addNode( sec, L("#this is a comment line") );
//		this->addNode( sec, L("This is a garbage line") );
//		this->addNode( sec, L("Threshold=559999.4535") );
//		this->addNode( sec, L("") );
//		f.addSection( sec );		
//
//		sec.clear();
//		sec.setName( L( "George Section" ) );
//		this->addNode( sec, L("Max=Over the top") );
//		this->addNode( sec, L("Min=Below the horizon") );
//		this->addNode( sec, L("Threshold=Freeda") );
//		this->addNode( sec, L("#this is a comment line") );
//		this->addNode( sec, L("This is a garbage line") );
//		this->addNode( sec, L("") );
//		f.addSection( sec );		
//
//
//		//sec.addNode( L("") );
//		mr_inireader::iniFile::SectionIterator it = f.getSection( L( "George Section" ) );
//		if (it != f.sections().end())
//		{
//			it->addNode( 
//				mr_inireader::iniInputLine( L("Extra=Added this after it was already in the ini file object") ) 
//			);
//		}
//
//		// Stream out the ini file.
//		this->getVerboseBuffer() << f;
//		return true; 
//	}
//_REG_TEST_( INI_7, instINI_7, IniFileCreate, L( "Create and dump ini file" ) )
