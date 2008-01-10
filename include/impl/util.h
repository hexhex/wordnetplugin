#ifndef _UTIL_H
#define _UTIL_H

#include <string>
using namespace std;

namespace dlvhex {
  namespace wordnet {

bool isPos( unsigned short pos_field, int pos );
string quoteString( string str );
int my_display_message( char *msg );

  } // namespace wordnet
} // namespace dlvhex

#endif
