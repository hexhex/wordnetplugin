EXTRA_DIST= \
  tests/wordnetplugintests.test \
  ../testsuite/run-dlvhex-tests.sh \
  ../testsuite/answerset_compare.py \
  01-antonyms.hex \
  01-antonyms-nonword.hex \
  02-hypernyms.hex \
  03-hyponyms.hex \
  04-entailment.hex \
  05-similar.hex \
  06-holonyms_member.hex \
  07-holonyms_substance.hex \
  08-holonyms_part.hex \
  09-meronyms_member.hex \
  10-meronyms_substance.hex \
  11-meronyms_part.hex \
  14-causeto.hex \
  15-participleofverb.hex \
  18-attribute.hex \
  20-derivations.hex \
  23-synonyms.hex \
  38-instanceof.hex \
  39-instances.hex \
  baseforms.hex \
  relative_via_holonym.hex \
  relative_via_hypernym.hex \
  tests/01-antonyms-nonword.out \
  tests/cautiously_true.stdout


TESTS = $(top_srcdir)/testsuite/run-dlvhex-tests.sh

TESTS_ENVIRONMENT = \
        TOP_SRCDIR=$(top_srcdir) \
        DLVHEX="$(DLVHEX_BINDIR)/dlvhex2 -s --plugindir=!$(top_builddir)/src/.libs" \
        EXAMPLESDIR=$(top_srcdir)/examples \
        TESTS=$(top_srcdir)/examples/tests/wordnetplugintests.test \
        OUTDIR=$(top_srcdir)/examples/tests

