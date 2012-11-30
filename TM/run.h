// =====================================
//  Turing Machine (C++ Implementation)
//    Alex Vinokur
//    http://up.to/alexvn
// =====================================

// ===============
// File run.h
// ===============



// ###############
#ifndef _RUN_H
#define _RUN_H

#include "turing-m.h"

#define	DEFAULT_NUMBER_OF_TAPES		1
#define	DEFAULT_METAFILE		"metafile.txt"
#define	DEFAULT_ALPHABET_FILE		"alphabet.txt"
#define	DEFAULT_STATES_FILE		"states.txt"
#define	DEFAULT_TRANSITION_FILE		"trans.txt"
#define	DEFAULT_INPUT_WORDS_FILE	"iwords.txt"

// =========
class Aux
{
friend class Run;
  private :
    vector<string>	help_request_keys_;
    void		init ();

  public :
    Aux ();
    ~Aux ();
};


// =========
class Run
{
  private :
    // ------ Private Data ------
    size_t		number_of_tapes_;
    bool		check_results_;
    size_t		serial_number_;

    static string	metafile_name_s;
    string		states_file_name_;
    string		alphabet_file_name_;
    string		transitions_file_name_;
    vector<string>	input_words_files_names_;

    static vector<vector<string> >	metafile_data_s;
    vector<vector<string> >		states_file_data_;
    vector<vector<string> >		alphabet_file_data_;
    vector<vector<string> >		transitions_file_data_;
    vector<vector<vector<string> > >	input_words_files_data_;
    Transitions_t			transitions_;

    static const vector<string>		help_request_keys_s;

    // ------ Private Methods ------
    bool	init_number_of_tapes (size_t number_of_tapes_i);
    bool	init_states (const string& states_file_name_i);
    bool	init_alphabet (const string& alphabet_file_name_i);
    bool	init_transitions (const string& transitions_file_name_i);
    bool	create_transitions ();
    bool	init_input_words (const vector<string>& input_words_files_names_i);


    static bool	read_file_S (const string& filename_i, vector<vector<string> >& data_o);
    static bool	read_metafile_S (const string& filename_i = DEFAULT_METAFILE);

    static void	invoke_turing_machine_S (
		size_t			serial_number_i,
		size_t			total_tapes_i,
		const string&		states_file_name_i,
		const string&		alphabet_file_name_i,
		const string&		transitions_file_name_i,
		const vector<string>&	input_words_files_names_i
		);

    void	invoke_turing_machine (
		const vector<string>&		states_file_data_i,
		const vector<string>&		alphabet_file_data_i,
		const vector<string>&		transitions_file_data_i,
		const vector<vector<string> >&	input_words_files_data_i
		);
    
    bool	read_alphabet_file ();
    bool	read_states_file ();
    bool	read_transitions_file ();
    bool	read_input_words_file (const string& filename_i);

    static void	show_metafile_structure_S ();
    static void	show_alphabet_file_structure_S ();
    static void	show_states_file_structure_S ();
    static void	show_transitions_file_structure_S ();
    void	show_transitions_file_structure () const;
    static void	show_input_words_file_structure_S ();

    static void	show_metafile_sample_S ();
    static void	show_alphabet_file_sample_S ();
    static void	show_states_file_sample_S ();
    static void	show_transitions_file_sample_S ();
    static void	show_input_words_file_sample_S ();
							
    static void	show_metafile_content_S ();
    void	show_alphabet_file_content () const;
    void	show_states_file_content () const;
    void	show_transitions_file_content () const;
    void	show_input_words_files_content () const;

    static void	show_help_S(const string& exe_name_i);
    static void	show_sample_S();
    static void	show_usage_S(const string& exe_name_i);

    bool	invoke_machine();

  public :
    Run (
		size_t			serial_number_i,
		size_t			total_tapes_i,
		const string&		states_file_name_i,
		const string&		alphabet_file_name_i,
		const string&		transitions_file_name_i,
		const vector<string>&	input_words_files_names_i
		);
    ~Run ();  
    static void	run (uint argc, char** argv);
};

#endif	// _RUN_H
