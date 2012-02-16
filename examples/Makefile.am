EXTRA_DIST= \
	tests/wordnetplugintests.test \
    ../testsuite/run-dlvhex-tests.sh \
    ../testsuite/answerset_compare.py \
	01-antonyms-nonword.hex \
    tests/01-antonyms-nonword.out

# we run only one test which should return nothing, but verify that the plugin can be built and loaded
# (as WordNet is subject to change, we cannot create fixed testcases except testcases with non-existing words like this one)

TESTS = $(top_srcdir)/testsuite/run-dlvhex-tests.sh

TESTS_ENVIRONMENT = \
        TOP_SRCDIR=$(top_srcdir) \
        DLVHEX="$(DLVHEX_BINDIR)/dlvhex2 -s --plugindir=!$(top_builddir)/src/.libs" \
        EXAMPLESDIR=$(top_srcdir)/examples \
        TESTDIR=$(top_builddir)/examples/tests \
        OUTDIR=$(top_srcdir)/examples/tests
