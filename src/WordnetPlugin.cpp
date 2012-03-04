/* -*- C++ -*- */

/**
 * @file   wordnetplugin.cpp
 * @author Juergen Bock
 * @date   06/08/2006
 *
 * @brief  Definition of classes WordNetAtom and WordNetPlugin
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "WordnetPlugin.h"
#include "WordnetAtom.h"

namespace dlvhex {
  namespace wordnet {

	WordnetPlugin::WordnetPlugin() { 
	
		setNameVersion(PACKAGE_TARNAME, WORDNETPLUGIN_VERSION_MAJOR, 
				WORDNETPLUGIN_VERSION_MINOR, WORDNETPLUGIN_VERSION_MICRO);
		LOG(DBG, "WordnetPlugin::WordnetPlugin");
	}
	
	WordnetPlugin::~WordnetPlugin() { }
	
	std::vector<PluginAtomPtr> WordnetPlugin::createAtoms(ProgramCtx&) const {
		
		LOG(DBG, "WordnetPlugin::createAtoms");
		std::vector<PluginAtomPtr> ret;
		ret.push_back(PluginAtomPtr(new WordnetAtom, PluginPtrDeleter<PluginAtom>()));
		return ret;
	}
	
	WordnetPlugin theWordnetPlugin;

  } // namespace wordnet
} // namespace dlvhex

IMPLEMENT_PLUGINABIVERSIONFUNCTION

extern "C"
void *PLUGINIMPORTFUNCTION() {
	return reinterpret_cast<void*>(& dlvhex::wordnet::theWordnetPlugin);
}

/*
extern "C"
dlvhex::wordnet::WordNetPlugin*
PLUGINIMPORTFUNCTION() {
  dlvhex::wordnet::theWordNetPlugin.setPluginName(PACKAGE_TARNAME);
  dlvhex::wordnet::theWordNetPlugin.setVersion(WORDNETPLUGIN_MAJOR,
					       WORDNETPLUGIN_MINOR,
					       WORDNETPLUGIN_MICRO);
  
  return &dlvhex::wordnet::theWordNetPlugin;
}
*/
