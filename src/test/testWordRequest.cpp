#include <iostream>
#include <string>
#include <set>

#include "WordRequest.h"

using namespace std;
using namespace dlvhex;
using namespace dlvhex::wordnet;

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
