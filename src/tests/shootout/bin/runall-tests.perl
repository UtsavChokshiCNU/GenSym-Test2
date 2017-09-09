#!/usr/local/bin/perl

# running perl tests (from Shootout/perl directory)
# cd perl
# ../bin/runall.perl perl .perl
# 
# running java tests (from Shooutout/java directory)
# cd java
# setenv CLASSPATH .
# ../bin/runall.perl java

$command=$ARGV[0];
$extension=$ARGV[1];

# Fibonnacci tests
run($command, "fibo$extension", "8");
run($command, "fibo$extension", "24");
run($command, "fibo$extension", "32"); 

# Ackerman tests
run($command, "ackermann$extension", "4");
run($command, "ackermann$extension", "5");
run($command, "ackermann$extension", "6");
run($command, "ackermann$extension", "7");
run($command, "ackermann$extension", "8");

# Heapsort tests
run($command, "heapsort$extension", "1000");
run($command, "heapsort$extension", "2000");
run($command, "heapsort$extension", "4000");
run($command, "heapsort$extension", "8000");

# String-concat tests
run($command, "strcat$extension", "5000");
run($command, "strcat$extension", "10000");
run($command, "strcat$extension", "150000");
run($command, "strcat$extension", "200000");

# Method call tests
run($command, "methcall$extension", "50000");
run($command, "methcall$extension", "100000");
run($command, "methcall$extension", "150000");
run($command, "methcall$extension", "200000");

# Object Instantiation tests
run($command, "objinst$extension", "50000");
run($command, "objinst$extension", "100000");
run($command, "objinst$extension", "150000");
run($command, "objinst$extension", "200000");

# Nested Loops tests
run($command, "nestedloop$extension", "4");
run($command, "nestedloop$extension", "8");
run($command, "nestedloop$extension", "12");
run($command, "nestedloop$extension", "16");


sub run {

my $command = shift(@_);
my $program  = shift(@_);
my $arg = shift(@_);

print("--------------------------------\n");
print("running: $command $program $arg\n");

($user, $system, $cuser, $csystem) = times;
system ($command, $program, $arg);
($userafter, $systemafter, $cuserafter, $csystemafter) = times;

my $total = ($userafter - $user) + ($systemafter - $system) +
($cuserafter - $cuser) + ($csystemafter - $csystem);

print("result: $command $program $arg = $total (s)\n");
print("--------------------------------\n");
}


