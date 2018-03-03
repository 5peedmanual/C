#!/bin/bash
echo "creating a tmp file with 400 MB of random data"
head -c 400MB < /dev/urandom > tmpfile
echo "done"
sleep 1
ls -l tmpfile
dfcmd="$(df $HOME)"
df $HOME
printf "free space:\t%s\n" "${dfcmd:119:10}"
sleep 2
echo "Starting program"
./a.out &
sleep 1
echo "checking that tmpfile is gone"
ls -l tmpfile
sleep 1
echo "checking available space again"
dfcmd_before_exit="$(df $HOME)"
printf "free space:\t%s\n" "${dfcmd_before_exit:119:10}"
sleep 16
echo "program is done, all open files are close.\nNow new disk space \
should be available"
# The file is not deleted while the program is running, because its still open
# Only when the process either closes the file or terminates, which causes 
# the kernel to close all its open files, is the file deleted.
dfcmd_after_exit="$(df $HOME)"
printf "free space:\t%s\n" "${dfcmd_after_exit:119:10}"
