AC_PREREQ([2.61])
AC_INIT([dlvhex-wordnetplugin],[0.3.0],[juergen.bock@web.de])
AC_CONFIG_SRCDIR([src/impl/wordnetplugin.cpp])

MAJOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/"`
MINOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/"`
MICRO=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/"`

# user corresponding names and texts here
AC_DEFINE_UNQUOTED([WORDNETPLUGIN_MAJOR], [$MAJOR], [Major version number of the wordnet-plugin])
AC_DEFINE_UNQUOTED([WORDNETPLUGIN_MINOR], [$MINOR], [Minor version number of the wordnet-plugin])
AC_DEFINE_UNQUOTED([WORDNETPLUGIN_MICRO], [$MICRO], [Micro version number of the wordnet-plugin])

AM_INIT_AUTOMAKE

AC_CANONICAL_HOST

# by default we look into /opt/local and /sw for include files (macports vs. fink)
case $host_os in
     darwin*|macosx*)
	CPPFLAGS="$CPPFLAGS -I/opt/local/include -I/sw/include"
     ;;
esac 



# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for header files.
AC_HEADER_DIRENT
AC_CHECK_HEADERS([time.h])
AC_CHECK_HEADERS([sys/param.h])

# Debugging option
AC_ARG_ENABLE(debug,
              [  --enable-debug          enable debugging output],
	      [AC_DEFINE(DEBUG)]
	     )	      

# Profiling option
AC_ARG_ENABLE(profile,
              [  --enable-profile        enable performance analysis],
	      [AC_DEFINE(PROFILE)]
	     )

# Assume WordNet in this directory:
ASSUMED_WN_BASE="/usr/local/WordNet-2.1"

#
# running configure --with-wordnet will take wordnetdir.
#

AC_ARG_WITH(wordnet,
           [  --with-wordnet          Base directory of WordNet], 
           [wordnetdir=$withval],
           [wordnetdir=$ASSUMED_WN_BASE]
           )

#AC_SUBST([wordnetdir])

# Look for WordNet header and library in additional directories
CPPFLAGS="$CPPFLAGS -I$wordnetdir/include"
LDFLAGS="$LDFLAGS -L$wordnetdir/lib"

AC_CHECK_HEADERS(wn.h,
                 [],
		 AC_MSG_ERROR([WordNet header not found. \
Check your WordNet installation \
or use --with-wordnet to \
specify the WordNet base directory.]))


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC # we don't need a static library
AC_PROG_LIBTOOL

#
# check for the WordNet wn library
#
AC_CHECK_LIB([WN], 
             wninit, 
             [], 
             AC_MSG_ERROR([WordNet library not found. \
Check your WordNet installation \
or use --with-wordnet to specify \
the WordNet base directory.]))

#
# of course we need dlvhex itself!
#
PKG_CHECK_MODULES([DLVHEX], [dlvhex >= 1.7])

# checking for boost libs
BOOST_REQUIRE([1.33.0])
BOOST_SMART_PTR
BOOST_STRING_ALGO
BOOST_TOKENIZER

#
# where the plugin will be installed by default.
# running configure will take sysplugindir from dlvhex.pc,
# running configure --enable-userinstall will take homeplugindir.
#

AC_ARG_ENABLE(userinstall, 
             [  --enable-userinstall    Install plugin into home directory],
             [plugindir=$HOME/`pkg-config dlvhex --variable=userplugindir`],
             [plugindir=`pkg-config dlvhex --variable=sysplugindir`]
             )
AC_SUBST([plugindir])

#
# all needed makefiles
#
AC_CONFIG_FILES([
           Makefile
           src/impl/Makefile
           include/impl/Makefile
])

AC_OUTPUT


