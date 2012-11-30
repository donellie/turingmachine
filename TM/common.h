// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File common.h
// ===============



// ###############
#ifndef _COMMON_H
#define _COMMON_H

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <assert.h>
using namespace std;


#include "macro.h"

// ===================
unsigned int is_udec (char * const str_i);
unsigned int is_dec (char * const str_i);
unsigned int is_hex (char * const str_i);


// ===================
template <typename T>
string to_string (
	const T& value_i, 
	int width_i = -1, 
	char fill_i = ' ', 
	bool align_i = true, 		// true - left
	const string& prefix_i = string ()
	)
{
string		ret_string_value;
ostringstream	tmp_osstr;

        // =================================
        tmp_osstr << prefix_i;
        if (width_i > 0)
        {
                tmp_osstr << setw (width_i);
                tmp_osstr << setfill (fill_i);
        }
        tmp_osstr << (align_i ? left : right) << value_i;

        // =================================
        ret_string_value = tmp_osstr.str();
        // =================================
        return ret_string_value;

} // string to_string (T value_i)


#endif	// _COMMON_H
