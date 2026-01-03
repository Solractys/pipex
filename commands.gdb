set follow-fork-mode child
set detach-on-fork off
b main
r infile cat cat cat "wc -l" outfile32
set logging enable on
info locals
