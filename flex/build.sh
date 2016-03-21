flex talky.l
# -ll for mac os, others should use -lfl if flex is installed correctly
g++ lex.yy.c -ll -o talky
