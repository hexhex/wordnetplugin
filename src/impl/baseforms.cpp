/* -*- C++ -*- */

/**
 * @file   baseforms.cpp
 * @author Juergen Bock
 * @date   06/08/2006
 *
 * @brief  Definition of class BaseForms for 
 *         accessing WordNet's Morphy and requesting 
 *         and storing morphological base forms
 */

#include "impl/baseforms.h"
#include "impl/util.h"

#include <wn.h>

#include <map>
#include <set>
#include <string>
#include <iostream>
using namespace std;

// constructor that takes a string argument
BaseForms::BaseForms( string word ) {

	this->word_ca = new char[word.length()+1];
	memset( this->word_ca, '\0', word.length()+1 );
	word.copy( this->word_ca, word.length() );

	init();
}

// constructor that takes a char array argument
BaseForms::BaseForms( char *word ) {

	// set the word_ca field
	this->word_ca = new char[strlen( word ) + 1];
	strcpy( this->word_ca, word );

	init();
}

// destructor
BaseForms::~BaseForms() {
	delete[] word_ca;
	word_ca = NULL;
}

// common to all constructors
void BaseForms::init() {
	this->pos_field = 0;
	load();
}

// loading the morphological base forms
void BaseForms::load() {

	int pos;
	for( pos = 1; pos <= NUMPARTS; pos++ ) {
	
		// requesting base forms from WordNet
		char *newBaseForm = morphstr( word_ca, pos );

		set<string> setOfBaseForms;

		// insert and reload until no more base forms found
		while( newBaseForm != NULL ) {
			// more than one base forms are very rare, so it's not
			// a big deal to process this bit-or here:
			pos_field |= (1 << pos-1);

			string baseFormStr( newBaseForm );
			setOfBaseForms.insert( baseFormStr );
			newBaseForm = morphstr( NULL, pos );
		}

		bfmap[pos] = setOfBaseForms;
	}
}

// prints all gatheres base forms
// (for testing purposes)
void BaseForms::printBaseForms() {
	int pos;
    
	cout << "Base Forms for " << this->word_ca << endl;
	for( pos = 1; pos <= NUMPARTS; pos++ ) {
		cout << "Part of Speech: " << pos << endl;
		set<string> bfpos = (this->bfmap)[pos];
		set<string>::iterator it;
		for( it = bfpos.begin(); it != bfpos.end(); it++ )
			cout << "\t" << *it << endl;
	}
}

// returns base forms of given part of speech
// or all if not specified
set<string> BaseForms::getBaseForms( int pos ) {

	set<string> returnSet;

	if( pos == ALL_POS ) {
		int pos_count;
		for( pos_count = 1; pos_count <= NUMPARTS; pos_count++ ) {
			set<string>::iterator begin_pos = (this->bfmap)[pos_count].begin();
			set<string>::iterator end_pos = (this->bfmap)[pos_count].end();
			returnSet.insert( begin_pos, end_pos );
		}
	} else
		returnSet = (this->bfmap)[pos];

	return returnSet;
}

// returns bit field of detected parts of speech
unsigned short BaseForms::getPOS() {
	return this->pos_field;
}
