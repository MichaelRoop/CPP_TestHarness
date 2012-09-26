#if !defined(_TEST_LIST_H_)
#define _TEST_LIST_H_

// Needs to be here if using ld to link
#if defined(__linux) || defined(_linux_)
// the std iostream does not seem to link in unless you force it
// http://www.linuxquestions.org/questions/programming-9/fyi-shared-libs-and-iostream-c-331113/
//extern "C" {
//    void *__dso_handle = 0;
//}


#endif

#include "mr_testSharedPtr.h"
#include "mr_util_str_token_tests.h"
#include "mr_util_str_trim_tests.h"
#include "MrTestMacroTests.h"



#endif







