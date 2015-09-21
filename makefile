all: enumerate_rpn rpn

enumerate_rpn: enumerate_rpn.cpp 
	clang++ -std=c++11 -Wall ./../cfg/cfg.o ./../cfg/parse_tree.o enumerate_rpn.cpp -o enumerate_rpn
rpn: main.cpp
	clang++ -std=c++11 -Wall main.cpp -o main

clean:
	rm -f *~ *.o a.out main dump enumerate_rpn
