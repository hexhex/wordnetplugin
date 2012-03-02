
#include "WordnetAtom.h"

#include <dlvhex2/Registry.h>
#include "WordRequest.h"
#include "Profile.h"

namespace dlvhex {
  namespace wordnet {
	
	WordnetAtom::WordnetAtom() : PluginAtom("wordnet", 0) {

		LOG(DBG, "wordnet-atom: atom instantiated");
		
		#ifdef PROFILE
		total_time = 0;
		#endif
		
		// the first input constant is the search to be performed
		// (this is the same integer, as used in WordNet)
		addInputConstant();
	
		// the second input constant is the word itself
		addInputConstant();

		// ...and the output is unary.
		setOutputArity(4);

		init();
	}
	
	void WordnetAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
	
		#ifdef PROFILE
		clock_t start, end;
		double elapsed;
		cout.precision(5);
		#endif
		
		Registry& registry = *getRegistry();
		
		// get the input constants ...
		std::string word;
		int search;

		if( query.input[0].isIntegerTerm() )
			search = query.input[0].address;
		else
			throw PluginError( "Wrong input argument type" );			

		if( query.input[1].isConstantTerm() )
			word = registry.terms.getByID(query.input[1]).getUnquotedString();
		else
			throw PluginError( "Wrong input argument type" );
	
		LOG(DBG, "----------------");
		LOG(DBG, "wordnet-atom: atom invoked (search: " << search << ", word: " << word << ")");

		WordRequest *wr = new WordRequest( word, registry );

		// ...and prepare the atom's output:
		std::vector<Tuple> result;
		
		// fill the answer object...
		#ifdef PROFILE
		start = clock();
		#endif
		
		wr->doSearch( search, ALL_POS, result );

		#ifdef PROFILE
		end = clock();
		elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
		total_time += elapsed;
		LOG(PLUGIN, "wordnet-atom: search " << search << " on \"" << word << 
			"\" done in " << elapsed << " seconds (total: " << total_time << ")");
		#endif

		for (int i=0; i<result.size(); i++)
			answer.get().push_back(result[i]);

		delete wr;
	}
	
	void WordnetAtom::init() {
	
		int initStatus = -1;
		LOG(DBG, "wordnet-atom: initialising WordNet");
		
		START_TIMING

		// open database and morphological exception lists
		initStatus = wninit();

		if( initStatus != 0 )
			throw PluginError( "Failed to initialise WordNet." );

		END_TIMING("initialisation")
	}
	
  }
}
