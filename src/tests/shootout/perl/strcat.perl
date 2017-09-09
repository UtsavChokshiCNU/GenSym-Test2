#!/usr/local/bin/perl 
# $Id: strcat.perl,v 1.1 2004-01-30 23:03:10 ajs Exp $
# http://www.bagley.org/~doug/shootout/

use strict;

my $NUM = $ARGV[0];
$NUM = 1 if ($NUM < 1);

my $str = "";
foreach (1..$NUM) {
    $str .= "hello\n"
} 
print length($str),"\n";

