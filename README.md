# Fork and pipe simple process interaction

This lab was to demonstrate the interaction between adult and child processes, the main piece of code that is interesting is within the checkpasswd.c file, where the it takes in strings from standard input and create a child process running the validate.c code, to see whether the password is valid or not, that is if it is within the pass.txt file.

