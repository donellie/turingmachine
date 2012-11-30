// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File tape.h
// ===============



// ###############
#ifndef _TAPE_H
#define _TAPE_H

#include "defs.h"


// =========
#define LEFT_SHIFT	"L"
#define NO_SHIFT	"N"
#define RIGHT_SHIFT	"R"

// =========
class Tape
{
friend class TuringMachine;
  private :
    // ------ Private Data ------
    const vector<symbol_t>	empty_symbols_alphabet_;
    const vector<symbol_t>	internal_alphabet_;
    const vector<symbol_t>	input_alphabet_;
    
    vector<symbol_t>		tape_;
    size_t			position_;
    bool			check_results_;
    size_t			max_symbol_size_;

    // ------ Private Methods ------
    void	clear_it();
    vector<symbol_t>	get_full_alphabet() const;

    void	shift_position (shift_t shift_i);
    symbol_t	get_position_symbol () const;
    void	set_position_symbol (const symbol_t& symbol_i);
    size_t	get_position () const;

    void	set_max_symbol_size_ ();
    
 
    bool	is_input_symbol (const symbol_t& symbol_i) const;
    bool	is_internal_symbol (const symbol_t& symbol_i) const;
    bool	is_empty_symbol (const symbol_t& symbol_i) const;
    bool	is_valid_symbol (const symbol_t& symbol_i) const;
    bool	is_valid_shift (shift_t shift_i) const;

    bool	check_alphabet () const;
    void	show_alphabet (const string& msg_i = string()) const;
    void	show_tape (const string& msg_i = string()) const;

  public :
   Tape () {}
    Tape (
	const vector<symbol_t>& empty_symbols_alphabet_i, 
	const vector<symbol_t>& internal_alphabet_i,
	const vector<symbol_t>& input_alphabet_i,
	const string& msg_i = string()
	);
    ~Tape ();  

};

#endif	// _TAPE_H
