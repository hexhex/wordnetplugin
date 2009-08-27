EXTRA_DIST= \
  tests/run-dlvhex-tests.sh \
  tests/wordnetplugintests.test \
  tests/01-antonyms-nonword.out \
  01-antonyms-nonword.hex

# we run only one test which should return nothing, but verify that the plugin can be built and loaded
# (as WordNet is subject to change, we cannot create fixed testcases except testcases with non-existing words like this one)
TESTS = ./tests/run-dlvhex-tests.sh
TESTS_ENVIRONMENT = TESTDIR=$(top_srcdir)/examples/tests DLVHEX=dlvhex PARAMETERS="-s --plugindir=$(CURDIR)/$(top_builddir)/src/impl/"
