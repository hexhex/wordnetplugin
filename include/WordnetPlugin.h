#ifndef _WN_PLUGININTERFACE_H
#define _WN_PLUGININTERFACE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <dlvhex2/PluginInterface.h>

namespace dlvhex {
  namespace wordnet {
	
	class WordnetPlugin : public PluginInterface {
		
	public:
		WordnetPlugin();
		~WordnetPlugin();
		std::vector<PluginAtomPtr> createAtoms(ProgramCtx&) const;	
	}
	
  }
}

#endif // _WN_PLUGININTERFACE_H
