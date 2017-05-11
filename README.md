# fhclose.c

This is a simple c application for Linux systems that will close all file handles above
STDIN/STDOUT/STDERR before execvp()'ing its first operand, passing subsequent operands through to the exec()ed program.

This is useful when you need to launch a child process from a language such as PHP that offers
no way to prevent the child from inheriting your file handles.

Compile with just `gcc -o fhclose fhclose.c`

Use like:
```
% ./fhclose echo 'this is an example -- echo definitely has no file handles besides STDIN/OUT/ERR'
this is an example -- echo definitely has no file handles besides STDIN/OUT/ERR
%

