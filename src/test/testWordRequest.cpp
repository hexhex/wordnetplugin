#include <iostream>
#include <string>
#include <set>
using namespace std;

#include "WordRequest.h"

main( int argc, char **argv) {

    WordRequest *wr = new WordRequest( argv[1] );
    cout << "entered word: " << argv[1] << endl;

    
    set<string> synonyms = wr->getSynonyms( ALL_POS );
    set<string>::iterator it;

    for( it = synonyms.begin(); it != synonyms.end(); it++ )
	cout << "\t" << *it << endl;
    
    delete wr;
    wr = NULL;
}
