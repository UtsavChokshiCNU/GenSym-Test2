#!/bin/csh
# This script calls createkey with its arguments, tnen sleeps for 2
# seconds.

# min sleep time between generations is 1 second, but we 
# have to use 2, so this will never happen during the same
# second according to the absolute time of day.
set min_sleep_time=2


./createkey $argv
sleep $min_sleep_time
