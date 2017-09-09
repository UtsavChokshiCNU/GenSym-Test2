
# This file is intended to be sourced at the beginning of every tape writing
# script.  These scripts are called out of make-gensym-tape, and contain the
# knowledge about how to write a tape for a particluar platform/media pair.
# This file will accept arguments given to the tape writing script and set them
# into the following variables: command, media, platform, software_platform,
# parts_list, release_directory, target_host, and target_pathname.

# Make-gensym-tape decides which tape writing script to call by looking up a
# platform/media pair in the file media-map.dat.

# Tape writing scripts are invoked with three, eight or ten arguments.
#  - a command -- one of rewind, write, offline
#  - the requested media  -- enumerated in media.dat
#  - the requested media platform -- enumerated in platforms.dat, this is
#    the type of computer that contains the media device.
# The remaining arguments are only given for the write command.
#  - the requested software platform -- enumerated in platforms.dat, this is
#    the type of computer that runs the software being placed on the media
#  - the product name
#  - the release number
#  - the parts-list -- a file of pathnames, relative to the product release
#    directory.
#  - the release-directory -- This is the product release directory that is to
#    go onto the tape.  It will contain symbolic links!  They should not go
#    onto the tape, but the files they reference should.  Tar does this when
#    given the -h switch.
# The next two arguments appear if the media.dat states that this media
# requires a target for example unix-directory, or unix-tar-file.
# - the target-host  -- the machine were the result should be put, this is bound
#   to SELF if the target-host is the machine you are running on right now.
# - the target-pathname -- what can I say?
# If these are not bound you can use $?target_pathname to notice that.

set command = "$1"
if ($command == write) then
  echo "LOG: Beginning to write:"
else if ($command == rewind) then
  echo "LOG: Rewinding tape:"
else if ($command == offline) then
  echo "LOG: Taking media offline:"
else if ($command == online) then
  echo "LOG: Bringing media online:"
else
  echo "ERROR: Unrecognized command $command to $0"
  exit 1
endif

set media = "$2"
set platform = "$3"
# echo "    script:        $0"
echo "    media:         $media"
echo "    platform:      $platform"
if ($#argv > 3) then
  set software_platform = "$4"
  set product = "$5"
  set release = "$6"
  set parts_list = "$7"
  set release_directory = "$8"
  echo "    software_platform: $software_platform"
  echo "    product:       $product"
  echo "    release:       $release"
#  echo "    parts_list:    $parts_list"
#  echo "    directory:     $release_directory"
  if ($#argv > 8) then
    set target_host = "$9"
    set target_pathname = "$10"
    echo "    target_host:   $target_host"
    echo "    target_pathname: $target_pathname"
  endif
endif

# Tar Switches explained
# c -- create
# e -- exit immediately if error occurs
# h -- release symbol links with the actual files
# l -- error message if links can not be resolved
# f -- file to create next argument
# C -- chdir to this directory so file names are relative to here.
