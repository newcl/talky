#bison
cd bison
bison -d talky.y
cd ..

#flex
cd flex
flex talky.l
cd ..

# -ll for mac os, others should use -lfl if flex is installed correctly
g++ -w -std=c++11 -o talky  ./bison/talky.tab.c ./flex/lex.yy.c ./parser/src/main.cpp ./parser/src/talky_parser.cpp ./parser/src/talky_unit.cpp ./parser/src/interface.cpp  ./parser/src/structure.cpp ./parser/src/function.cpp ./parser/src/enum.cpp ./parser/src/util.cpp ./parser/src/java_code_generator.cpp ./parser/src/code_generator.cpp ./parser/src/c_sharp_code_generator.cpp   -lboost_program_options -lboost_filesystem -lboost_system -ll -lstdc++
#g++ -w -lboost_program_options -lboost_filesystem -lboost_system -ll -lstdc++ -o talky ./bison/talky.tab.c ./flex/lex.yy.c ./parser/src/parser.cpp 
