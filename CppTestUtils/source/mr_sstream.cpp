


#include "mr_sstream.h"
#include "mr_string.h"

namespace mr_utils
{

void ResetStringStream(mr_stringstream& ss) {
	// set a new string held by the string stream
	ss.str(mr_utils::mr_string());

	// Clear any error state back to goodbit
	ss.clear();
}




}