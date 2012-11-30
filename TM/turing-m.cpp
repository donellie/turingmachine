// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// =================
// File turing-m.cpp
// =================



// ###############
#include "turing-m.h"


#define	SETW_RULE_NUMBER	4
#define	UNBELIEVABLE_NUMBER_OF_TAPES	100



// =========
// =========
// Constructor-0
TuringMachine::TuringMachine (
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
	const string& msg_i
	)
	:
	initial_states_ (initial_states_i),
	halting_states_ (halting_states_i),
	internal_states_ (internal_states_i),
	transitions_ (transitions_i),
	check_results_ (true),
	transition_statistics_ (transitions_i.size()),
	max_state_size_ (0),
	max_symbol_size_ (0)
{

  IF_NOT_EMPTY (msg_i, 5, '=');

typedef Tapes_t::value_type value_type;
pair<Tapes_t::iterator, bool> the_pair;

  if (number_of_tapes_i == 0)
  {
    check_results_ = false;
    FATAL_MSG	("Illegal number of tapes : "
		<< number_of_tapes_i
		);
    return;
  }

  if (number_of_tapes_i > UNBELIEVABLE_NUMBER_OF_TAPES)
  {
    WARNING_MSG	("Unbelievable number of tapes : "
		<< number_of_tapes_i
		);
  }

  for (size_t i = 0; i < number_of_tapes_i; i++)
  {
    the_pair = tapes_.insert (value_type(i, Tape (empty_symbols_alphabet_i, internal_alphabet_i, input_alphabet_i)));
    if (!the_pair.second)
    {
      check_results_ = false;
      FATAL_MSG	("The same current position occurs more tjan once in transition rules");
      break;
    }
    assert (the_pair.second);

    if (!the_pair.first->second.check_results_)
    {
      check_results_ = false;
      FATAL_MSG	("Tape#" << i << " has problems");
      break;
    }
  }


  // ------------------------------------
  set_max_state_size();
  set_max_symbol_size();


  // ---------------
  show_env();

  // ----------------------
  if (check_results_)	check_results_ = check_states ();
  if (check_results_)	check_results_ = check_alphabets ();
  if (check_results_)	check_results_ = check_transition ();

} 

// =========
// Destructor
TuringMachine::~TuringMachine ()
{
} 

// =========
void TuringMachine::set_max_state_size()
{
vector<state_t>	tmp_all_states = get_all_states();
  assert (max_state_size_ == 0);
  for (size_t i = 0; i < tmp_all_states.size(); i++)
  {
    max_state_size_ = MAX_VALUE (max_state_size_, tmp_all_states[i].size()); 
  }

}

// =========
void TuringMachine::set_max_symbol_size()
{
Tapes_t::const_iterator iter;
  assert (max_symbol_size_ == 0);
  for (iter = tapes_.begin(); iter != tapes_.end(); iter++)
  {
    max_symbol_size_ = MAX_VALUE (max_symbol_size_, iter->second.max_symbol_size_);
  }
}

// =========
vector<state_t> TuringMachine::get_all_states () const
{
vector<state_t>	ret_vector;

  copy (initial_states_.begin(), initial_states_.end(), back_inserter(ret_vector));
  copy (halting_states_.begin(), halting_states_.end(), back_inserter(ret_vector));
  copy (internal_states_.begin(), internal_states_.end(), back_inserter(ret_vector));

  return ret_vector;

}


// =========
void TuringMachine::set_input (const vector<vector<symbol_t> >& input_words_i)
{
  assert (cur_states_.empty());
  cur_states_.push_back (initial_states_.front());
  for (size_t i = 0; i < tapes_.size(); i++) tapes_[i].tape_.clear();

  for (size_t i = 0; i < input_words_i.size(); i++) 
  {
    for (size_t j = 0; j < input_words_i[i].size(); j++) 
    {
      tapes_[i].tape_.push_back (input_words_i[i][j]);
    }
  }
}


// =========
void TuringMachine::clear_it ()
{
  cur_states_.clear();
  cur_transitions_.clear();
  for (size_t i = 0; i < transition_statistics_.size(); i++)
  {
    transition_statistics_[i] = 0;
  } 


Tapes_t::iterator iter;
  for (iter = tapes_.begin(); iter != tapes_.end(); iter++)
  {
    iter->second.clear_it();
  }

}


// =========
bool	TuringMachine::check_input_words (const vector<vector<symbol_t> >& input_words_i) const
{
Tapes_t::const_iterator	iter;

  if (input_words_i.empty())
  {
    FATAL_MSG	("No input words");
    return false;
  }

  if (input_words_i.size() != tapes_.size())
  {
    FATAL_MSG	("Number of input words ("
		<< input_words_i.size()
		<< ") is NOT equal number of tapes ("
		<< tapes_.size()
		<< ")"
		);
    return false;  
  }

size_t i;
  for (i = 0, iter = tapes_.begin(); i < input_words_i.size(); i++, iter++)
  {
    assert (iter->first == i);
    if (input_words_i[i].empty())
    {
      FATAL_MSG	("No input word for tape#"
		<< i
		);
      return false;
    }

    for (size_t j = 0; j < input_words_i[i].size(); j++)
    {
      if (!(iter->second.is_input_symbol (input_words_i[i][j])))
      {
        if (!((j == 0) && (input_words_i[i].size() == 1) && (iter->second.is_empty_symbol (input_words_i[i][j]))))
        { 
          FATAL_MSG	("Tape#"
			<< i
			<< ", symbol#"
			<< j
			<< " : "
			<< input_words_i[i][j]
			<< " is NOT input symbol"
			);
          return false;
        }
      }
    } // for (size_t j = 0; ...
  } // for (size_t i = 0; ...

  return true;
}


// =========
void TuringMachine::show_input (const vector<vector<symbol_t> >& input_words_i) const
{
  cout << endl;
  cout << "\t###### Input words on tape(s) ######" << endl;
  for (size_t i = 0; i < input_words_i.size(); i++)
  {
    cout << "Tape#" << i << " : ";
    for (size_t j = 0; j < input_words_i[i].size(); j++)
    {
      cout << setw (max_symbol_size_) << to_string (input_words_i[i][j]).c_str() << " ";
    }
    //copy (input_words_i[i].begin(), input_words_i[i].end(), ostream_iterator<symbol_t> (cout, " "));
    cout << endl;
  }
  cout << endl;
}

// =========
bool TuringMachine::perform_step (state_t& state_o, const string& msg_i)
{
  IF_NOT_EMPTY (msg_i, 5, '=');

vector<symbol_t>	scanned_symbols;
  for (size_t i = 0; i < tapes_.size(); i++)
  {
    scanned_symbols.push_back(tapes_[i].get_position_symbol ());
  }
const Transitions_t::const_iterator iter = transitions_.find (CurSituation(*cur_states_.rbegin(), scanned_symbols));

  if (iter == transitions_.end())	return false;

size_t dist = distance (transitions_.begin(), iter);
  assert (dist < transitions_.size());
  transition_statistics_[dist]++;

  cur_transitions_.push_back (iter);
  cur_states_.push_back (iter->second.get_state ());
  for (size_t i = 0; i < tapes_.size(); i++)
  {
    tapes_[i].set_position_symbol (iter->second.get_symbol (i));
    tapes_[i].shift_position (iter->second.get_shift(i));
  }
 
  state_o = *cur_states_.rbegin();;
  return true;

}

// =========
bool TuringMachine::process_input (
		const vector<vector<symbol_t> >& input_words_i,
		const string& msg_i
		)
{
  IF_NOT_EMPTY (msg_i, 5, '=');

  if (!check_results_)
  {
    FATAL_MSG	("Invalid Turing Machine definition");
    return false;
  }

  cout << endl;
  show_input (input_words_i);
  if (!check_input_words(input_words_i))
  {
    FATAL_MSG	("Invalid input words");
    return false;
  }
  clear_it ();
  set_input (input_words_i);


  // ------------------
state_t	state;
bool	ret_bool_value;

  cout << endl;
  cout << endl;
  cout << "\t###### Processing ######" << endl;
  show_situation ("Initial status");
  for (int i = 0; ; i++)
  {
    ret_bool_value = perform_step (state);  
    if (!ret_bool_value)
    { 
      cout << "\t" << "Failure : 1) There exists no appropriate rule" << endl;
      cout << "\t" << "          2) Current state is not halting one" << endl;
      break;
    }
    show_situation ("Status#" + to_string (i + 1));
    if (is_halting_state (state))
    {
      cout << "\t" << "Success : Current state is halting one" << endl;
      break;
    }
  }

const size_t the1_setw = 39;
const size_t the2_setw = 3;

  cout << endl;
  cout << "\t" << string (the1_setw, '-') << endl;
  cout << "\t" 
       << string (the2_setw, '-') 
       << " Result : Input word(s) " 
       << (ret_bool_value ? "ACCEPTED" : "REJECTED") 
       << " " 
       << string (the2_setw, '-') 
       << endl;
  cout << "\t" << string (the1_setw, '-') << endl;
  cout <<  endl;

  // -----------------------------
  show_statistics ();

  return ret_bool_value;
}


// =========
void TuringMachine::show_env () const
{
  cout << endl;
  cout << "\t###### Turing Machine Definition ######" << endl;
  show_states ();
  show_alphabets();
  show_transition ();

}


// =========
void TuringMachine::show_states (const string& msg_i) const
{
  cout << "\t   ====== States Definition ======" << endl;

  IF_NOT_EMPTY (msg_i, 5, '=');


string text_initial_states ("Initial states");
string text_halting_states ("Halting states");
string text_internal_states ("Internal states");
size_t text_max_size = 0;

  text_max_size	= MAX_VALUE(text_max_size, text_initial_states.size());
  text_max_size	= MAX_VALUE(text_max_size, text_halting_states.size());
  text_max_size	= MAX_VALUE(text_max_size, text_internal_states.size());


  cout << setw(text_max_size) << left << text_initial_states.c_str() << " : ";
  for (size_t i = 0; i < initial_states_.size(); i++)
  {
    cout << setw (max_symbol_size_) << initial_states_[i].c_str() << " ";
  }
  cout << endl;

  cout << setw(text_max_size) << left << text_halting_states.c_str() << " : ";
  for (size_t i = 0; i < halting_states_.size(); i++)
  {
    cout << setw (max_symbol_size_) << halting_states_[i].c_str() << " ";
  }
  cout << endl;

  cout << setw(text_max_size) << left << text_internal_states.c_str() << " : ";
  for (size_t i = 0; i < internal_states_.size(); i++)
  {
    cout << setw (max_symbol_size_) << internal_states_[i].c_str() << " ";
  }
  cout << endl;


}

// =========
void TuringMachine::show_alphabet (const Tapes_t::const_iterator& iter) const
{
  iter->second.show_alphabet();
}

// =========
void TuringMachine::show_alphabets () const
{
Tapes_t::const_iterator iter;
  cout << endl;
  cout << endl;
  cout << "\t   ====== Alphabet Definition ======" << endl;
  for (iter = tapes_.begin(); iter != tapes_.end(); iter++)
  {
    cout << "\t      ------ Tape# " << distance (tapes_.begin(), iter) << " ------" << endl;
    show_alphabet (iter);
    cout << endl;
  }
}

// =========
void TuringMachine::show_transition () const
{
Transitions_t::const_iterator iter;
  cout << endl;
  cout << endl;
  cout << "\t   ====== Transition Rules Definition ======" << endl;
  for (iter = transitions_.begin(); iter != transitions_.end(); iter++)
  {
    cout << getstr_rule_S (transitions_.begin(), iter, max_state_size_, max_symbol_size_) << endl;
  }
  cout << endl;
}

// =========
string TuringMachine::getstr_rule_S (
		Transitions_t::const_iterator iter0_i,
		Transitions_t::const_iterator iter_i,
		size_t	max_state_size_i,	
		size_t	max_symbol_size_i	
		)
{
ostringstream oss;
  oss	<< ""
	<< "Rule#"
	<< setw (SETW_RULE_NUMBER)
	<< right
	<< distance (iter0_i, iter_i)
	<< " :   "
	<< setw (max_state_size_i)
	<< iter_i->first.get_state().c_str()
	<< " [ " 
	<< iter_i->first.getstr_symbols(max_symbol_size_i)
	<< "] ---> "
	<< setw (max_state_size_i)
	<< iter_i->second.get_state().c_str()
	<< " [ " 
	<< iter_i->second.getstr_symbols_and_shifts(max_symbol_size_i)
	<< "]";

  return oss.str();
}
   
// =========
void TuringMachine::show_tape (const Tapes_t::const_iterator& iter) const
{
  iter->second.show_tape();
}

// =========
void TuringMachine::show_situation (const string& msg_i) const
{
Tapes_t::const_iterator iter;
const size_t size1 = 5;

  if (!cur_transitions_.empty())
  {  
const Transitions_t::const_iterator iter2 = transitions_.find ((*cur_transitions_.rbegin())->first);
    assert (iter2 != transitions_.end());
    cout << "\t" 
         << "Applied " 
         << getstr_rule_S (transitions_.begin(), iter2, max_state_size_, max_symbol_size_) 
         << endl;
    cout << endl;
  }

  IF_NOT_EMPTY (msg_i, size1, '-');


  cout << "\tState  : " << *cur_states_.rbegin() << endl;
  //cout << "\t" << string (size2, '-') << endl;

  for (iter = tapes_.begin(); iter != tapes_.end(); iter++)
  {
    cout << "Tape#" << distance (tapes_.begin(), iter) << " : ";
    show_tape (iter);
  }
  //cout << endl;

}


// =========
void TuringMachine::show_statistics (const string& msg_i) const
{
const size_t size1 = 5;

  IF_NOT_EMPTY (msg_i, size1, '-');

uint total = accumulate (transition_statistics_.begin(), transition_statistics_.end(), 0);

const string text_statistics ("Statistics");
const string text_transition ("Transition");
const string text_rules ("Rules");
const string text_times ("Times");
const string text_total ("Total");
const string delim (":");

const size_t max_size1 = MAX_VALUE (text_statistics.size(), text_transition.size());
const size_t the_size2 = 3;
const size_t the_size1 = the_size2 + 1 + max_size1 + 1 + the_size2;
const size_t the_size3 = (the_size1 - 1)/2;
const size_t the_size4 = (the_size1 - 1) - the_size3;
  assert (text_rules.size() < (the_size3 - 1));
  assert (text_times.size() < (the_size4 - 1));

const string l_border ("\t      |");		
const string r_border ("|");		

  cout << l_border << string (the_size1, '=') << r_border << endl;

  cout << l_border 
       << string (the_size2, '-') 
       << " "
       << setw (max_size1)
       << left
       << text_statistics.c_str()
       << " "
       << string (the_size2, '-') 
       << r_border 
       << endl;

  cout << l_border 
       << string (the_size2, '.') 
       << " "
       << setw (max_size1)
       << left
       << text_transition.c_str()
       << " "
       << string (the_size2, '.') 
       << r_border 
       << endl;

  cout << l_border << string (the_size1, '-') << r_border << endl;

  cout << l_border 
       << setw (the_size3 - 1)
       << right
       << text_rules.c_str()
       << " "
       << delim
       << setw (the_size4 - 1)
       << right
       << text_times.c_str()
       << " "
       << r_border 
       << endl;

  cout << l_border << string (the_size1, '-') << r_border << endl;

  for (size_t i = 0; i < transition_statistics_.size(); i++)
  {
    cout << l_border 
         << setw (the_size3 - 1)
         << right
         << i
         << " "
         << delim
         << setw (the_size4 - 1)
         << right
         << transition_statistics_[i]
         << " "
         << r_border 
         << endl;
  }
  cout << l_border << string (the_size1, '-') << r_border << endl;

  cout << l_border 
       << setw (the_size3 - 1)
       << right
       << text_total.c_str()
       << " "
       << delim
       << setw (the_size4 - 1)
       << right
       << total
       << " "
       << r_border 
       << endl;

  cout << l_border << string (the_size1, '=') << r_border << endl;

}


// =========
bool TuringMachine::is_initial_state (const state_t& state_i) const
{
  return (find (initial_states_.begin(), initial_states_.end(), state_i) != initial_states_.end());
}

// =========
bool TuringMachine::is_halting_state (const state_t& state_i) const
{
  return (find (halting_states_.begin(), halting_states_.end(), state_i) != halting_states_.end());
}


// =========
bool TuringMachine::is_internal_state (const state_t& state_i) const
{
  return (find (internal_states_.begin(), internal_states_.end(), state_i) != internal_states_.end());
}

// =========
bool TuringMachine::is_valid_state (const state_t& state_i) const
{
  return (is_initial_state(state_i) || is_halting_state (state_i) || is_internal_state (state_i));
}



// =========
bool TuringMachine::check_states () const
{
bool	ret_bool_value = true;

state_t	phisical_empty_state = string();
vector<state_t>::const_iterator	iter;

  assert (!initial_states_.empty());
  assert (!halting_states_.empty());
  assert (!internal_states_.empty());

  // ---------
  iter = find (initial_states_.begin(), initial_states_.end(), phisical_empty_state); 
  if (iter != initial_states_.end())
  {
    ret_bool_value = false;
    FATAL_MSG	("Initial state#"
		<< distance (initial_states_.begin(), iter)
		<< " is empty : <"
		<< *iter
		<< ">"
		);
  }

  iter = find (halting_states_.begin(), halting_states_.end(), phisical_empty_state); 
  if (iter != halting_states_.end())
  {
    ret_bool_value = false;
    FATAL_MSG	("Halting state#"
		<< distance (halting_states_.begin(), iter)
		<< " is empty : <"
		<< *iter
		<< ">"
		);
  }


  iter = find (internal_states_.begin(), internal_states_.end(), phisical_empty_state); 
  if (iter != internal_states_.end())
  {
    ret_bool_value = false;
    FATAL_MSG	("Internal state#"
		<< distance (internal_states_.begin(), iter)
		<< " is empty : <"
		<< *iter
		<< ">"
		);
  }

  // ------
vector<state_t> tmp_all_states = get_all_states();
vector<state_t>::iterator	iter2;
  for (iter2 = tmp_all_states.begin(); iter2 != tmp_all_states.end(); iter2++)
  {
    assert (count (iter2, tmp_all_states.end(), *iter2));
    if (count (iter2, tmp_all_states.end(), *iter2) > 1)
    {
      ret_bool_value = false;
      FATAL_MSG	("State "
		<< "<"
		<< (*iter2)
	 	<< ">"
		<< " occurs more than once"
		);
    }
  }

  // -----------
  return ret_bool_value;
} // check_states


// =========
bool TuringMachine::check_alphabets () const
{
bool	ret_bool_value = true;

Tapes_t::const_iterator	iter;
  for (iter = tapes_.begin(); iter != tapes_.end(); iter++)
  {
    assert (iter->first == static_cast<size_t> (distance (tapes_.begin(), iter)));
    if (!(iter->second.check_alphabet()))	ret_bool_value = false;	
  }

  return ret_bool_value;
}


// =========
bool TuringMachine::check_transition () const
{
bool	ret_bool_value = true;

Transitions_t::const_iterator	iter;
Tapes_t::const_iterator		iter2;
size_t		i;
state_t		cur_state;
size_t		cur_total_symbols;
symbol_t	cur_symbol;

state_t		next_state;
size_t		next_total_symbols;
symbol_t	next_symbol;
shift_t	shift;

  if (transitions_.empty())
  {
    ret_bool_value = false;
    FATAL_MSG	("No transition function");
  }

  for (iter = transitions_.begin(); iter != transitions_.end(); iter++)
  {
    const string transitions_line_info ("Transition Line#" + to_string (distance (transitions_.begin(), iter)));
    const string transitions_line_and_tape_no_info (transitions_line_info + ", tape#");

    // --- first ---
    cur_state = iter->first.get_state();
    cur_total_symbols = iter->first.get_total_symbols();

    if (!((is_initial_state (cur_state)) || (is_internal_state (cur_state))))
    {
      ret_bool_value = false;
      FATAL_MSG	(transitions_line_info
		<< " : illegal cur-state = <"
		<< cur_state
		<< ">"
		);
    }

    if (cur_total_symbols != tapes_.size())
    {
      ret_bool_value = false;
      FATAL_MSG	(transitions_line_info
		<< " : number-of-cur-symbols = "
		<< cur_total_symbols
		<< " is not equal number-of-tapes = "
		<< tapes_.size()
		);
    }


    for (i = 0, iter2 = tapes_.begin(); i < cur_total_symbols; i++, iter2++)
    {
      assert (iter2->first == i);
      cur_symbol = iter->first.get_symbol(i);

      if (!(iter2->second.is_valid_symbol(cur_symbol)))
      {
        ret_bool_value = false;
        FATAL_MSG	(transitions_line_and_tape_no_info
			<< i
			<< " : illegal cur-symbol = <"
			<< cur_symbol
			<< ">"
			);
      }
    }

    
    // --- second ---
    next_state = iter->second.get_state();
    next_total_symbols = iter->second.get_total_symbols();

    if (!((is_halting_state (next_state)) || (is_internal_state (next_state))))
    {
      ret_bool_value = false;
      FATAL_MSG	(transitions_line_info
		<< " : illegal next-state = <"
		<< next_state
		<< ">"
		);
    }

    if (next_total_symbols != tapes_.size())
    {
      ret_bool_value = false;
      FATAL_MSG	(transitions_line_info
		<< " : number-of-next-symbols = "
		<< next_total_symbols
		<< " is not equal number-of-tapes = "
		<< tapes_.size()
		);
    }

    for (i = 0, iter2 = tapes_.begin(); i < next_total_symbols; i++, iter2++)
    {
      assert (iter2->first == i);
      next_symbol = iter->second.get_symbol(i);
      shift = iter->second.get_shift(i);

      if (!(iter2->second.is_valid_symbol(next_symbol)))
      {
        ret_bool_value = false;
        FATAL_MSG	(transitions_line_and_tape_no_info
			<< i
			<< " : illegal next-symbol = <"
			<< next_symbol
			<< ">"
			);
      }

      if (!(iter2->second.is_valid_shift(shift)))
      {
        ret_bool_value = false;
        FATAL_MSG	(transitions_line_and_tape_no_info
			<< i
			<< " : illegal shift = <"
			<< shift
			<< ">"
			);
      }

    }

  } // for (iter = transition.begin(); ...
  return ret_bool_value;
}

	
// =========
bool TuringMachine::get_check_results () const
{
  return check_results_;
}


