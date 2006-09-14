#ifndef _BASEFORMS_H
#define _BASEFORMS_H

#include <wn.h>

#include <set>
#include <map>
#include <string>
using namespace std;


class BaseForms {

 public:
	BaseForms( string word );
	BaseForms( char *word );
	~BaseForms();

	set<string> getBaseForms( int pos = ALL_POS );
	unsigned short getPOS();

	void printBaseForms();


 private:
	char *word_ca;
	unsigned short pos_field;
	map<int, set<string> > bfmap;
	set<string> bfpos;

	void init();
	void load();
};

#endif
