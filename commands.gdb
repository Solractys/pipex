set follow-fork-mode child
set detach-on-fork off
b main
r infile "cat" "grep hello" "wc -l" outfile
set logging enable on
info locals
