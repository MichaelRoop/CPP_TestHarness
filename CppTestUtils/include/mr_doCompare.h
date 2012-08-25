///--------------------------------------------------------------------------------------
/// @file	mr_doCompare.h
/// @brief	Comparison functionality between same or differing types.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///
///
/// @todo Add specialisations for string type mismatch wide narrow and other
/// type to type conversions for comparison.
///
///	Note: Use the template classes below rather than the template classes directly.  They will 
///	automaticaly resolve the template args from the function arg types so you do not have to use 
///	the <> notation.  They will automaticaly call the right template class specialization which 
///	will do the work.
///
///------------------------------------------------------------------------------------------------
#if !defined(MR_DO_COMPARE_H)
#define MR_DO_COMPARE_H


namespace mr_utils {

///--------------------------------------------------------------------------------------
///
/// @brief	Template comparison class to do comparisons between two types.
///
/// @tparam	T	The first type in the comparison.
/// @tparam	T2	The second type in the comparison.
///
///------------------------------------------------------------------------------------------------
template<class T, class T2>
class DoCompare {
public:

	/// @brief	Equal operator for two instances of the same type.
	///
	///	@param	lhs	Variable on left hand side operator.
	///	@param	rhs	Variable on right hand side operator.
	///
	/// @return	true if both values are the same, otherwise false.
	static bool equal(const T& lhs, const T2& rhs) {
		return lhs == rhs;
	}


	/// @brief	Not equal operator for two instances of the same type.
	///
	///	@param	lhs	Variable on left hand side operator.
	///	@param	rhs	Variable on right hand side operator.
	///
	/// @return	true if both values are different, otherwise false.
	static bool notEqual(const T& lhs, const T2& rhs) {
		return !equal( lhs, rhs );
	}
};



/// @brief	Template function for equality test with automatic type conversion.
///
/// @tparam	T	The first type in the comparison.
/// @tparam	T2	The second type in the comparison.
///	@param	lhs	Variable on left hand side operator.
///	@param	rhs	Variable on right hand side operator.
///
/// @return	true if both values are the same, otherwise false.
template<class T, class T2>
bool CompareEqual(const T&	lhs, const T2& rhs) {
	return DoCompare<T,T2>::equal( lhs, rhs );
}


/// @brief	Template function for non equality test with automatic type conversion.
///
/// @tparam	T	The first type in the comparison.
/// @tparam	T2	The second type in the comparison.
///	@param	lhs	Variable on left hand side operator.
///	@param	rhs	Variable on right hand side operator.
///
/// @return	true if both values are different, otherwise false.
template<class T, class T2>
bool CompareNotEqual(const T&	lhs, const T2& rhs) {
	return DoCompare<T,T2>::notEqual( lhs, rhs );
}




//// Class specialisation to bridge between wide char to narrow char output stream.
//template<>
//class DoCompare<std::wstring>
//{
//public:
//	static bool compareEqual( const std::wstring& expected, const std::wstring& actual )
//	{
//		return expected == actual;
//	}
//
//	static bool compareNotEqual( const std::wstring& notExpected, const std::wstring& actual )
//	{
//		return !compareEqual( notExpected, actual );
//	}
//};
//
//
//// Class specialisation to bridge between narrow char to wide output stream.
//template<>
//class compClass<std::string>
//{
//public:
//	static bool compareEqual( const std::string& expected, const std::string& actual )
//	{
//		return expected == actual;
//	}
//
//	static bool compareNotEqual( const std::string& notExpected, const std::string& actual )
//	{
//		return !compareEqual( notExpected, actual );
//	}
//};
//


} // end namespace


#endif