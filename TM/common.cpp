// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File common.cpp
// ===============



// ###############
#include "common.h"


// ==================================
// ---------------------------------
// Is a string an unsigned decimal?
// ---------------------------------
unsigned int is_udec (char * const str_i)
{
  char *p = &str_i[0];
  while (*p) if (!isdigit (*p++)) return 0;
  return str_i[0];
}

// ==================================
// ---------------------------------
// Is a string a signed decimal?
// ---------------------------------
unsigned int is_dec (char * const str_i)
{
  return (is_udec (&str_i[(str_i[0] == '-') || (str_i[0] == '+')]));
}

// ==================================
// ---------------------------------
// Is a string an hexadecimal?
// ---------------------------------
unsigned int is_hex (char * const str_i)
{
  int start_pos = ((str_i[0] == '0') && (str_i[1] == 'x')) ? 2 : 0;
  char *p = &str_i[start_pos];
  while (*p) if (!isxdigit (*p++)) return 0;
  return str_i[start_pos];
}

