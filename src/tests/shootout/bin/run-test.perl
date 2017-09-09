#!/usr/local/bin/perl

($user, $system, $cuser, $csystem) = times;
system ($ARGV[0], $ARGV[1], $ARGV[2]);
($userafter, $systemafter, $cuserafter, $csystemafter) = times;

$total = ($userafter - $user) + ($systemafter - $system) +
($cuserafter - $cuser) + ($csystemafter - $csystem);
print("$ARGV[0] $ARGV[1] $ARGV[2]: $total (s)\n");


