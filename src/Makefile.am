#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexwordnet.la

#
# replace 'plugin' on the left side as above and
# add all sources of your plugin
#
libdlvhexwordnet_la_SOURCES = \
			      WordnetPlugin.cpp \
			      WordnetAtom.cpp \
			      WordRequest.cpp \
			      BaseForms.cpp \
			      Util.cpp

#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	$(CPPFLAGS) \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexwordnet_la_LDFLAGS = -avoid-version -module
