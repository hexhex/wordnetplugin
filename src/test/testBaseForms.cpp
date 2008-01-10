// testBaseForms.cpp
// -----------------
// 16/4/06, Juergen Bock
// Tests class BaseForms

#include <iostream>
#include <list>
#include <string>

#include "BaseForms.h"
#include "wn.h"

using namespace std;
using namespace dlvhex;
using namespace dlvhex::wordnet;

void showBaseForms( set<string>::iterator b, set<string>::iterator e );

main() {
    list<string> testWords;

    // some test words:
    testWords.push_back( "trees" );
    testWords.push_back( "has" );
    testWords.push_back( "played" );
    testWords.push_back( "plays" );
    testWords.push_back( "organised" );
    testWords.push_back( "organized" );
    testWords.push_back( "jumping" );
    testWords.push_back( "read" );
    testWords.push_back( "sat" );    
    testWords.push_back( "saw" );
    testWords.push_back( "teeth" );
    testWords.push_back( "got" );

    // TODO: think of a test word with more than one base forms in the same POS

    wninit();

    // iterate through test cases:
    list<string>::iterator test_it;
    for( test_it = testWords.begin(); test_it != testWords.end(); test_it++ ) {

	cout << "Morphological base forms for \"" << *test_it << "\":" << endl;
	cout << "====================================================" << endl;

	// load base forms
	BaseForms *bfs = new BaseForms( *test_it );

	set<string>::iterator bf_it;

	// show base forms of each POS seperately
	int pos;
	for( pos = 1; pos <= NUMPARTS; pos++ ) {
	    set<string> posBaseForms = bfs->getBaseForms( pos );

	    cout << "Part of speech: " << pos << endl;
	    cout << "-----------------" << endl;
	    showBaseForms( posBaseForms.begin(), posBaseForms.end() ); 
	}

	// show base forms of all POS together
	set<string> allBaseForms = bfs->getBaseForms();

	cout << "All parts of speech:" << endl;
	cout << "--------------------" << endl;
	showBaseForms( allBaseForms.begin(), allBaseForms.end() ); 

	cout << "Parts of speech detected: " << bfs->getPOS() << endl;

	cout << endl;
    }
}


// show base forms given by iterator range
void showBaseForms( set<string>::iterator b, set<string>::iterator e ) {
    set<string>::iterator bf_it;
    for( bf_it = b; bf_it != e; bf_it++ )
	cout << "\t" << *bf_it << endl;
}

  } // namespace wordnet
} // namespace dlvhex
