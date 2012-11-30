// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File macro.h
// ===============



// ###############
#ifndef _MACRO_H
#define _MACRO_H

#include "version.h"

#define	COUT	cout << "[ " << setw(12) << left << __FILE__ << ", " << setw (3) << right << __LINE__ << " ] "
#define	FATAL_MSG(t)	cout << endl; COUT << "FATAL ERROR : " << t << endl
#define	WARNING_MSG(t)	COUT << "WARNING : " << t << endl
#define	INFO_MSG(t)	cout << string (20, '#') << endl; cout << "INFO : " << t << endl; cout << string (20, '#') << endl

#define	IF_NOT_EMPTY(mg, wd, ch) \
		if (!mg.empty()) \
		{ \
		cout << "\t" << string (wd, ch) << " " << mg << " " << string (wd, ch) << endl; \
		}

#define MIN_VALUE(x,y)  ((x) < (y) ? (x) : (y))
#define MAX_VALUE(x,y)  ((x) > (y) ? (x) : (y))

#define ASSERT(x)       if (!(x)) {cerr << endl << endl << "\t=== BUG IN PROGRAM ===" << endl;}; assert (x)

#endif	// _MACRO_H
