/* -*- C++ -*- */

/**
 * @file   util.cpp
 * @author Juergen Bock
 * @date   06/08/2006
 *
 * @brief  Definition of useful functions
 */

#include "impl/util.h"
#include "dlvhex/Error.h"

#include <string>
using namespace std;

namespace dlvhex {
  namespace wordnet {

bool isPos( unsigned short pos_field, int pos ) {
	return (pos_field & (1 << pos-1)) > 0;
}

// this is a bit nasty but probably the only way
// to convert a string to a char*
// c_str can't be used, since it returns a const char*
void stringToChar( string str, char *word_buf ) {
	int word_length = str.size()+1;
//      char word_buf[word_length];
	memset( word_buf, '\0', word_length+1 ); 
	str.copy( word_buf, word_length );

}

string quoteString( string str ) {
	return "\"" + str + "\"";
}

int my_display_message( char *msg ) {
	// all WordNet error messages that end up in this
	// function seem to begin with "WordNet library error: "
	// so no additional message prefix is required
	throw PluginError( msg );
}

  } // namespace wordnet
} // namespace dlvhex
