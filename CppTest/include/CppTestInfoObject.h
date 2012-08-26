///--------------------------------------------------------------------------------------
/// @file	CppTestInfoObject.h
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_INFO_OBJECT_H)
#define CPP_TEST_INFO_OBJECT_H

#include "CppTestCrossPlatform.h"
#include "ICppTestCaseArgument.h"
#include "mr_string.h"
#include <vector>


//CPPTESCASE_EXP_TEMPLATE template struct CPPTESCASE_API std::pair<mr_utils::mr_string,mr_utils::mr_string>;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator< std::pair<mr_utils::mr_string,mr_utils::mr_string> >;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector< std::pair<mr_utils::mr_string,mr_utils::mr_string> >;


namespace CppTest {


/// @typedef Test info pair define.
//typedef std::pair<mr_utils::mr_string,mr_utils::mr_string> TestInfoArgument; 

/// @typedef Typedef for a vector of argument pairs.
//typedef std::vector<TestInfoArgument> TestArguments; 




//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTestCase::TestInfoArgument>;
//CPPTESCASE_EXP_TEMPLATE template struct CPPTESCASE_API std::pair<mr_utils::mr_string,mr_utils::mr_string>;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTestCase::TestInfoArgument>;



///--------------------------------------------------------------------------------------
///
/// @brief	Class to abstract the information necessary to retrieve a test case and the
///			arguments to send it.
///
/// The testInfoObject is built by the derived script readers from the script data that 
/// they parse.  
///
/// It will hold the test name as well as any arguments that are to be sent to the test 
/// case after it is retrieved and before it is executed.
///
///--------------------------------------------------------------------------------------
class CPPTESCASE_API TestInfoObject {

public:

	/// @brief	Constructor.
	TestInfoObject();


	/// @brief	Retrieves active status for the test case as indicated by the script line.
	///
	/// A script may inidicate that a test is inactive and not to be run. It is up to the 
	/// derived script readers to determine according to its own rules.  
	///
	/// @return true if active and ready to be run otherwise false.
	bool IsActive() const;


	/// @brief	Sets the active status for the test case as indicated by the script line.
	///
	/// A script may inidicate that a test is inactive and not to be run. It is up to the 
	/// derived script readers to determine according to its own rules.  
	///
	/// @param	active	true if active and ready to be run otherwise false. Default is true.
	void SetActive( bool active = true );


	/// @brief	Indicates that there is no longer any data in the script file to define a test.
	///
	/// @return true if the object contains test data from the script otherwise false.
	bool IsNull() const;


	/// @brief	Set the state of the object to indicate if it has data.
	///
	/// @param	inNull	true if the object contains test data from the script otherwise false.
	void SetNull( bool isNull );


	/// @brief	Retrieve the name of the test.
	///
	/// @return	The test name.
	const mr_utils::mr_string& GetName() const;


	/// @brief	Set the name of the test.
	///
	/// @param	name	The test name.
	void SetName( const mr_utils::mr_string& name );


	/// @brief	Retrieve the argument set.
	///
	/// @return	The argument set.
	const TestCaseArguments& GetArguments() const;


	/// @brief	Add an argument to the argument set.
	///
	/// @param	name	The name of the argument.
	/// @param	value	The value of the argument.
	void AddArgument(const mr_utils::mr_string& name, const mr_utils::mr_string& value);

private:
	bool							m_isActive;		///< The active status.
	bool							m_isNull;		///< The NULL status.
	mr_utils::mr_string				m_name;			///< Test Name.
	std::vector<CppTest::ICaseArgument>	m_arguments;	///< Test arguments.

};



} // end namespace

//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::TestInfoObject>;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::TestInfoObject>;




#endif