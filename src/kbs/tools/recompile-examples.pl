#!/usr/local/bin/perl

if(@ARGV < 3) {
    print "Usage: $0 /bt/srcbox/kbs/tools/example-kbs.txt host port [-full]\n";
    print "  Recompile and commit example kbs using G2 running on host and port\n";
    print "  (-full really recompiles, rather than just resaving.)\n";
    exit;
}

if (@ARGV > 3 && $ARGV[3] eq '-full') {
    $program = "RecompileKB";
} else {
    $program = "LoadAndSaveKB";
}

die "DISPLAY is not set (and java is stupid)" unless $ENV{DISPLAY};

$kbsfile = $ARGV[0];
open(HANDLE,$kbsfile);


while ($line = <HANDLE>) {
    chop($line);
    if (length($line) > 0) {
	$onefile = "$ENV{SRCBOX}/$line";
	if ( -e "$onefile" ) {
	    system("java com.gensym.tests.$program -g2host $ARGV[1] -g2port $ARGV[2] -kb $onefile");
	} else {
	    die "$onefile does not exist!";
	}
    }
}

