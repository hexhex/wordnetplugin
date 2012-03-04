plugin_LTLIBRARIES = libdlvhexplugin-wordnet.la

libdlvhexplugin_wordnet_la_SOURCES = WordnetPlugin.cpp \
									 WordnetAtom.cpp \
									 WordRequest.cpp \
									 BaseForms.cpp \
									 Util.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_wordnet_la_LDFLAGS = -avoid-version -module
