///--------------------------------------------------------------------------------------
/// @file	mr_logOutputFactory.h
/// @brief	Factory to create iLogOutput objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_LOG_OUTPUT_FACTORY_H)
#define MR_LOG_OUTPUT_FACTORY_H


#include "mr_iLogOutput.h"
#include "mr_iLogInitialiser.h"
#include "mr_sharedPtr.h"


namespace mr_test
{

typedef mr_utils::SharedPtr<mr_test::iLogOutput> logOutputSharedPtr;

//----------------------------------------------------------------------------------------
/// @brief	Class for creating iLogInitiser objects.
///
/// 
class logOutputFactory
{
public:

	///	@brief	Creates the appropriate iLogInitialiser.
	///
	/// @param	initialiser	Initialiser object. 
	static logOutputSharedPtr create( mr_utils::SharedPtr<mr_test::iLogInitialiser>& initialiser );
};



}// end namespace

#endif
