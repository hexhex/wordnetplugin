#ifndef _WORDREQUEST_H
#define _WORDREQUEST_H

#include "impl/baseforms.h"
#include "dlvhex/Term.h"

#include <wn.h>

#include <vector>
#include <string>
using namespace std;


class WordRequest {

 public:
	WordRequest( char *word );
	WordRequest( string word );
	~WordRequest();

	void doSearch( int search, 
		       int pos, 
		       vector<Tuple> &returnSet );
	bool isPos( int pos );

 private:
	string word_str;
	char *word_ca;

	BaseForms *baseForms;
    
	void loadBaseForms();

	void prepareReturnVector( SynsetPtr synset,
				  int pos, 
				  int search,
				  vector<Tuple> &returnVector );

	void appendSynonyms( int pos,
			     int synSense,
			     SynsetPtr synset,
			     int searchSense,
			     vector<Tuple> &returnVector );

};

#endif

