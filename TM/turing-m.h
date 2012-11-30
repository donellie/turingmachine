// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File turing-m.h
// ===============



// ###############
#ifndef _TURING_M_H
#define _TURING_M_H


#include "rules.h"
#include "tape.h"


typedef map<CurSituation, NextSituation>	Transitions_t;
typedef map<size_t, Tape>			Tapes_t;


// =========
class TuringMachine
{
  private :
    // ------ Private Data ------
    const vector<state_t>	initial_states_;
    const vector<state_t>	halting_states_;
    const vector<state_t>	internal_states_;
    const Transitions_t		transitions_;
    bool			check_results_;

    vector<Transitions_t::const_iterator>	cur_transitions_;
    vector<state_t>		cur_states_;
    Tapes_t			tapes_;
    vector<uint>  		transition_statistics_;

    size_t	max_state_size_;
    size_t	max_symbol_size_;


    // ------ Private Methods ------
    void	clear_it ();
    void	set_input (const vector<vector<symbol_t> >& input_words_i);
    bool	perform_step (state_t& state_o, const string& msg_i = string());

    vector<state_t>	get_all_states () const;


    bool	is_initial_state (const state_t& state_i) const;
    bool	is_halting_state (const state_t& state_i) const;
    bool	is_internal_state (const state_t& state_i) const;
    bool	is_valid_state (const state_t& state_i) const;

    void 	set_max_state_size();
    void	set_max_symbol_size();

    bool	check_states () const;
    bool	check_alphabets () const;
    bool	check_transition () const;
    bool	check_input_words (const vector<vector<symbol_t> >& input_words_i) const;

    void	show_states (const string& msg_i = string()) const;
    void	show_alphabet (const Tapes_t::const_iterator& iter) const;
    void	show_alphabets () const;
    void	show_transition () const;
    static string	getstr_rule_S (
			Transitions_t::const_iterator iter0_i,
			Transitions_t::const_iterator iter_i,
			size_t max_state_size_i,
			size_t max_symbol_size_i
			);
    void	show_tape (const Tapes_t::const_iterator& iter) const;
    void	show_situation (const string& msg_i = string()) const;
    void	show_statistics (const string& msg_i = string()) const;

    void	show_input (const vector<vector<symbol_t> >& input_words_i) const;			

  public :
    TuringMachine (
	size_t	number_of_tapes_i,
	// ---
	const vector<state_t>& initial_states_i, 
	const vector<state_t>& halting_states_i, 
	const vector<state_t>& internal_states_i,
	// ---
	const vector<symbol_t>& empty_symbols_alphabet_i, 
	const vector<symbol_t>& internal_alphabet_i,
	const vector<symbol_t>& input_alphabet_i,
	// ---
	const Transitions_t& transitions_i,
	// ---
	const string& msg_i = string ()
	);
    ~TuringMachine ();  
    bool	process_input (
			const vector<vector<symbol_t> >& input_words_i,
			const string& msg_i = string()
			);
    void	show_env () const;
    bool	get_check_results () const;

};

#endif	// _TURING_M_H
