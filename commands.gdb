set follow-fork-mode child
set detach-on-fork off
b main
r here_doc eof cat cat cat outfile
set logging enable on
info locals
