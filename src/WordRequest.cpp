/* -*- C++ -*- */

/**
 * @file   wordrequest.cpp
 * @author Juergen Bock
 * @date   06/08/2006
 *
 * @brief  Definition of class WordRequest to represent
 *         a WordNet query and its results
 */

#include "WordRequest.h"
#include "Util.h"
#include "Profile.h"

#include <dlvhex2/Registry.h>
#include <dlvhex2/Error.h>
#include <dlvhex2/Term.h>

#include <wn.h>

#include <iostream> 
#include <cstring>

using namespace std;

namespace dlvhex {
  namespace wordnet {

WordRequest::WordRequest( string word, Registry& reg ) : registry(reg) {

  ///@todo TK: whoopsiedaisy, memory leak time!

	// set word_ca
	this->word_ca = new char[word.length()+1];
	memset( this->word_ca, '\0', word.length()+1 );
	word.copy( this->word_ca, word.length() );

	// also set word_str
	this->word_str = word;

	baseForms = NULL;
	display_message = my_display_message;
}


WordRequest::WordRequest( char *word, Registry& reg ) : registry(reg) {

  ///@todo TK: whoopsiedaisy, memory leak time!

	// set word_ca
	this->word_ca = new char[strlen( word ) + 1];
	strcpy( this->word_ca, word );

	// also set word_str
	this->word_str = word;

	baseForms = NULL;
	display_message = my_display_message;
}



WordRequest::~WordRequest() {
	delete baseForms;
	baseForms = NULL;
}


void WordRequest::loadBaseForms() {

	LOG(DBG, "wordnet-atom: loading baseforms");

	START_TIMING
	baseForms = new BaseForms( this->word_str );
	END_TIMING("baseforms loaded")
}


void WordRequest::doSearch( int search, int pos, vector<Tuple> &returnVector) {

	SynsetPtr synset;

	if( pos == ALL_POS )
		LOG(DBG, "wordnet-atom: checking all parts of speech");

	int currentPos;
	
	for( currentPos = 1; currentPos <= NUMPARTS; currentPos++ ) {
		if( pos == currentPos || pos == ALL_POS ) {
			
			START_TIMING
			LOG(DBG, "wordnet-atom: checking part of speech " << currentPos);
			synset = findtheinfo_ds( word_ca, currentPos, search, ALLSENSES );
			END_TIMING("WordNet called")

			prepareReturnVector( synset, currentPos, search, returnVector );
		}
	}

	free_syns( synset );

	// If the return vector is still empty at this stage,
	// we check, if there are baseforms of the input.
	// All baseforms are treated equally, so no distinction
	// between different baseforms of the same morphological
	// input form is possible.
	if( returnVector.empty() ) {
		set<string>::iterator it;
		loadBaseForms();
		set<string> bf = baseForms->getBaseForms();
		for( it = bf.begin(); it != bf.end(); it++ ) {
			WordRequest *bfRequest = new WordRequest( *it, registry );
			bfRequest->doSearch( search, pos, returnVector);
			delete bfRequest;
			bfRequest = NULL;
		}
	}
}


// Checks for a particular part-of-speech
bool WordRequest::isPos( int pos ) {
	unsigned int pos_template = bit( pos );
	unsigned int pos_field = in_wn( this->word_ca, pos );
	return ((pos_field & pos_template) > 0);
}


//
// Prepares the return vector delivered by the external atom.
// The function takes a SynsetPtr which contains the requested
// words / pointer of a WordNet query and a part-of-speech integer.
// The output is passed via the reference to a returnVector.
// All senses of the request will be returned.
// 
// This implementation descends only one level!
//
// The return vector contains 4 fields (in this order):
//   - part-of-speech number
//   - synonym sense number
//   - word according to query
//   - sense number of query
//
// Note: If the query is SYNS, both sense numbers will be the same
//
void WordRequest::prepareReturnVector( SynsetPtr synset, int pos, int search, 
									   vector<Tuple> &returnVector ) {

	// Iterate through synonym senses:
	int synSense = 1;
	while( synset != NULL ) {
		SynsetPtr searchset;
		if( search == SYNS ) {

			// No ptrlist available for this search, 
			// so just iterate through 0-level synsets:
			appendSynonyms( pos, 
							synSense,   // only 1 sense available 
							synset,     // no descending
							synSense,   // only 1 sense available
							returnVector );
		} else {
			// descend 1 level
			searchset = synset->ptrlist;
	
			// Iterate through search senses:
			int searchSense = 1;
			while( searchset != NULL ) {

				// Iterate through words itself
				appendSynonyms( pos, 
								synSense,   // sense in synset
								searchset,  // 1-level synset
								searchSense,// sense in searchset
								returnVector );

				searchset = searchset->nextss;
				searchSense++;
			}
		}

		synset = synset->nextss;
		synSense++;
	}
}


//
// Appends all words of a synset to the return vector
// 
void WordRequest::appendSynonyms(int pos, int synSense, SynsetPtr synset, 
								 int searchSense, vector<Tuple> &returnVector) {

	if(synset != NULL) {
		Tuple quadruple;
		for( int wordCounter = 0; wordCounter < synset->wcount; wordCounter++ ) {
			quadruple.clear();
			quadruple.push_back(ID::termFromInteger(pos));
			quadruple.push_back(ID::termFromInteger(synSense));
			quadruple.push_back(registry.storeConstantTerm(quoteString(synset->words[wordCounter]), false));
			quadruple.push_back(ID::termFromInteger(searchSense));
			
			returnVector.push_back(quadruple);
		}
	}
}

  } // namespace wordnet
} // namespace dlvhex
