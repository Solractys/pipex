set follow-fork-mode child
set detach-on-fork off
b main
r infile "grep a" "///usr/bin/wc -l" outfile
set logging enable on
backtrace
info locals
