// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File tape.cpp
// ===============



// ###############
#include "tape.h"

// =========
// Constructor-0
Tape::Tape (
	const vector<symbol_t>& empty_symbols_alphabet_i, 
	const vector<symbol_t>& internal_alphabet_i,
	const vector<symbol_t>& input_alphabet_i,
	const string& msg_i
	) 
	:
	empty_symbols_alphabet_ (empty_symbols_alphabet_i),
	internal_alphabet_ (internal_alphabet_i),
	input_alphabet_ (input_alphabet_i),
	position_ (0),
	max_symbol_size_ (0)
{

  IF_NOT_EMPTY (msg_i, 3, '=');

  check_results_ = check_alphabet ();
  set_max_symbol_size_ ();
  //show_alphabet ("Tape constructed");

} 

// =========
// Destructor
Tape::~Tape ()
{
}
 
// =========
void Tape::clear_it ()
{
  position_ = 0;
  tape_.clear();
} 

// =========
void Tape::shift_position (shift_t shift_i)
{
  assert (is_valid_shift(shift_i));
  
  if (shift_i == LEFT_SHIFT)
  {
    assert (position_ > 0);
    position_--;
    return;
  }

  if (shift_i == RIGHT_SHIFT)
  {
    position_++;
    assert (position_ <= tape_.size());
    assert (!empty_symbols_alphabet_.empty());
    if (position_ == tape_.size()) tape_.push_back (empty_symbols_alphabet_.front());
    assert (position_ < tape_.size());
    return;
  }

  if (shift_i == NO_SHIFT)
  {
    // Do nothing
    return;
  }
  
  assert (0);

}


// =========
symbol_t Tape::get_position_symbol () const
{
  assert (position_ < tape_.size());

symbol_t ret_symbol = tape_[position_];
  assert (is_valid_symbol(ret_symbol));
  return ret_symbol;
}

// =========
size_t Tape::get_position () const
{
  assert (position_ < tape_.size());
  return position_;
}


// =========
vector<symbol_t> Tape::get_full_alphabet () const
{
vector<symbol_t>	ret_vector;

  copy (empty_symbols_alphabet_.begin(), empty_symbols_alphabet_.end(), back_inserter(ret_vector));
  copy (input_alphabet_.begin(), input_alphabet_.end(), back_inserter(ret_vector));
  copy (internal_alphabet_.begin(), internal_alphabet_.end(), back_inserter(ret_vector));

  return ret_vector;
}



// =========
void Tape::set_position_symbol (const symbol_t& symbol_i)
{
  assert (position_ < tape_.size());
  assert (is_valid_symbol(symbol_i));
  tape_[position_] = symbol_i;
}


// =========
void Tape::set_max_symbol_size_ ()
{
vector<symbol_t>	tmp_full_alphabet = get_full_alphabet();
  assert (max_symbol_size_ == 0);
  for (size_t i = 0; i < tmp_full_alphabet.size(); i++)
  {
    max_symbol_size_ = MAX_VALUE (max_symbol_size_, tmp_full_alphabet[i].size()); 
  }
}


// =========
bool Tape::is_input_symbol (const symbol_t& symbol_i) const
{
  return (find (input_alphabet_.begin(), input_alphabet_.end(), symbol_i) != input_alphabet_.end());
}

// =========
bool Tape::is_internal_symbol (const symbol_t& symbol_i) const
{
  return (find (internal_alphabet_.begin(), internal_alphabet_.end(), symbol_i) != internal_alphabet_.end());
}

// =========
bool Tape::is_empty_symbol (const symbol_t& symbol_i) const
{
  return (find (empty_symbols_alphabet_.begin(), empty_symbols_alphabet_.end(), symbol_i) != empty_symbols_alphabet_.end());
}

// =========
bool Tape::is_valid_symbol (const symbol_t& symbol_i) const
{
  return (is_input_symbol (symbol_i) || is_internal_symbol (symbol_i) || is_empty_symbol (symbol_i));
}

// =========
bool Tape::is_valid_shift (shift_t shift_i) const
{
  return ((shift_i == LEFT_SHIFT) || (shift_i == NO_SHIFT) || (shift_i == RIGHT_SHIFT)); 
}



// =========
bool Tape::check_alphabet () const
{
bool	ret_bool_value = true;

symbol_t	phisical_empty_symbol = string();
vector<symbol_t>::const_iterator	iter;

  assert (!empty_symbols_alphabet_.empty());
  assert (!input_alphabet_.empty());
  assert (!internal_alphabet_.empty());

  // ---------
  iter = find (empty_symbols_alphabet_.begin(), empty_symbols_alphabet_.end(), phisical_empty_symbol); 
  if (iter != empty_symbols_alphabet_.end())
  {
    ret_bool_value = false;
    FATAL_MSG	("Empty symbols alphabet -> symbol#"
		<< distance (empty_symbols_alphabet_.begin(), iter)
		<< " is phisically empty : <"
		<< *iter
		<< ">"
		);
  }

  iter = find (input_alphabet_.begin(), input_alphabet_.end(), phisical_empty_symbol); 
  if (iter != input_alphabet_.end())
  {
    ret_bool_value = false;
    FATAL_MSG	("Input alphabet -> symbol#"
		<< distance (input_alphabet_.begin(), iter)
		<< " is phisically empty : <"
		<< *iter
		<< ">"
		);
  }


  iter = find (internal_alphabet_.begin(), internal_alphabet_.end(), phisical_empty_symbol); 
  if (iter != internal_alphabet_.end())
  {
    ret_bool_value = false;
    FATAL_MSG	("Internal alphabet -> symbol#"
		<< distance (internal_alphabet_.begin(), iter)
		<< " is phisically empty : <"
		<< *iter
		<< ">"
		);
  }

  // ------
vector<symbol_t> tmp_full_alphabet = get_full_alphabet();
vector<symbol_t>::iterator	iter2;
  for (iter2 = tmp_full_alphabet.begin(); iter2 != tmp_full_alphabet.end(); iter2++)
  {
    assert (count (iter2, tmp_full_alphabet.end(), *iter2));
    if (count (iter2, tmp_full_alphabet.end(), *iter2) > 1)
    {
      ret_bool_value = false;
      FATAL_MSG	("Alphabets -> symbol "
		<< "<"
		<< (*iter2)
	 	<< ">"
		<< " occurs more than once"
		);
    }
  }
  
  return ret_bool_value;

}

// =========
void Tape::show_alphabet (const string& msg_i) const
{
  IF_NOT_EMPTY (msg_i, 3, '=');

string text_empty_symbols_alphabet ("Empty symbols alphabet");
string text_input_alphabet ("Input alphabet");
string text_internal_alphabet ("Internal alphabet");
size_t text_max_size = 0;

  text_max_size	= MAX_VALUE(text_max_size, text_empty_symbols_alphabet.size());
  text_max_size	= MAX_VALUE(text_max_size, text_input_alphabet.size());
  text_max_size	= MAX_VALUE(text_max_size, text_internal_alphabet.size());


  cout << setw(text_max_size) << left << text_empty_symbols_alphabet.c_str() << " : ";
  for (size_t i = 0; i < empty_symbols_alphabet_.size(); i++)
  {
    cout << setw (max_symbol_size_) << empty_symbols_alphabet_[i].c_str() << " ";
  }
  cout << endl;

  cout << setw(text_max_size) << left << text_input_alphabet.c_str() << " : ";
  for (size_t i = 0; i < input_alphabet_.size(); i++)
  {
    cout << setw (max_symbol_size_) << input_alphabet_[i].c_str() << " ";
  }
  cout << endl;

  cout << setw(text_max_size) << left << text_internal_alphabet.c_str() << " : ";
  for (size_t i = 0; i < internal_alphabet_.size(); i++)
  {
    cout << setw (max_symbol_size_) << internal_alphabet_[i].c_str() << " ";
  }
  cout << endl;


}


// =========
void Tape::show_tape (const string& msg_i) const
{

  IF_NOT_EMPTY (msg_i, 3, '=');

#define	LEFT_USUAL_DELIM	" "
#define	RIGHT_USUAL_DELIM	" "
#define	LEFT_SCAN_DELIM		"["
#define	RIGHT_SCAN_DELIM	"]"
string	left_delim;
string	right_delim;

  for (size_t i = 0; i < tape_.size(); i++)
  {
    if (get_position() == i)
    {
      left_delim = LEFT_SCAN_DELIM;
      right_delim = RIGHT_SCAN_DELIM;
    }
    else
    {
      left_delim = LEFT_USUAL_DELIM;
      right_delim = RIGHT_USUAL_DELIM;
    }
    cout	<< left_delim 
		<< setw (max_symbol_size_) 
		<< tape_[i].c_str() 
		<< right_delim 
		<< " ";
  }
  cout << endl;

}

