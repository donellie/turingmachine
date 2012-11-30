// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ================
// File service.cpp
// ================



// ###############
#include "service.h"

// =============================
// =============================
// Constructor-0
Logo::Logo ()
{
	show_logo ("START");
}

// =============================
// Destructor
Logo::~Logo ()
{
	cout << endl;
	cout << endl;
	cout << endl;
	show_logo ("FINISH");
}

// =============================
void	Logo::show_logo (const string& msg_i) const
{
time_t timer;
	timer	= time(NULL);

const string pref1 ("\t#");
const string pref2 (pref1 + " ");

vector<string>	product_info;
  product_info.push_back (product_name);
  product_info.push_back (string ("  --> [") + string (sw_version) + string ("]"));
  product_info.push_back (string (2, ' ') + author_name);
  product_info.push_back (string (2, ' ') + author_url);
  product_info.push_back (string (2, ' ') + author_email);

vector<vector<string> >	system_info;

#if (__DJGPP__)
  system_info.push_back(vector<string>());
  system_info.rbegin()->push_back (pref2);
  system_info.rbegin()->push_back ("DJGPP ");
  system_info.rbegin()->push_back (to_string(__DJGPP__));
#ifdef __DJGPP_MINOR__ 
  system_info.rbegin()->push_back (".");
  system_info.rbegin()->push_back (to_string(__DJGPP_MINOR__));
#endif
#endif  

#if (__MINGW32__ || __MINGW__ )
  system_info.push_back(vector<string>());
  system_info.rbegin()->push_back (pref2);
  system_info.rbegin()->push_back ("MINGW");
#endif  

#if (__CYGWIN32__ || __CYGWIN__)
  system_info.push_back(vector<string>());
  system_info.rbegin()->push_back (pref2);
  system_info.rbegin()->push_back ("CYGWIN");
#endif  

#ifdef __GNUC__ 
  system_info.push_back(vector<string>());
  system_info.rbegin()->push_back (pref2);
  system_info.rbegin()->push_back ("GNU gcc version ");
  system_info.rbegin()->push_back (to_string(__GNUC__));
#ifdef __GNUC_MINOR__  
  system_info.rbegin()->push_back (".");
  system_info.rbegin()->push_back (to_string(__GNUC_MINOR__));
#ifdef __GNUC_PATCHLEVEL__   
  system_info.rbegin()->push_back (".");
  system_info.rbegin()->push_back (to_string(__GNUC_PATCHLEVEL__));
#endif
#endif
#endif  


size_t the_width = 0;
  for (size_t i = 0; i < product_info.size(); i++)
  {
    the_width = MAX_VALUE (the_width, product_info[i].size());
  }
  
  cout << endl;
  cout << pref1 << string (the_width + 1, '=') << endl;
  for (size_t i = 0; i < product_info.size(); i++)
  {
    cout << pref2 << product_info[i] << endl;
  }

  if (!system_info.empty())
  {
    cout << pref1 << string (the_width + 1, '-') << endl;
  }
  for (size_t i = 0; i < system_info.size(); i++)
  {
    copy (system_info[i].begin(), system_info[i].end(), ostream_iterator<string> (cout, ""));
    cout << endl;
  }
  cout << pref1 << string (the_width + 1, '-') << endl;

  cout << pref2 << msg_i << endl;
  cout << pref2 << asctime (localtime(&timer));
  cout << pref1 << string (the_width + 1, '=') << endl;
  cout << endl;

}

//===========			   
Logo	logo;
//===========			   
