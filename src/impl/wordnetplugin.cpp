/* -*- C++ -*- */

/**
 * @file   wordnetplugin.cpp
 * @author Juergen Bock
 * @date   06/08/2006
 *
 * @brief  Definition of classes WordNetAtom and WordNetPlugin
 */

#include "impl/wordrequest.h"
#include "impl/profile.h"
#include "dlvhex/PluginInterface.h"

#include <wn.h>

#include <iostream>
#include <string>


//
// each atom has to be derived from PluginAtom
//
class WordNetAtom : public PluginAtom
{
public:
	WordNetAtom() {

#ifdef DEBUG
		cout << "D> wordnet-atom: atom instantiated" << endl;
#endif

#ifdef PROFILE
		total_time = 0;
#endif

		// the first input constant is the search to be performed
		// (this is the same integer, as used in WordNet)
		addInputConstant();
	
		// the second input constant is the word itself
		addInputConstant();

		//
		// ...and the output is unary.
		//
		setOutputArity(4);

		init();
	}

	virtual void retrieve( const Query& query, 
			       Answer& answer ) throw (PluginError) {
#ifdef PROFILE
		clock_t start, end;
		double elapsed;

		cout.precision(5);
#endif
		//
		// get the input constants ...
		//
		std::string word;
		int search;

		if( query.getInputTuple()[0].isInt() )
			search = query.getInputTuple()[0].getInt();
		else
			throw PluginError( "Wrong input argument type" );			

		if( query.getInputTuple()[1].isString() )
			word = query.getInputTuple()[1].getUnquotedString();
		else
			throw PluginError( "Wrong input argument type" );
	
#ifdef DEBUG
		cout << "----------------" << endl << 
			"D> wordnet-atom: atom invoked (search: " <<
			search << ", word: " << word << ")" << endl;
#endif

		WordRequest *wr = new WordRequest( word );

		//
		// ...and prepare the atom's output:
		//
	
		std::vector<Tuple> out;
		//
		// fill the answer object...
		//
#ifdef PROFILE
		start = clock();
#endif
		wr->doSearch( search, ALL_POS, out );
#ifdef PROFILE
		end = clock();
		elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
		total_time += elapsed;
		cout << "P> wordnet-atom: search " << search << 
			" on \"" << word << "\" done in " <<
			elapsed << " seconds (total: " << total_time <<
		        ")" << endl;
#endif

		answer.addTuples(out);

		delete wr;
	}


private:

#ifdef PROFILE
	double total_time;
#endif

// inititalisation
	void init() {
		int initStatus = -1;

#ifdef DEBUG
		cout << "D> wordnet-atom: initialising WordNet" << endl;
#endif
		
		START_TIMING

		// open database and morphological exception lists
		initStatus = wninit();

		if( initStatus != 0 )
			throw PluginError( "Failed to initialise WordNet." );


		END_TIMING("initialisation")
	}
};



//
// A plugin must derive from PluginInterface
//
class WordNetPlugin : public PluginInterface {
public:

	//
	// register all atoms of this plugin:
	//
	virtual void getAtoms(AtomFunctionMap& a) {
		//
		// these strings will be the external atoms' 
		// names in the program
		//
		a["wordnet"] = new WordNetAtom;
    }
};


//
// now instantiate the plugin
//
WordNetPlugin theWordNetPlugin;

//
// and let it be loaded by dlvhex!
//
extern "C"
WordNetPlugin*
PLUGINIMPORTFUNCTION() {
    theWordNetPlugin.setVersion(WORDNETPLUGIN_MAJOR,
                            WORDNETPLUGIN_MINOR,
                            WORDNETPLUGIN_MICRO);

	return &theWordNetPlugin;
}
