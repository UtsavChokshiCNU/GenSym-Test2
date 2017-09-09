Readme.txt for tests/defs Module

Mark H. David
Oct. 30, 2001

This module contains definitions corresponding to the rather complicated and
series of validity tests that occur when there is a change to a definition,
specifically for changes to the direct-superior-class of a definition.

The test KBs here are at present not automated. Hopefully, a level of automation
could be done. Probably, they could all be included in one KB and run as player
regression tests.

The tests KBs' names are prepended with a number from 1 to 24, and the number
corresponds to numbering of these tests in DEFINITIONS in the subsection Testing
for Valid Superior Classes.

This set of tests were built when we decided to rewrite the once-giant function
invalid-set-of-direct-superior-classes-p and the once-giant slot value compiler
for the direct-superior-classes slot to be drivers for the 24 tests, which were
extracted so as to be maintained as individual functions.  The initial commit of
this module is going in with that change.

At present, there is missing a full set of tests, but this provides a good
start, and the remaining tests should be and can be readily added in the future.
All tests that are here were found to pass both before and after this large
change.

NOTE: save tests in an earlier major version only, so we can readily test for
regressions.  The KBs in the initial commit were all saved in G2 5.1r9.


Listing of KBs in this directory:
--------------------------------

 1-specified-an-internal-system-class.kb
 2-no-editing-of-default-junction.kb
 3-default-junction-cannot-be-a-direct-superior-class.kb
 4-no-editing-of-transient-definition-with-defaults.kb
 5-direct-superior-is-name-of-class.kb
 6-incorrect-foundation-class-for-this-definition.kb
 7-direct-superior-not-the-mixed-hierarchy-type.kb
11-system-inheritance-change-for-instantiated-class.kb

