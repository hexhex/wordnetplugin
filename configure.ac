AC_PREREQ([2.59])

AC_INIT([dlvhex-wordnetplugin],[0.1],[juergen.bock@web.de])
AC_CONFIG_SRCDIR([src/impl/wordnetplugin.cpp])

AM_INIT_AUTOMAKE

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
AC_PROG_LIBTOOL

#
# check for the WordNet wn library
#
AC_CHECK_LIB(WN, 
             wninit, 
             [], 
             AC_MSG_ERROR([WordNet library not found. \
Check your WordNet installation \
or use --with-wordnet to specify \
the WordNet base directory.]))

#
# of course we need dlvhex itself!
#
PKG_CHECK_MODULES([DLVHEX], [dlvhex >= 0.1])

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
])

AC_OUTPUT


