#ifndef _WN_PLUGIN_WNATOM_H_
#define _WN_PLUGIN_WNATOM_H_

#include <dlvhex2/PluginInterface.h>

namespace dlvhex {
  namespace wordnet {
	
	class WordnetAtom : public PluginAtom {
	
	public:
		WordnetAtom();
		virtual void retrieve(const Query& query, Answer& answer) throw (PluginError);
	private:
		#ifdef PROFILE
		double total_time;
		#endif
		void init();
	}
	
  }
}

#endif // _WN_PLUGIN_WNATOM_H_
