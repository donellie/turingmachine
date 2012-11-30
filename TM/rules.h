// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File rules.h
// ===============



// ###############
#ifndef _RULES_H
#define _RULES_H

#include "defs.h"


// =========
class CurSituation
{
friend bool operator< (const CurSituation& inst1_i, const CurSituation& inst2_i);
  private :
    const state_t		cur_state_;
    const vector<symbol_t>	cur_symbols_;	// cur_symbols_.size() == number of tapes

  public :
    CurSituation ();
    CurSituation (const state_t& cur_state_i, const vector<symbol_t>& cur_symbols_i);
    ~CurSituation ();

   state_t	get_state () const;
   symbol_t	get_symbol (size_t index_i) const;
   size_t	get_total_symbols () const;
   string	getstr_symbols (size_t max_symbol_size_i = 0) const;
};

// =========
class SymbolAndShift 
{ 
friend class NextSituation;
  private :
    symbol_t symbol_; 
    shift_t shift_; 

  public :
    SymbolAndShift (const symbol_t& symbol_i, shift_t shift_i) : symbol_ (symbol_i), shift_ (shift_i) {}
    ~SymbolAndShift () {} 
};

// =========
class NextSituation
{
  private :
    const state_t			next_state_;
    const vector<SymbolAndShift>	next_symbols_and_shifts_;	// next_symbol_and_shift_.size() == number of tapes

  public :
    NextSituation ();
    NextSituation (const state_t& next_state_i, const vector<SymbolAndShift>& next_symbols_and_shifts_i);
    ~NextSituation ();	

   state_t	get_state () const;
   symbol_t	get_symbol (size_t index_i) const;
   shift_t	get_shift (size_t index_i) const;
   size_t	get_total_symbols () const;
   string	getstr_symbols_and_shifts(size_t max_symbol_size_i = 0) const;
};



#endif	// _RULES_H
