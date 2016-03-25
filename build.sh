#bison
cd bison
bison -d talky.y
cd ..

#flex
cd flex
flex talky.l
cd ..

# -ll for mac os, others should use -lfl if flex is installed correctly
# g++ -std=c++11 ./parser/src/parser.cpp ./bison/talky.tab.c ./flex/lex.yy.c -ll -o talky
g++ ./parser/src/parser.cpp ./bison/talky.tab.c ./flex/lex.yy.c -ll -o talky
