#!/usr/local/bin/perl
# We need network services.
require 'sys/socket.ph';

# Parse the User's Request
($who, $password, $request) = @ARGV;
# $password = <STDIN>;
# chop $password;

# Where is the licensing server.
$host = "tha"; $port = 7535;
# What to do on interupt.

# Open a stream <S> to the server, just like in Perl man page.
$sockaddr = 'S n a4 x8';
($name, $aliases, $type, $len, $thataddr) = gethostbyname($host);
$this = pack($sockaddr, &AF_INET, 0, $thisaddr);
$that = pack($sockaddr, &AF_INET, $port, $thataddr);
socket(S, &PF_INET, &SOCK_STREAM, $proto) || die "socket: $!";
bind(S, $this) || die "bind: $!";
connect(S, $that) || die "connect: $!";
select(S); $| = 1; select(stdout);

# Are we connected?
$_ = <S>; die "No server?" unless /Howdy/;

# Send our request.
print S "(do-for-me $who ($request))";

# Respond to the challenge.
$_ = <S>;
die "No challenge?" unless /Challenge: (\d*)/;
$response = `response $password $1`;
chop $response;
print S "(response \"$response\")";

# Dump the reply to our request.
while(<S>){ print unless /Have a nice day/; }
