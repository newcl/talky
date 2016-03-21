#bison
cd bison
bison -d talky.y
cd ..

#flex
cd flex
flex talky.l
cd ..

# -ll for mac os, others should use -lfl if flex is installed correctly
g++ ./bison/talky.tab.c ./flex/lex.yy.c -ll -o talky
