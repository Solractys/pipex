set follow-fork-mode child
set detach-on-fork off
b main
r infile "grep a" "wc -l" outfile23242
set logging enable on
backtrace
info locals
