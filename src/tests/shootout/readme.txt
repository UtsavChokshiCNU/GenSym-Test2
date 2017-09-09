Shootout KB Performance Test
----------------------------
ajs - 1/30/2004


The purpose of the shootout.kb is to compare the performance of features in
G2 that exist in other general purpose programming languages.

The tests used are implementations in G2 of a suite of tests that were created
by Doug Bageley (http://www.bagley.org/~doug/shootout).  Doug Bageley's tests
have been implemented and compared in over 30 different programming languages.

The advantages of using Doug's tests are:
i) They are pretty comprehensive;
ii) We do not have to design them;
iii) Doug provides the source for all the tests on his web site so it is simple
to test the performance of other languages that we wish to compare G2 to.

The shootout.kb currently depends on the btsdriver.kb and 
btsdriver-template.kb. The shootout.kb is committed in CVS in the 
/tests/shootout directory.

To run the G2 tests
-------------------

> cd /bt/ab/tests/shootout
> bin/run.sh

Load the shootout.kb

When the KB starts it automatically runs all the tests.

The test track is on the workspace SHOOTOUT-WS.

To view the results of an individual test block select the 'view results' 
user menu choice.

To view previously run java and perl tests for comparison select the 'view 
java results' or 'view perl results' user menu choice.


To run the Perl tests
-------------------

> cd /bt/ab/tests/shootout/perl
> ../bin/runall-tests.perl perl .perl

Results of the Perl tests are sent to standard output.


To run the Java tests
-------------------
> cd /bt/ab/tests/shootout/java
> setenv CLASSPATH .
> ../bin/runall-tests.perl java ""

Results of the Perl tests are sent to standard output.






